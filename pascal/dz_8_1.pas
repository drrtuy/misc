program dz_8_1;

uses
    SysUtils;

Type
    TArrElement = record
      Value: integer;
    end;
    TIntArray = array of TArrElement;
    TIntArrPntr = ^TIntArray;
    TDynArray = record
      ArrPntr: TIntArrPntr;
      Length: ^integer;
    end;

procedure sum_print(sum: integer);
begin
   writeln('Сумма элементов массива равна: ', sum);
end;

procedure array_input(DynArr: TDynArray);
var
     UserInput: string;
     Ind : integer = 0;
     InputArray: ^TIntArray;

begin
  writeln('Введите значения элементов массива(типа integer) , подтверждая ввод каждого нажатием Enter');
  writeln('Чтобы завершить ввод элементов, введите слово end');
  InputArray := DynArr.ArrPntr;
  SetLength(InputArray^, 2);

  repeat
    readln(UserInput);
    if UserInput = 'end' then
       break;
    InputArray^[Ind].Value := StrToIntDef(UserInput, 0);
    writeln('Очередной эл массива: ', InputArray^[Ind].Value);
    Ind += 1;
    if Ind >= Length(InputArray^)-1 then
       SetLength(InputArray^, Length(InputArray^)*2);
  until False;

  DynArr.Length^ := Ind;
end;

function array_sum(DynArr: TDynArray): integer;
var
     i, sum: integer;
begin
  sum := 0;
  for i := 0 to (DynArr.Length^-1) do
     sum += DynArr.ArrPntr^[i].Value;
  Result := sum;
end;

var
   DynArrA: TDynArray;

begin
   new(DynArrA.ArrPntr);
   new(DynArrA.Length);
   DynArrA.Length^ := 0;

   array_input(DynArrA);

   if DynArrA.Length^ = 0 then
   begin
      writeln('Задан пустой массив');
      Halt(1);
   end;

   sum_print(array_sum(DynArrA));

end.

