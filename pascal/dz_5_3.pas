program dz_5_3;

uses
    SysUtils;

Type
  TIntArray = Array of integer;
  TDynArrRec = Record
    InputArray: TIntArray;
    Length: integer;
  end;

var
   i : integer;
   ArrLength : integer;
   InputArray: ^TIntArray;
   DynArrayRec: TDynArrRec;
   Target: integer;
   UserInput: string;

procedure print_array(DynArrayRec: TDynArrRec);
var
   ArrLength : integer;
   InputArray: TIntArray;
begin
  InputArray := DynArrayRec.InputArray;
  ArrLength := DynArrayRec.Length;

  for i := 0 to ArrLength-1 do
  begin
     writeln('Значение ', InputArray[i]);
  end;
end;

function array_input(DynArrayRec: TDynArrRec) : TDynArrRec;
var
     UserInput: string;
     Ind : integer = 0;

begin
  writeln('Введите значения элементов массива(типа integer) , подтверждая ввод каждого нажатием Enter');
  writeln('Чтобы завершить ввод элементов, введите слово end');
  InputArray := DynArrayRec.InputArray;
  SetLength(InputArray, 2);

  repeat
    readln(UserInput);
    if UserInput = 'end' then
       break;
    InputArray[Ind] := StrToIntDef(UserInput, 0);
    writeln('Очередной эл массива: ', InputArray[Ind]);
    Ind += 1;
    if Ind >= Length(InputArray)-1 then
       SetLength(InputArray, Length(InputArray)*2);
  until False;

  DynArrayRec.InputArray := InputArray;
  DynArrayRec.Length := Ind;
  Result := DynArrayRec;
end;

function binary_search(DynArrayRec: TDynArrRec; Target: integer) : boolean;
    var
         l, r, m: integer;
    function array_sort(DynArrayRec: TDynArrRec) : TDynArrRec; {Пузырьковая сортировка}
    var
       i, j, temp, ArrLength : integer;
       InputArray: TIntArray;

    begin
      InputArray := DynArrayRec.InputArray;
      ArrLength := DynArrayRec.Length;
      for i := ArrLength-1 downto 0 do
      begin
        for j := 1 to i do
            begin
                if (InputArray[j-1] > InputArray[j]) Then
                begin
                     temp := InputArray[j-1];
                     InputArray[j-1] := InputArray[j];
                     InputArray[j] := temp;
	        end;
              end;
      end;
      DynArrayRec.InputArray := InputArray;
      //print_array(DynArrayRec);
      Result := DynArrayRec;
    end;
{(0 + 3)  / 2 = 1

(1 + 3) / 2 = 2

(2 + 3) / 2 = 2

...

(2 + 3) / 2 = 2}
begin
  DynArrayRec := array_sort(DynArrayRec);
  r := DynArrayRec.Length - 1;
  l := 0;

  while r - l > 1 do
  begin
    m := (r + l) Div 2;
    writeln('m: ', m, ' l: ', l,' r: ', r);
    if DynArrayRec.InputArray[m] < Target then
       l := m
    else
       r := m
  end;
  if (DynArrayRec.InputArray[l] = Target) or (DynArrayRec.InputArray[r] = Target) then
     Result := True
  else
     Result := False
end;


begin
 DynArrayRec := array_input(DynArrayRec);
 writeln('Введите значения искомого элемента');
 readln(UserInput);
 Target := StrToIntDef(UserInput, 0);
 writeln('Ищем в массиве элемент равный: ', Target);

 InputArray := DynArrayRec.InputArray;
 ArrLength := DynArrayRec.Length;

 if binary_search(DynArrayRec, Target) = True then
    writeln('Элемент: [', Target, '] найден в массиве.')
 else
    writeln('Элемент: [', Target, '] НЕ найден в массиве.')

end.
