program dz_5_2;

uses
    SysUtils;

Type
  TIntArray = Array of integer;
  TDynArrRec = Record
    InputArray: TIntArray;
    Length: integer;
  end;

var
   i : integer;
   min,max,ArrLength : integer;
   InputArray: TIntArray;
   DynArrayRec: TDynArrRec;


function array_input(DynArrayRec: TDynArrRec) : TDynArrRec;
var
     UserInput: string;
     Ind : integer = 0;

begin
  writeln('Введите значения элементов массива(типа integer) , подтверждая ввод каждого нажатием Enter');
  writeln('Чтобы завершить ввод элементов, введите слово end');
  InputArray := DynArrayRec.InputArray;
  SetLength(InputArray, 2);

  repeat
    readln(UserInput);
    if UserInput = 'end' then
       //writeln('break');
       break;
    InputArray[Ind] := StrToIntDef(UserInput, 0);
    writeln('Очередной эл массива: ', InputArray[Ind]);
    Ind += 1;
    if Ind >= Length(InputArray)-1 then
       SetLength(InputArray, Length(InputArray)*2);
  until False;

  DynArrayRec.InputArray := InputArray;
  DynArrayRec.Length := Ind;
  Result := DynArrayRec;
end;

begin
 DynArrayRec := array_input(DynArrayRec);
 InputArray := DynArrayRec.InputArray;
 ArrLength := DynArrayRec.Length;
 min := InputArray[0];
 max := min;

 for i := Low(InputArray) to ArrLength-1 do
 begin
     if max < InputArray[i] then
        max := InputArray[i];
     if min > InputArray[i] then
        min := InputArray[i];
 end;

 writeln('Максимальное значение среди элементов массива равна: ', max);
 writeln('Минимальное значение среди элементов массива равна: ', min);

end.

