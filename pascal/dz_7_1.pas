program dz_7_1;

uses
    SysUtils;
var
  Needle,Hay, res : string;
  i, it: integer;
  n, h : char;
  inWord: boolean = False;

begin
  writeln('Введите строку, в которой будем искать.');
  readln(Hay);
  writeln('Введено:', Hay);
  writeln('Введите строку, которую будем искать.');
  readln(Needle);

  if ( Length(Hay) = 0 ) or ( Length(Needle) = 0 ) then
  begin
     writeln('Введена строка нулевой длины.');
     Halt();
  end;

  if Length(Hay) < Length(Needle) then
  begin
     writeln('Искомое больше чем строка для поиска');
     Halt();
  end;

  i := 1;
  while i <= Length(Hay) do
  begin
    it := 1;
    //Ищем подстроку начиная с этого места
    while ( Hay[i] = Needle[it] ) and ( ( i <= Length(Hay) ) or ( i <= Length(Needle) ) ) do
    begin
      //writeln('it:', it, ' i:', i, 'hay: ',Hay[i], ' needle: ',Needle[it]);
      it += 1; i += 1;
    end;

    if it = length(Needle)+1 then
    begin
       res := '';
       //writeln('break');
       break;
    end
    else
       res := 'не';

    //writeln('cont');
    i += 1;
  end;

  writeln('Слово: [', Needle, '] ', res,' найдено в слове [', Hay, '].');

end.

