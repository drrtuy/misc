program dz_8_5;

Uses
    SysUtils;

Type
    TIntPntr = ^integer;
    TArrElement = record
      Value: integer;
    end;
    TIntArray = array of TArrElement;
    TIntArrPntr = ^TIntArray;
    TDynArray = record
      ArrPntr: TIntArrPntr;
      Length: ^integer;
    end;

procedure binsearch_input(DynArr: TDynArray; Target: TIntPntr);
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

  writeln('Введите число для поиска в массиве.');
  readln(UserInput);
  Target^ := StrToIntDef(UserInput, 0);
  writeln('Введено число:[', Target^, ']');
end;

{Пузырьковая сортировка}
procedure array_sort(DynArr: TDynArray);
var
   i, j, temp, ArrLength : integer;
   InputArray: ^TIntArray;

   begin
      InputArray := DynArr.ArrPntr;
      ArrLength := DynArr.Length^;
      for i := ArrLength-1 downto 0 do
      begin
        for j := 1 to i do
            begin
                if (InputArray^[j-1].Value > InputArray^[j].Value) Then
                begin
                     temp := InputArray^[j-1].Value;
                     InputArray^[j-1].Value := InputArray^[j].Value;
                     InputArray^[j].Value := temp;
	            end;
            end;
      end;
      //print_array(DynArr);
   end;

function binary_search(DynArrayRec: TDynArray; Target: TIntPntr): integer;
var
   l, r, m: integer;
begin
    array_sort(DynArrayRec);
    r := DynArrayRec.Length^ - 1;
    l := 0;
    Result := -1;

    while r - l > 1 do
    begin
      m := (r + l) Div 2;
      writeln('m: ', m, ' l: ', l,' r: ', r);
      if DynArrayRec.ArrPntr^[m].Value < Target^ then
         l := m
      else
         r := m
    end;

    if DynArrayRec.ArrPntr^[l].Value = Target^ then
       Result := l;

    if DynArrayRec.ArrPntr^[r].Value = Target^ then
       Result := r;

end;

procedure binsearch_print( pos: integer; Target: TIntPntr);
begin
  if pos < 0 then
     writeln('Элемент [', Target^, '] не найден')
  else
     writeln('Элемент [', Target^, '] найден в массиве на [', pos, '] месте.' );
end;

var
   DynArrA: TDynArray;
   Target: TIntPntr;

begin
   new(DynArrA.ArrPntr);
   new(DynArrA.Length);
   new(Target);
   DynArrA.Length^ := 0;

   binsearch_input(DynArrA, Target);

   if DynArrA.Length^ = 0 then
   begin
      writeln('Задан пустой массив');
      Halt(1);
   end;

   binsearch_print( binary_search(DynArrA, Target), Target );

end.

