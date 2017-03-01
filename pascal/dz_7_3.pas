program dz_7_3;

uses
    RegExpr,
    SysUtils;
var
  Hay : string;
  RegexObj: TRegExpr;
  i : integer;

begin
  writeln('Введите строку, в которой ищем время.');
  readln(Hay);

  if Length(Hay) = 0 then
  begin
     writeln('Введена строка нулевой длины.');
     Halt();
  end;

  RegexObj := TRegExpr.Create;
  RegexObj.Expression := '(0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]';
  if RegexObj.Exec(Hay) then
  begin
     writeln('Нашли соответствие в строке:[', RegexObj.Match[0], ']');
     while RegexObj.ExecNext() do
        writeln('Нашли соответствие в строке:[', RegexObj.Match[0], ']');
  end;
  RegexObj.Free;

end.

