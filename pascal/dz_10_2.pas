program dz_10_2;

Uses
    SysUtils;

function GetRecFib(Iter, Fib1, Fib2: integer): integer;
begin
  if Iter = 0 then
     begin
       Result := Fib2;
       Exit();
     end;

  Result := GetRecFib(Iter-1, Fib2, Fib1+Fib2);
end;

function GetIterFib(Iter: integer): integer;
var
 Fib1, Fib2, temp: integer;
begin
  Fib1 := 1;
  Fib2 := 1;
  while Iter > 0 do
  begin
    temp:= Fib2;
    Fib2 := Fib1 + Fib2;
    Fib1 := temp;
    Iter -= 1;
  end;
  Result := Fib2;
end;

function GetUserInput(): integer;
var
 UserInput: string;
begin
  writeln('Введите кол-во итераций');
  readln(UserInput);
  Result := StrToIntDef(UserInput, 0);
end;

procedure ResultPrint(Fib: integer);
begin
  writeln('Число Фибоначчи равно ', Fib);
end;

var
 UserInput: integer;

begin
  UserInput := GetUserInput();
  ResultPrint(GetRecFib(UserInput, 1, 1));
  ResultPrint(GetIterFib(UserInput));

end.

