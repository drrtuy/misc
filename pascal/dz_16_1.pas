program dz_16_1;

Uses
    sysutils,
    math;

const
 pi = 3.1415926535897932384626433832795;

Function Factorial(n : Integer) : Integer;
Begin
    If n = 1 Then
        Result := 1
    Else
        Result := n*Factorial(n-1);
End;

function myCos(x:Real; n:integer): Real;
var
 i:Integer;
 s, z, x2, xi, ai, fi:Real;
begin

 while (x < 0) do
       x:= x + pi*2;
 while (x > pi) do
       x:= x - pi*2;

 s:=1;
 z := 1;
 xi := 1;
 x2 := x * x;
 fi := 1.0;
 for i:= 1 to n do
 begin
   z := -z;
   xi := xi * x2;
   fi:= fi * (2 * i - 1) * 2 * i;
   ai := (z * xi) / fi;
   s := s + ai;
   //writeln(Format('итеративное значение %.4F суммарное значение%.4F',[ ai, s ]));
 end;

 result := s;
end;

var
 arg : Real;
 TaylorRange : integer;

begin
 arg := 50;
 TaylorRange := 10;
 writeln('Длина ряда Тейлора ', TaylorRange);
 writeln(Format('Погрешность вычисления косинуса с пом. ряда Маклорена: %.5F',[cos(arg) - myCos(arg, TaylorRange)]));
 writeln(Format('Значение косинуса с пом. ряда Маклорена: %.5F',[ myCos(arg, TaylorRange)]));
 writeln(Format('Точное значение cos: %.4F', [cos(arg)]));
end.
