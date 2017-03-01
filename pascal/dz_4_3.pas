program dz_4_3;

uses
  SysUtils;
var
  input: string;
  digit: char;
  sum: integer = 0;

begin
  writeln('Введите число:');
  readln(input);
  for digit in input do
  begin
      sum += StrToIntDef(digit, 0);
  end;

  writeln('Сумма цифр числа: ', input, ' равна: ', sum);

end.

