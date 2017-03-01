program dz_10_3;

Uses
    SysUtils;

Type
    TIntArray = array of integer;
    TIntArrPntr = ^TIntArray;
    TDynArray = record
      ArrPntr: TIntArrPntr;
      Length: ^integer;
    end;

Const
  RANDOM_UPPER_LIMIT : integer = 1000;

procedure PrintArray(DynArr: TDynArray);
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

procedure GenerateArray(DynArr: TDynArray);
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
    InputArray^[Ind]  := Random(RANDOM_UPPER_LIMIT);
    Ind += 1;
  end;

  DynArr.Length^ := Ind;

  writeln('Сгенерирован массив');
  PrintArray(DynArr);
end;

procedure SwapElements(DynArr: TDynArray; SrcInd, DstInd: integer);
var
   TempStor: integer;
begin
   TempStor := DynArr.ArrPntr^[SrcInd];
   DynArr.ArrPntr^[SrcInd] := DynArr.ArrPntr^[DstInd];
   DynArr.ArrPntr^[DstInd] := TempStor;
   PrintArray(DynArr);
end;

{Рекурсивный quicksort}
procedure QuickRecSort(DynArr: TDynArray; l, r: integer);
var
   pivote, i, j: integer;
   InputArray: ^TIntArray;
   begin
        InputArray := DynArr.ArrPntr;
        pivote := InputArray^[( l + r ) div 2];
        i := l; j := r;
        writeln('pivot:',pivote, ' i: ', i, ' j: ',j);
        repeat
          while ( InputArray^[i] > pivote ) do inc(i);
          while ( InputArray^[j] < pivote ) do dec(j);
          writeln(' i ', i, ' j ', j);
          if ( i <= j ) then
          begin
             SwapElements(DynArr, i, j); inc(i); dec(j);
          end;
          writeln('after swap i: ', i, ' j: ',j);
        until i > j;

        if (l < j) then QuickRecSort(DynArr, l, j);
        if (r > i) then QuickRecSort(DynArr, i, r);

end;

{Итеративный quicksort}
procedure QuickIterSort(DynArr: TDynArray);
var
   pivot, i, j, StTop, l, r: integer;
   InputArray: ^TIntArray;
   Stack: TIntArray; {Массив для эмуляции стэка}
   begin
     l := 0; r:= DynArr.Length^-1;
     SetLength(Stack, DynArr.Length^);
     InputArray := DynArr.ArrPntr;
     StTop := 0;
     Stack[StTop] := l; inc(StTop); Stack[StTop] := r; //Пушим первое задание в стэк

     while StTop > 0 do
     begin
       writeln(StTop);
       r := Stack[StTop]; dec(StTop); l:= Stack[StTop]; //Вытаскиваем задание из стэка
       pivot := InputArray^[( l + r ) div 2];
       i := l; j := r;
       repeat
          while ( InputArray^[i] > pivot ) do inc(i);
          while ( InputArray^[j] < pivot ) do dec(j);
          if ( i <= j ) then
          begin
             SwapElements(DynArr, i, j); inc(i); dec(j);
          end;
       until i > j;
          PrintArray(DynArr);
       //Пушим задания в стэк по необходимости.
       if (l < j) then
       begin
          Stack[StTop] := l; inc(StTop); Stack[StTop] := j;
       end;
       if (r > i) then
       begin
          Stack[StTop] := i; inc(StTop); Stack[StTop] := r;
       end;
     end;

end;

procedure PrintResult(DynArr: TDynArray);
begin
   writeln('Результат сортировки массива');
   PrintArray(DynArr);
end;

var
   DynArr: TDynArray;

begin
   new(DynArr.ArrPntr);
   new(DynArr.Length);
   DynArr.Length^ := 0;

   GenerateArray(DynArr);

   if DynArr.Length^ < 2 then
   begin
      writeln('Задан массив недостаточной длины');
      Halt(1);
   end;

   //QuickRecSort(DynArr, 0, DynArr.Length^-1);
   QuickIterSort(DynArr);
   PrintResult(DynArr);

end.

