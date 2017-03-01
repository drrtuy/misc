program dz_7_2;

uses
    SysUtils;
var
  Needle,Hay, res : string;
  i, it, size: integer;

begin
  writeln('Введите строку, которую перевернём.');
  readln(Hay);

  size := Length(Hay);

  if size = 0 then
  begin
     writeln('Введена строка нулевой длины.');
     Halt();
  end;
  SetLength(Needle,size);

  for i := size downto 1 do
    Needle[size-i+1] := Hay[i];

  writeln('Слово: [', Needle, '] ', res,' найдено в слове [', Hay, '].');

end.

