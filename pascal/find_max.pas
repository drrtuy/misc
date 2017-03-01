program find_max;
var
   inp: array [1..3] of integer;
   maxim: integer = 0;
   i: integer;

begin
  writeln('Enter three numbers. Hit enter after every input:');

  for i := 1 to 3 do
      begin
           readln(inp[i]);
      end;
  maxim := inp[1];
  for i := 2 to 3 do
      begin
           if maxim < inp[i] then maxim := inp[i];
      end;
  writeln('max(input) is:', maxim);
end.

