program dz_9_1;

Uses
    SysUtils;

Type
    TIntArray = array of integer;
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
     writeln('Значение ', InputArray^[i] );
  end;
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
    InputArray^[Ind]  := Random(1000);
    Ind += 1;
  end;

  DynArr.Length^ := Ind;

  writeln('Сгенерирован массив');
  print_array(DynArr);
end;

procedure array_swap_elements(DynArr: TDynArray; SrcInd, DstInd: integer);
var
   TempStor: integer;
begin
   TempStor := DynArr.ArrPntr^[SrcInd];
   DynArr.ArrPntr^[SrcInd] := DynArr.ArrPntr^[DstInd];
   DynArr.ArrPntr^[DstInd] := TempStor;
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
        if Arr^[max] < Arr^[i]  then max := i;
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
          while (j > 0) and (InputArray^[j]  < ChunkMax) do
          begin
               array_swap_elements(DynArr, j, j-1);
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

   array_generate(DynArr);

   if DynArr.Length^ < 2 then
   begin
      writeln('Задан массив недостаточной длины');
      Halt(1);
   end;

   array_selection_sort(DynArr);

   print_result(DynArr);

end.

