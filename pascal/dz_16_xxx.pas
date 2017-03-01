program dz_16_xxx;
const
 pi = 3.1415926535897932384626433832795;
function mySin(x:Real; n:integer): Real;
var
 i, j:Integer;
 s, z, x2, xi, ai, fi:Real;
begin

 while (x < -pi*2) do
 x:= x + pi*2;
 while (x > pi*2) do
 x:= x - pi*2;

 s:=0;

 z:=-1;
 xi:= 1.0 / x;
 x2:= x*x;
 fi := 1.0;
 for i:= 1 to n do
 begin
 z:= -z;
 xi := xi * x2;

 ai := (z * xi) / fi;
 s := s + ai;

 fi:= fi * (i*2 + 0);
 fi:= fi * (i*2 + 1);
 end;
 mySin := s;
end;
begin
 writeln(sin(50) - mySin(50, 10));
end.
