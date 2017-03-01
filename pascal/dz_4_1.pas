program dz_4_1;
uses SysUtils;
var
  a, b, r: integer;
  inp_a, inp_b: string;

begin
  writeln('Введите два целых числа и нажмите enter после ввода каждого из них.');
  readln(inp_a);
  readln(inp_b);
  a := StrToIntDef(inp_a, 0);
  b := StrToIntDef(inp_b, 0);

  if (a = 0) or (b = 0) then
  begin
    writeln('Введены некорректные данные.');
    Exit();
  end;

  repeat
    r := a Mod b;
    a := b; b := r;
  until r = 0;

  writeln('НОД(', inp_a, ',', inp_b,')=', a);

end.

