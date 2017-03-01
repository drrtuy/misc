program dz_6__2;

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

  //ArrSymDiff.Length^ := bigLength + smallLength;

 {
  writeln('Массив перед операцией');
  print_array(ArrSymDiff);
  }
  i := 0;
  ite := 0;

//Проход по бОльшему массиву. Каждая итерация содержит проход по меньшему массиву.
  while i < bigLength do
  begin

     el := bigArr^.[i].Value;
     //Сравниваем последний элемент с искомым только один раз за проход по меньшему массиву.
     //if el = smallArr^[smallLength-1].Value then
     //   break;
     it := 0;
     while ( it < smallLength ) and ( el <> smallArr^[it].Value ) do
        it += 1;

     //Добавляем элемент в результат, если массив полностью пройден
     if it = smallLength then
     begin
        writeln('el: ', el);
        ArrSymDiff.ArrPntr^[ite].Value := el;
        ite += 1;
        ArrSymDiff.Length^ += 1;
     end
     else
     begin
        smallArr^[it].Seen := True;
     end;
     i += 1;
  end;

  //Проходим по меньшему массиву и добавляем в результат все элементы со снятым флагом Seen.
  for i := 0 to smallLength-1 do
  begin
     if smallArr^[i].Seen <> False then
        break;

     writeln('el из бОльшего: ', smallArr^[i].Value);
     ArrSymDiff.ArrPntr^[ite].Value := smallArr^[i].Value;
     ite += 1;
     ArrSymDiff.Length^ += 1;
  end;

  //writeln('Массив после операции');
  //print_array(ArrSymDiff);

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

   DynArrA.Length^ := 0;
   DynArrB.Length^ := 0;
   DynArrC.Length^ := 0;

   array_input(DynArrA);
   array_input(DynArrB);

   if ( DynArrA.Length^ = 0 ) or ( DynArrB.Length^ = 0 ) then
   begin
      writeln('Задан пустой массив');
      Halt(1);
   end;

   get_symmetric_diff(DynArrA, DynArrB, DynArrC);
   writeln('Sym diff массивов');
   print_array(DynArrC);

end.

