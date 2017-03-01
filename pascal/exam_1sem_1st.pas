program exam_1sem_1st;

Uses
    SysUtils;

Type
    TExtInt = record
      value: integer;
      visible: ^boolean; //флаг видимости/невидимости значения
    end;

    TIntArray = array of TExtInt;
    TIntArrPntr = ^TIntArray;
    TDynArray = record
      ArrPntr: TIntArrPntr;
      Length: ^integer;
    end;

procedure print_array(DynArr: TDynArray; mode: integer);
var
   ArrLength, i : integer;
   InputArray: ^TIntArray;
begin
  InputArray := DynArr.ArrPntr;
  ArrLength := DynArr.Length^;

  for i := 0 to ArrLength-1 do
  begin
     if mode = 1 then
        writeln('Значение ', InputArray^[i].value )
     else
       begin
          //writeln('Значение ', InputArray^[i].value );
          //writeln('Флаг ', InputArray^[i].visible^ );
          if InputArray^[i].visible^ = True then
             writeln('Значение ', InputArray^[i].value )
       end;
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
    InputArray^[Ind].value := StrToIntDef(UserInput, 0);
    new(InputArray^[Ind].visible);
    InputArray^[Ind].visible^ := True;
    writeln('Очередной эл массива: ', InputArray^[Ind].value);
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
    InputArray^[Ind].value  := Random(1000);
    new(InputArray^[Ind].visible);
    InputArray^[Ind].visible^ := True;
    Ind += 1;
  end;

  DynArr.Length^ := Ind;

  writeln('Сгенерирован массив');
  print_array(DynArr, 1);
end;

procedure array_swap_elements(DynArr: TDynArray; SrcInd, DstInd: integer);
var
   TempStor: integer;
begin
   TempStor := DynArr.ArrPntr^[SrcInd].value;
   DynArr.ArrPntr^[SrcInd].value := DynArr.ArrPntr^[DstInd].value;
   DynArr.ArrPntr^[DstInd].value := TempStor;
end;

{Сортировка выбором}
procedure array_selection_sort(DynArr: TDynArray);
  function find_max(DynArr: TDynArray; left: integer): integer;
  var
     max, i: integer;
     Arr: TIntArrPntr;
  begin
    Arr := DynArr.ArrPntr;
    max := left;
    for i := left to DynArr.Length^-1 do
       begin
        if Arr^[max].value < Arr^[i].value  then max := i;
       end;
    Result := max;
  end;

var
   i, j, ArrLength: integer;
   InputArray: ^TIntArray;
   ChunkMax: integer;
   begin
       InputArray := DynArr.ArrPntr;
       ArrLength := DynArr.Length^;

       for i:= 1 to ArrLength-1 do
       begin
          j := i - 1;
          ChunkMax := find_max(DynArr, j);
          array_swap_elements(DynArr, j, ChunkMax);
          while (j > 0) and (InputArray^[j].value  < ChunkMax) do
          begin
               array_swap_elements(DynArr, j, j-1);
               j -= 1;
	      end;

      end;
      //print_array(DynArr);

end;

//Проходим по сортированному массиву, отключая visibility у дублей.
procedure remove_doubles(DynArr: TDynArray);
var
   it, i: integer;
   cur, next: TExtInt;
begin
     i := 0;
     while i <= DynArr.Length^ - 2 do
     begin
          cur := DynArr.ArrPntr^[i];
          next := DynArr.ArrPntr^[i+1];
          while ( cur.value = next.value ) and ( i <= DynArr.Length^ - 2 ) do
          begin
                 next.visible^ := False;
                 //writeln(i, cur.value, next.value, cur.visible^);
                 i += 1;
                 cur := DynArr.ArrPntr^[i];
                 next := DynArr.ArrPntr^[i+1];
          end;

          //writeln(i, cur.value, next.value, ' ', next.visible^);
          i += 1;
     end;
end;

{
procedure print_result(DynArr: TDynArray);
begin
   writeln('Результат сортировки массива');
   print_array(DynArr, 1);
end;
}

procedure adv_print_result(DynArr: TDynArray);
begin
   writeln('Результат');
   print_array(DynArr, 2);
end;
var
   DynArr: TDynArray;

begin
   new(DynArr.ArrPntr);
   new(DynArr.Length);
   DynArr.Length^ := 0;

   //array_input(DynArr); //Годная функция для проверки кода.
   array_generate(DynArr);
   if DynArr.Length^ < 2 then
   begin
      writeln('Задан массив недостаточной длины');
      Halt(1);
   end;

   array_selection_sort(DynArr);
   remove_doubles(DynArr);
   adv_print_result(DynArr);

end.

