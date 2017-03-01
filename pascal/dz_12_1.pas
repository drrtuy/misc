program dz_12_1;
Uses
    SysUtils;
Type
 TBytePtr = ^Byte;
var
 i, it: Integer;
 p: Pointer;

begin
 i := 65537;
 p := @i;
 for it := 0 to SizeOf(Integer)-1 do
  writeln('Byte number: ', it,' v:', TBytePtr(p+it)^);

end.
