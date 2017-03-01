program dz_12_2;
Uses
    SysUtils;
Type
 TBytePtr = ^Byte;
var
 i, it, sum: Integer;
 p: Pointer;

begin
 i := 65538;
 p := @i;
 sum := 0;
 for it := 0 to SizeOf(Integer)-1 do
 begin
     writeln('Byte number: ', it,' v:', TBytePtr(p+it)^);
     sum += TBytePtr(p+it)^;
 end;
 writeln(Format('Sum %d', [sum]));
end.
