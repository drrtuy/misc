program dz_3_1;
uses SysUtils;
var
  a, b, c: string;
  h, k1, k2: integer;
  m, l, r: integer;


begin
     writeln('Enter a triangle side s length and hit enter after each.');
     readln(a);
     readln(b);
     readln(c);
     m := StrToIntDef(a, 0);
     l := StrToIntDef(b, 0);
     r := StrToIntDef(c, 0);
     if (m=0) or (l=0) or (r=0) then
     begin
        writeln('Wrong length was given');
        Exit();
     end;
     if (m+l<r) or (l+r<m) or (r+m<l) then
     begin
       writeln('A sum of two sides is bigger then a third.');
       Exit();
     end;
     if m>l then
     begin
       h := m;
       k1 := l;
     end
     else
     begin
       h := l;
       k1 := m;
     end;
     if r>h then
        begin k2 := h; h := r; end
     else
         k2 := r;
     writeln('h :', h, ' k1: ', k1, ' k2: ', k2);
     if (h*h>k1*k1+k2*k2) then
        writeln('The triangle is TUPOUGOLNIY.')
     else
         if (h*h=k1*k1+k2*k2) then
            writeln('The triangle is PRYAMOUGOLNIY.')
         else
            writeln('The triangle is OSTROUGOLNIY.');

end.

