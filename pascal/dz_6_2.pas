program dz_6_2;

Uses
    SysUtils;

Type
    TArrElement = record
      Value: integer;
      prev: ^integer;
      next: ^integer;
      Seen: boolean;
    end;
    TIntArray = array of TArrElement;
    TIntArrPntr = ^TIntArray;
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
     writeln('Значение ', InputArray^[i].Value);
  end;
end;

procedure copy_array(ArrSrc, ArrDst: TDynArray);
var
   ArrLength, i : integer;
   InputArray, DstArray: ^TIntArray;
begin
  InputArray := ArrSrc.ArrPntr;
  ArrLength := ArrSrc.Length^;
  DstArray := ArrDst.ArrPntr;

  SetLength(DstArray^, ArrLength);
  for i := 0 to ArrLength-1 do
     DstArray^[i].Value := InputArray^[i].Value;

  ArrDst.Length^ := ArrLength;
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
    InputArray^[Ind].Value := StrToIntDef(UserInput, 0);
    InputArray^[Ind].Seen := False;
    writeln('Очередной эл массива: ', InputArray^[Ind].Value);
    Ind += 1;
    if Ind >= Length(InputArray^)-1 then
       SetLength(InputArray^, Length(InputArray^)*2);
  until False;

  DynArr.Length^ := Ind;
end;

{
 TopDownMerge(A[], iBegin, iMiddle, iEnd, B[])
{
    i = iBegin, j = iMiddle;

    // While there are elements in the left or right runs...
    for (k = iBegin; k < iEnd; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i];
            i = i + 1;
        } else {
            B[k] = A[j];
            j = j + 1;
        }
    }
}

}
procedure merge(ArrSrc: TDynArray; left, mid, right: integer; ArrDst: TDynArray);
var
     i, it, ite, temp : integer;
     ArrS, ArrD : TIntArrPntr;
begin
  writeln('Merge left: ', left, ' right: ', right, ' mid: ', mid);
  ArrS := ArrSrc.ArrPntr; ArrD := ArrDst.ArrPntr;
  i := left; it := mid;

  ite := left;
  for ite := left to right do
  begin
     sleep(1000);
     if ( i < mid ) and ( ( it > right ) or ( ArrS^[i].Value <= ArrS^[it].Value ) ) then
     begin
        writeln('True, ite:', ite,' i:', i, ' Value:', ArrS^[i].Value, ' it:', it, ' value:', ArrS^[it].Value);
        ArrD^[ite].Value := ArrS^[i].Value;
        i += 1;
     end
     else
     begin
        writeln('False, ite:', ite,' i:', i, ' Value:', ArrS^[i].Value, ' it:', it, ' value:', ArrS^[it].Value);
        ArrD^[ite].Value := ArrS^[it].Value;
        writeln('dst val', ArrD^[ite].Value);
        it += 1;
     end;
     print_array(ArrSrc);
     print_array(ArrDst);
  end;
end;

procedure merge_sort(ArrSrc: TDynArray; left, right: integer; ArrDst: TDynArray);
var
     mid : integer = 0;
     temp : integer;
     ArrS, ArrD : TIntArrPntr;
begin
  if (left = right) then
     begin
          writeln('Rec case: ', left, ' right: ', right);
          exit();
     end;
      begin
     writeln('left: ', left, ' right: ', right);
     mid := (left + right) div 2;
     merge_sort(ArrSrc, left, mid, ArrDst);
     merge_sort(ArrSrc, mid+1, right, ArrDst);
     merge(ArrSrc, left, mid+1, right, ArrDst);
  end;
end;

{Расчитываем получить множества ArrA и ArrB, содержащими только уникальные элементы. }
procedure get_symmetric_diff(ArrA: TDynArray; ArrB: TDynArray; ArrSymDiff: TDynArray);
var
   bigLength, smallLength, i, it, ite, el, flag: integer;
   bigArr, smallArr : TIntArrPntr;

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

  //Размер SymmDiff равен сумме длин исходных.
  setLength(ArrSymDiff.ArrPntr^, bigLength + smallLength);
  ArrSymDiff.Length^ := bigLength + smallLength;

{
  writeln('Массив перед операцией');
  print_array(ArrSymDiff);
}
  i := 0;
  ite := smallLength;
//Проход по бОльшему массиву. Каждая итерация содержит проход по меньшему массиву.
  while i < bigLength do
  begin
     el := bigArr^.[i].Value;

     //Сравниваем последний элемент с искомым только один раз за проход по меньшему массиву.
     if el = smallArr^[smallLength-1].Value then
        break;
     it := 0;
     while ( it < smallLength ) and ( el <> smallArr^[it].Value ) do
        it += 1;

     //Добавляем элемент в результат, если массив полностью пройден
     if it = smallLength then
     begin
        ArrSymDiff.ArrPntr^[ite].Value := el;
        ite += 1;
        ArrSymDiff.Length^ += 1;
     end;
     i += 1;
  end;

  writeln('Массив после операции');
  print_array(ArrSymDiff);

end;
{
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
}
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
   //array_input(DynArrB);

   if ( DynArrA.Length^ = 0 ) or ( DynArrB.Length^ = 0 ) then
   begin
      writeln('Задан пустой массив');
      Halt(1);
   end;


   print_array(DynArrA);
   //print_array(DynArrB);
   copy_array(DynArrA, DynArrC);
   //print_array(DynArrC);
   merge_sort(DynArrA, 0, DynArrA.Length^-1, DynArrC);
   //print_array(DynArrC);
   //get_args_merge(DynArrA, DynArrB, DynArrC);
   //writeln('Объединение массивов');
   //print_array(DynArrC);
   //get_args_interception(DynArrA, DynArrB, DynArrC);
   //writeln('Пересечение массивов');
   //print_array(DynArrC);

end.

