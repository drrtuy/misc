program dz_8_2;

uses
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
    TExtreemsRec = record
      max: integer;
      maxPos: integer;
      min: integer;
      minPos: integer;
    end;

procedure array_input(DynArr: TDynArray);
var
     UserInput: string;
     Ind : integer = 0;
     InputArray: ^TIntArray;

begin
  writeln('Введите значения элементов массива(типа integer) , подтверждая ввод каждого нажатием Enter');
  writeln('Чтобы завершить ввод элементов, введите слово end');
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

function array_extreems(DynArr: TDynArray): TExtreemsRec;
var
     min, max, minPos, maxPos, i, curVal: integer;
     ExtreemRec: TExtreemsRec;
begin

  min := DynArr.ArrPntr^[0].Value; minPos := 0;
  max := min; maxPos := minPos;

  for i := 0 to DynArr.Length^-1 do
  begin
     curVal := DynArr.ArrPntr^[i].Value;
     if max < curVal then
     begin
        max := curVal;
        maxPos := i;
     end;
     if min > curVal then
     begin
        min := curVal;
        minPos := i;
     end;
  end;

  ExtreemRec.min := min; ExtreemRec.minPos := minPos;
  ExtreemRec.max := max; ExtreemRec.maxPos := maxPos;

  Result := ExtreemRec;
end;

procedure extreems_print(ExtreemRec: TExtreemsRec);
begin
   writeln('Значение минимального элемента массива: [', ExtreemRec.min,
   '] и его позиция: [', ExtreemRec.minPos, ']');
   writeln('Значение максимального элемента массива: [', ExtreemRec.max,
   '] и его позиция: [', ExtreemRec.maxPos, ']');
end;

var
   DynArrA: TDynArray;

begin
   new(DynArrA.ArrPntr);
   new(DynArrA.Length);
   DynArrA.Length^ := 0;

   array_input(DynArrA);

   if DynArrA.Length^ = 0 then
   begin
      writeln('Задан пустой массив');
      Halt(1);
   end;

   extreems_print(array_extreems(DynArrA));

end.

