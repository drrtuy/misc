program dz_6_1;

Uses
    SysUtils;

Type
    TIntArray = array of integer;
    TIntArrPntr = ^TIntArray;
    TArrElement = record
      Value: integer;
      prev: ^integer;
      next: ^integer;
    end;
    TDynArray = record
      ArrPntr: TIntArrPntr;
      Length: ^integer;
    end;


procedure print_array(DynArr: TDynArray);
var
   ArrLength, i : integer;
   InputArray: ^TIntArray;
begin
  InputArray := DynArr.ArrPntr;
  ArrLength := DynArr.Length^;

  for i := 0 to ArrLength-1 do
  begin
     writeln('Значение ', InputArray^[i]);
  end;
end;

procedure array_input(DynArr: TDynArray);
var
     UserInput: string;
     Ind : integer = 0;
     InputArray: ^TIntArray;

begin
  writeln('Введите значения элементов массива(типа integer) , подтверждая ввод каждого нажатием Enter');
  writeln('Чтобы завершить ввод элементов, введите слово end');
  writeln('!!! Обратите внимание, что ,по определению, множество не может содержать одинаковых элементов!!!');
  InputArray := DynArr.ArrPntr;
  SetLength(InputArray^, 2);

  repeat
    readln(UserInput);
    if UserInput = 'end' then
       break;
    InputArray^[Ind] := StrToIntDef(UserInput, 0);
    writeln('Очередной эл массива: ', InputArray^[Ind]);
    Ind += 1;
    if Ind >= Length(InputArray^)-1 then
       SetLength(InputArray^, Length(InputArray^)*2);
  until False;

  DynArr.Length^ := Ind;
end;

{Расчитываем получить множества ArrA и ArrB, содержащими только уникальные элементы. }
procedure get_args_merge(ArrA: TDynArray; ArrB: TDynArray; ArrMerge: TDynArray);
var
   bigLength, smallLength, i, it, ite, el, flag: integer;
   bigArr, smallArr,targetArr : TIntArrPntr;

begin
  bigLength := ArrA.Length^;
  bigArr := ArrA.ArrPntr;
  smallLength := ArrB.Length^;
  smallArr := ArrB.ArrPntr;

  if ArrA.Length^ < ArrB.Length^ then
  begin
     bigLength := ArrB.Length^;
     bigArr := ArrB.ArrPntr;
     smallLength := ArrA.Length^;
     smallArr := ArrA.ArrPntr
  end;
  //Merged множество в этой точке равно меньшему из двух исходных.
  //Но размер merge равен длине большего.
  setLength(ArrMerge.ArrPntr^, bigLength);
  ArrMerge.Length^ := smallLength;
  for i := 0 to smallLength-1 do
      ArrMerge.ArrPntr^[i] := smallArr^[i];
{
  writeln('Массив перед операцией');
  print_array(ArrMerge);
}
  i := 0;
  ite := smallLength;
//Проход по бОльшему массиву. Каждая итерация содержит проход по меньшему массиву.
  while i < bigLength do
  begin
     el := bigArr^.[i];

     //Сравниваем последний элемент с искомым только один раз за проход по меньшему массиву.
     if el = smallArr^[smallLength-1] then
        break;
     it := 0;
     while ( it < smallLength ) and ( el <> smallArr^[it] ) do
        it += 1;

     //Добавляем элемент в результат, если массив полностью пройден
     if it = smallLength then
     begin
        ArrMerge.ArrPntr^[ite] := el;
        ite += 1;
        ArrMerge.Length^ += 1;
     end;
     i += 1;
  end;
{
  writeln('Массив после операции');
  print_array(ArrMerge);
}
end;

{Расчитываем получить множества ArrA и ArrB, содержащими только уникальные элементы. }
procedure get_args_interception(ArrA: TDynArray; ArrB: TDynArray; ArrInter: TDynArray);
var
 bigLength, smallLength, interLength, i, it, ite, el: integer;
 bigArr, smallArr,targetArr : TIntArrPntr;

begin
  bigLength := ArrA.Length^;
  bigArr := ArrA.ArrPntr;
  smallLength := ArrB.Length^;
  smallArr := ArrB.ArrPntr;

  if ArrA.Length < ArrB.Length then
  begin
     bigLength := ArrB.Length^;
     bigArr := ArrB.ArrPntr;
     smallLength := ArrA.Length^;
     smallArr := ArrA.ArrPntr
  end;

  //Создаём пустое Interception множество нулевой мощности, как массив длинной 10.
  setLength(ArrInter.ArrPntr^, 10);
  ArrInter.Length^ := 0;
  interLength := 0;
{
  writeln('Массив перед операцией');
  print_array(ArrMerge);
}
  i := 0;
  ite := 0;
//Проход по бОльшему массиву. Каждая итерация содержит проход по меньшему массиву.
  while i < bigLength do
  begin
     el := bigArr^.[i];
     it := 0;
     while ( el <> smallArr^[it] ) and ( it < smallLength ) do
        it += 1;
     //Добавляем элемент в результат, если элемент найден в обоих массиве.
     if ( it < smallLength ) or ( el = smallArr^[smallLength-1] ) then
     begin
        ArrInter.ArrPntr^[ite] := el;
        if ite = ArrInter.Length^-2 then//Динамически наращиваем по необходимости
           SetLength(ArrInter.ArrPntr^, ArrInter.Length^*2);
        ite += 1;
        ArrInter.Length^ += 1;
     end;
     i += 1;
  end;
{
  writeln('Массив после операции');
  print_array(ArrMerge);
}

end;

var
   DynArrA, DynArrB, DynArrC: TDynArray;

begin
   new(DynArrA.ArrPntr);
   new(DynArrA.Length);
   new(DynArrB.ArrPntr);
   new(DynArrB.Length);
   new(DynArrC.ArrPntr);
   new(DynArrC.Length);
   DynArrC.Length^ := 0;

   array_input(DynArrA);
   array_input(DynArrB);

   if ( DynArrA.Length^ = 0 ) or ( DynArrB.Length^ = 0 ) then
   begin
      writeln('Задан пустой массив');
      Halt(1);
   end;

   {
   print_array(DynArrA);
   print_array(DynArrB);
   }

   get_args_merge(DynArrA, DynArrB, DynArrC);
   writeln('Объединение массивов');
   print_array(DynArrC);
   get_args_interception(DynArrA, DynArrB, DynArrC);
   writeln('Пересечение массивов');
   print_array(DynArrC);

end.

