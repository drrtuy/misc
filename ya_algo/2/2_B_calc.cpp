// 48924798
#include <iostream>
#include <cassert>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <type_traits>
#include <cctype>
#include <string>
#include <functional>

void calcCheckerWrapper(std::istream& in, std::ostream& out);

void testCalcChecker()
{
    std::stringstream in;
    in << "2 1 2 / *\n";
    std::stringstream ss;
    calcCheckerWrapper(in, ss);
    std::string out = ss.str();
    assert(out == "0\n");
    
    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "7 2 + 4 * 2 +\n";
    calcCheckerWrapper(in, ss);
    out = ss.str();
    assert(out == "38\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "2 1 + 3 *\n";
    calcCheckerWrapper(in, ss);
    out = ss.str();
    assert(out == "9\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "0 1 - 3 /\n";
    calcCheckerWrapper(in, ss);
    out = ss.str();
    assert(out == "-1\n");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "10 2 4 * -\n";
    calcCheckerWrapper(in, ss);
    out = ss.str();
    assert(out == "2\n");

}

using CalcOperandType = int32_t;
using FType = std::function<const CalcOperandType(const CalcOperandType, const CalcOperandType)>; 
using FMapType = std::unordered_map<std::string, FType>;

// Оставил в public только то, что надо.
class CalcCheckerStack: private std::stack<CalcOperandType>
{
  public:
    using std::stack<CalcOperandType>::top;
    using std::stack<CalcOperandType>::pop;
    using std::stack<CalcOperandType>::push;
    
    const CalcOperandType pop_top()
    {
        const CalcOperandType topElement = top();
        pop();
        return topElement;
    }
};

// Целочисленное деление ушербно в большистве языков, т.е. если результат положителен
// то он округляется вниз, а если отрицателен, то вверх.
// Если остаток отрицательное число, представленое доп. кодом, сдвиг битов вправо которого даст -1,
inline CalcOperandType divideRoundDown(const CalcOperandType x, const CalcOperandType y)
{
    return (x / y) + ((x % y) >> 31);
}

// Да, std::function wrapper отлично подошёл.
// В исходной версии, я первым дело попробовал мат. операции из functional, но
// не было типа для value в мапе - компилятор жалился, что std::plus<CalcOperandType>()
// это временный объект и нельзя сохранить его ссылку. А вот target std::function
// отлично для этого подошёл - благодарю за подсказку.
FMapType ops = {{"+", std::plus<CalcOperandType>()},
                {"-", std::minus<CalcOperandType>()},
                {"*", std::multiplies<CalcOperandType>()},
                {"/", divideRoundDown},
};

// Парсим поток, вытаскивая отдельные слова. Если слово - число,то бросаем операнд на стэк,
// Если слово это операция, то берём два операнда из стэка и исполняем арифметическую операцию.
// Операции хранятся в map-е с ключём равным строковому представлению операции в ОПН.
// Результат берём с вершины стэка.
void calcCheckerWrapper(std::istream& in, std::ostream& out)
{
    CalcCheckerStack stack;
    std::string element;
    while (in >> element)
    {
        // Любопытный факт, но конструкция, приведённая ниже давала RE во
        // многих тестах, например в 6. Поделитесь вводом, чтобы понять, что сбоило?
        // Результаты отправки других мне не видны - прав не хватает.
        // Вот моя посылка с множеством RE, ушедших после замены закоментированного.
        // 48824876
        /*
        if (!element.empty() && std::isdigit(element[0]))
        {
            stack.push(std::stoi(element));
        }
        */
        // Пытаемся прочитать CalcOperandType из очередного слова входного потока
        CalcOperandType operand;
        std::istringstream stream(element);
        stream >> operand;
        if (!stream.fail())
            stack.push(operand);
        else
        {
            const CalcOperandType rhs = stack.pop_top();
            const CalcOperandType lhs = stack.pop_top();
            // Результат падает на вершину стека.
            stack.push(ops[element](lhs, rhs));
        }

    }
    // Ответ на вершине стека.
    out << stack.top() << "\n";
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        testCalcChecker();
    else
        calcCheckerWrapper(std::cin, std::cout);
    std::cout << "\n";
}
