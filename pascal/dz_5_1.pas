program dz_5_1;

uses
    SysUtils;

Type
  TIntArray = Array of integer;

var
   i : integer;
   sum : integer = 0;
   InputArray: TIntArray;


function array_input(InputArray: TIntArray) : TIntArray;
var
     UserInput: string;
     Ind : integer = 1;
begin
  writeln('Введите значения элементов массива, подтверждая ввод каждого нажатием Enter');
  writeln('Чтобы завершить ввод элементов, введите слово end');
  SetLength(InputArray, 10);

  repeat
    readln(UserInput);
    InputArray[Ind] := StrToIntDef(UserInput, 0);
    Ind += 1;
    if Ind >= Length(InputArray)-2 then
       SetLength(InputArray, Length(InputArray)*2);
  until UserInput = 'end';

  Result := InputArray;
end;

begin
 InputArray := array_input(InputArray);

 for i := Low(InputArray) to High(InputArray) do
 begin
     sum += InputArray[i];
 end;

 writeln('Сумма элементов массива равна: ', sum);

end.

