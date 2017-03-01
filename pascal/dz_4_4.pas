program dz_4_4;

uses
    SysUtils;

var
  input: string;
  sum: integer;
  i: integer = 0;

function digits_sum(number: integer) : integer;
begin
    Result:=(number Div 100)+((number Mod 100) Div 10)+(number mod 10);
end;

begin
  writeln('Введите число N, 0 < N < 27.');
  readln(input);
  sum := StrToIntDef(input, 0);

  repeat
    if ( digits_sum(i) = sum ) then
       writeln('Сумма цифр числа ', i, ' равна ', sum);
    i += 1;
  until i > 999;
end.

