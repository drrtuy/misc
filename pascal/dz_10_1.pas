program dz_10_1;

Uses
    SysUtils;

Type
  TUserInp = Record
    A: integer;
    B: integer;
  end;

function GetRecNOD(A, B: integer): integer;
begin
  if B = 0 then
     begin
       Result := A;
       Exit();
     end;

  Result := GetRecNOD(B, A mod B);
end;

function GetIterNOD(A, B: integer): integer;
var
 temp: integer;
begin
  while B <> 0 do
  begin
    temp := B;
    B := A mod B;
    A := temp;
  end;
  Result := A;
end;

function GetUserInput(): TUserInp;
var
 UserInput: string;
begin
  writeln('Введите первое целое число');
  readln(UserInput);
  Result.A := StrToIntDef(UserInput, 0);
  writeln('Введите вторе целое число');
  readln(UserInput);
  Result.B := StrToIntDef(UserInput, 0);
  if Result.B = 0 then
     begin
       writeln('Второе число равно нулю!');
       Halt();
     end;
end;

procedure ResultPrint(NOD: integer);
begin
  writeln('НОД равен ', NOD);
end;

var
 UserInput: TUserInp;

begin
  UserInput := GetUserInput();
  ResultPrint(GetRecNOD(UserInput.A, UserInput.B));
  ResultPrint(GetIterNOD(UserInput.A, UserInput.B));

end.

