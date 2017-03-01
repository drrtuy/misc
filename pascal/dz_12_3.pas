program dz_12_3;
Uses
    sysutils,
    strutils;
Const
  BYTE_SIZE = 8;
Type
 TBytePtr = ^Byte;
var
 it, b: Integer;
 r: single;
 p: Pointer;

begin
 r := -10.0;
 p := @r;
 writeln(Format('Число %E', [r]));
 for it := SizeOf(Single)-1 downto 0 do
 begin
     b := TBytePtr(p+it)^;
     if it = 3 then
        writeln(Format('Номер байта: %d, назначение: знак+порядок, значение: %s',[ it, IntToBin(b, BYTE_SIZE) ]) );
     if it < 2  then
        writeln(Format('Номер байта: %d, назначение: мантисса, значение: %s', [ it, IntToBin(b, BYTE_SIZE) ]) );
     if it = 2  then
        writeln(Format('Номер байта: %d, назначение: порядок, значение: %s',[ it, IntToBin(b, BYTE_SIZE) ]) );

 end;
end.
