package main

import (
	"fmt"
	"log"
	"math/big"

	"github.com/consensys/gnark-crypto/ecc"
	"github.com/consensys/gnark-crypto/ecc/bn254/fr"
	"github.com/consensys/gnark/backend/groth16"
	"github.com/consensys/gnark/frontend"
	"github.com/consensys/gnark/frontend/cs/r1cs"
)

const MAX_N = 20 // Максимальное значение n

// Определение схемы FibonacciCircuit
type FibonacciCircuit struct {
	// Приватные входные данные
	Sequence      [MAX_N + 1]frontend.Variable `gnark:"sequence,secret"` // F0 to Fn
	CmpResultsSum frontend.Variable            `gnark:"secret"`          // Sum

	// Публичные входные данные
	N  frontend.Variable `gnark:"n,public"`  // индекс n
	Fn frontend.Variable `gnark:"fn,public"` // n-е число Фибоначчи
}

// Метод Define описывает ограничения схемы
func (circuit *FibonacciCircuit) Define(api frontend.API) error {
	// Установка начальных условий
	api.AssertIsEqual(circuit.Sequence[0], 0)
	api.AssertIsEqual(circuit.Sequence[1], 1)

	// Рекуррентное соотношение
	for i := 2; i <= MAX_N; i++ {
		sum := api.Add(circuit.Sequence[i-1], circuit.Sequence[i-2])
		api.AssertIsEqual(circuit.Sequence[i], sum)
	}

	// Проверка, что n <= MAX_N
	api.AssertIsLessOrEqual(circuit.N, MAX_N)

	// Вычисление Fn на основе N
	// fn := circuit.Sequence[0]
	for i := 1; i <= MAX_N; i++ {
		condition := api.Cmp(circuit.N, i)
		api.Println("condition", condition)
		cmpResultSq := api.Mul(condition, condition)
		api.Println("cmpResultSq", cmpResultSq)
		circuit.CmpResultsSum = api.Add(circuit.CmpResultsSum, cmpResultSq)
	}
	api.Println("circuit.CmpResultsSum", circuit.CmpResultsSum)
	api.Println("MAX_N-1", MAX_N-1)

	api.AssertIsEqual(circuit.CmpResultsSum, MAX_N-1)

	return nil
}

func main() {
	// Создаем схему
	var circuit FibonacciCircuit

	// Компилируем схему
	r1cs, err := frontend.Compile(ecc.BN254.ScalarField(), r1cs.NewBuilder, &circuit)
	if err != nil {
		log.Fatal(err)
	}

	// Устанавливаем n
	n := 10
	if n > MAX_N {
		log.Fatalf("n должно быть меньше или равно %d", MAX_N)
	}

	// Вычисляем последовательность Фибоначчи до MAX_N
	sequence := make([]*big.Int, MAX_N+1)
	sequence[0] = big.NewInt(0)
	sequence[1] = big.NewInt(1)
	for i := 2; i <= MAX_N; i++ {
		sequence[i] = new(big.Int).Add(sequence[i-1], sequence[i-2])
	}

	// Создаем приватное свидетельство
	witnessAssignment := &FibonacciCircuit{
		N:  n,
		Fn: sequence[n],
	}

	for i := 0; i <= MAX_N; i++ {
		witnessAssignment.Sequence[i] = sequence[i]
	}

	witnessAssignment.CmpResultsSum = big.NewInt(0)

	// Создаем Witness с помощью API
	fullWitness, err := frontend.NewWitness(witnessAssignment, fr.Modulus())
	if err != nil {
		log.Fatal(err)
	}

	// Создаем публичное свидетельство
	publicWitness, err := fullWitness.Public()
	if err != nil {
		log.Fatal(err)
	}

	// Генерируем ключи для Groth16
	pk, vk, err := groth16.Setup(r1cs)
	if err != nil {
		log.Fatal(err)
	}

	// Генерируем доказательство
	proof, err := groth16.Prove(r1cs, pk, fullWitness)
	if err != nil {
		log.Fatal(err)
	}

	// Верифицируем доказательство
	err = groth16.Verify(proof, vk, publicWitness)
	if err != nil {
		fmt.Println("Доказательство неверно:", err)
	} else {
		fmt.Println("Доказательство успешно верифицировано")
	}
}
