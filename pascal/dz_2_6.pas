program dz_2_6;
var
  number: array [1..5] of char;
  i: integer;

begin
  writeln('Enter a number to display.');
  readln(number);
  for i := 1 to 5 do writeln(i, ' digit of a number is: ', number[i]);
end.

