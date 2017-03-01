program dz_2_5;
var
  a, b, c, d, x1, x2: real;

begin
  writeln('Enter the coefficients. Hit enter after each one:');
  readln(a);
  readln(b);
  readln(c);

  if a = 0 then
     begin
       writeln('This is not a quadratic equation.');
       Exit();
     end;
  d := b * b - 4 * a * c;

  if d >= 0 then
  begin
    if d <> 0 then
       begin
         x1 := (-b + sqrt(d)) / 2 * a;
         x2 := (-b - sqrt(d)) / 2 * a;
         writeln('x1 = ', x1:4:2, ', x2 = ', x2:4:2)
       end
    else
    begin
         x1 := -(b / (2 * a));
         writeln('x = ', x1:4:2)
    end
  end
  else
  begin
    writeln('No real solutions!');
  end

end.

