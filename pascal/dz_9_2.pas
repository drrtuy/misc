program dz_9_2;

Uses
    SysUtils;

Type
    TArrElement = record
      Value: integer;
    end;
    TIntArray = array of TArrElement;
    TIntArrPntr = ^TIntArray;
    TDynArray = record
      ArrPntr: TIntArrPntr;
      Length: ^integer;
    end;


procedure print_array(DynArr: TDynArray);
var
   ArrLength, i : integer;
   InputArray: ^TIntArray;
begin
  InputArray := DynArr.ArrPntr;
  ArrLength := DynArr.Length^;

  for i := 0 to ArrLength-1 do
  begin
     writeln('Значение ', InputArray^[i].Value);
  end;
end;

procedure array_input(DynArr: TDynArray);
var
     UserInput: string;
     Ind : integer = 0;
     InputArray: ^TIntArray;

begin
  writeln('Введите значения элементов массива(типа integer) , подтверждая ввод каждого нажатием Enter');
  writeln('Чтобы завершить ввод элементов, введите слово end');
  writeln('!!! Обратите внимание, что ,по определению, множество не может содержать одинаковых элементов!!!');
  InputArray := DynArr.ArrPntr;
  SetLength(InputArray^, 2);

  repeat
    readln(UserInput);
    if UserInput = 'end' then
       break;
    InputArray^[Ind].Value := StrToIntDef(UserInput, 0);
    writeln('Очередной эл массива: ', InputArray^[Ind].Value);
    Ind += 1;
    if Ind >= Length(InputArray^)-1 then
       SetLength(InputArray^, Length(InputArray^)*2);
  until False;

  DynArr.Length^ := Ind;
end;

procedure array_generate(DynArr: TDynArray);
var
     UserInput: string;
     Ind : integer = 0;
     InputArray: ^TIntArray;
     ArrLength: integer = 0;

begin
  writeln('Введите длину массива(типа integer).');
  readln(UserInput);
  ArrLength := StrToIntDef(UserInput, -1);
  if ArrLength < 1 then
     Exit();

  Randomize;
  InputArray := DynArr.ArrPntr;
  SetLength(InputArray^, ArrLength);

  while Ind < ArrLength do
  begin
    InputArray^[Ind].Value := Random(1000);
    Ind += 1;
  end;

  DynArr.Length^ := Ind;

  writeln('Сгенерирован массив');
  print_array(DynArr);
end;

{Сортировка простыми вставками}
procedure array_insert_sort(DynArr: TDynArray);
var
   i, j, temp, ArrLength, elem: integer;
   InputArray: ^TIntArray;

   begin
      InputArray := DynArr.ArrPntr;
      ArrLength := DynArr.Length^;
      for i := 1 to ArrLength-1 do
      begin
        elem := InputArray^[i].Value;
        j := i - 1;
        while j >= 0 do
            begin
                if (InputArray^[j].Value < elem) Then
                begin
                     temp := InputArray^[j].Value;
                     InputArray^[j].Value := InputArray^[j+1].Value;
                     InputArray^[j+1].Value := temp;
	            end;
                j -= 1;
            end;
      end;
      //print_array(DynArr);
   end;

procedure print_result(DynArr: TDynArray);
begin
   writeln('Результат сортировки массива');
   print_array(DynArr);
end;

var
   DynArr: TDynArray;

begin
   new(DynArr.ArrPntr);
   new(DynArr.Length);
   DynArr.Length^ := 0;

   //array_input(DynArr);
   array_generate(DynArr);

   if DynArr.Length^ = 0 then
   begin
      writeln('Задан пустой массив');
      Halt(1);
   end;

   array_insert_sort(DynArr);

   print_result(DynArr);

end.

