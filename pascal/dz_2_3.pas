program dz_2_3;
uses SysUtils;
var
   deg_size: string;
   rad_size: real;

begin
   writeln('Enter an angle size in degrees.');
   readln(deg_size);
   rad_size := 3.14/180 * StrToFloat(deg_size);
   writeln('The anlge size in radians is: ', rad_size:4:2 );
end.

