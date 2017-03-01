program dz_15_1;

Uses
    sysutils,
    strutils,
    math;

Const
    FIRST_TERM = -1;
    SUM_LIMIT = -2;
    MAX_SERIES_NUM = 10;

Type
    TSeries = Function ( x:Real; num:Integer ):Real;
    TTaskRec = Record
      FuncId: Integer;
      FuncName: String;
      TaylorRange: Integer;
      ArgValue: Real;
    end;
    TTaskResultRec = Record
      TaylRangeVal: Real;
      ExactFuncVal: Real;
      TaskRec: TTaskRec;
    end;
    TSeriesArrRec = Record
      series: array[1..MAX_SERIES_NUM] of TSeries;
      name: array[1..MAX_SERIES_NUM] of String;
    end;
    TSeriesArrPntr = ^TSeriesArrRec;

Function Factorial(n : Integer) : Integer;
Begin
  	If n = 1 Then
   		Result := 1
   	Else
   		Result := n*Factorial(n-1);
End;

Function expSeries( x:Real; num:Integer ):Real;

  Function firstTerm( x:Real ):Real;
  Begin
     firstTerm := 1;
  End;
  Function multTerm( x:Real; num:Integer ):Real;
  Begin
       multTerm:=x ** num/Factorial(num);
  End;
  Function sumLimit( x:Real ):Real;
  Begin
       sumLimit:=exp(x);
  End;

Begin
      Case num Of
        SUM_LIMIT: expSeries:=sumLimit(x);
        FIRST_TERM: expSeries:=firstTerm(x);
        Else expSeries := multTerm(x, num);
      End;
End;

 Function cosSeries( x:Real; num:Integer ):Real;
  Function firstTerm( x:Real ):Real;
  Begin
     firstTerm := 1;
  End;
  Function multTerm( x:Real; num:Integer ):Real;
  Begin
       multTerm:=(-1) ** num * x ** (2*num)/Factorial(2*num);
  End;
  Function sumLimit( x:Real ):Real;
  Begin
       sumLimit:=cos(x);
  End;

Begin
      Case num Of
        SUM_LIMIT: cosSeries := sumLimit(x);
        FIRST_TERM: cosSeries := firstTerm(x);
        Else cosSeries := multTerm(x, num);
      End;
 End;

Function sinSeries( x:Real; num:Integer ):Real;

  Function firstTerm( x:Real ):Real;
  Begin
     firstTerm := x;
  End;
  Function multTerm( x:Real; num:Integer ):Real;
  Begin
       multTerm:=(-1) ** num * x ** (2*num+1)/Factorial(2*num+1);
  End;
  Function sumLimit( x:Real ):Real;
  Begin
       sumLimit:=sin(x);
  End;

Begin
      Case num Of
        SUM_LIMIT: sinSeries:=sumLimit(x);
        FIRST_TERM: sinSeries:=firstTerm(x);
        Else sinSeries := multTerm(x, num);
      End;
End;

Procedure initSeries(SeriesRecs: TSeriesArrPntr);
var
   i: integer = 1;
Begin
     SeriesRecs^.series[i] := @sinSeries; {Оператор @ - особенность FPC}
     SeriesRecs^.name[i] := 'sin';
     i += 1;
     SeriesRecs^.series[i] := @cosSeries; {Оператор @ - особенность FPC}
     SeriesRecs^.name[i] := 'cos';
     i += 1;
     SeriesRecs^.series[i] := @expSeries; {Оператор @ - особенность FPC}
     SeriesRecs^.name[i] := 'exp';
     i += 1;
     while i <= MAX_SERIES_NUM do
     begin
        writeln(i);
        SeriesRecs^.name[i] := '';
        SeriesRecs^.series[i] := nil;
        i += 1;
     end;

End; {initSeries}


Function anySeries(TaskRecord: TTaskRec; SeriesRecs: TSeriesArrPntr): TTaskResultRec;
Var
   series: array[1..MAX_SERIES_NUM] of TSeries; {The evil}
   SerFunc: TSeries;
   i: integer;
   TaylValue: Real;
Begin
     series := SeriesRecs^.series;

     SerFunc := series[TaskRecord.FuncId];
     TaylValue := SerFunc(TaskRecord.ArgValue, FIRST_TERM);
     for i := 1 to TaskRecord.TaylorRange do
        begin
           //writeln('Итерация в anySeries ', i);
           TaylValue += SerFunc(TaskRecord.ArgValue, i);
           //writeln('Итерация в anySeries delta:', SerFunc(TaskRecord.ArgValue, i), ' абсолютное знач:', TaylValue );
        end;

     With result Do
     begin
          TaylRangeVal := TaylValue;
          ExactFuncVal := SerFunc(TaskRecord.ArgValue, SUM_LIMIT);
          TaskRec := TaskRecord;
     end;
End;

procedure drawMenu(SeriesRecs: TSeriesArrPntr);
var
   i: integer;
Begin
   writeln(Format('%50S',['Меню']));
   i := 1;
   writeln(Format('%10S',['Доступные функции']));
   while ( SeriesRecs^.name[i] <> '' ) and ( i <= MAX_SERIES_NUM ) do
   begin
        //writeln(i);
        writeln(Format('%d - %s',[i, SeriesRecs^.name[i]]));
        i += 1;
   end;
end;

procedure outputResult(TaskResultRec: TTaskResultRec);
var
   diff: Real;
begin
     writeln(Format('%50S',['Результат']));
     writeln('Выбранная функция: ', TaskResultRec.TaskRec.FuncName);
     writeln(Format('Аргумент: %.4F', [TaskResultRec.TaskRec.ArgValue]));
     writeln('Количество членов ряда: ', TaskResultRec.TaskRec.TaylorRange);
     writeln(Format('Приближённое значение: %.4F', [TaskResultRec.TaylRangeVal]));
     writeln(Format('Точное значение: %.4F', [TaskResultRec.ExactFuncVal]));
     diff := abs(TaskResultRec.ExactFuncVal - TaskResultRec.TaylRangeVal);
     writeln(Format('Погрешность вычеслений: %.4F', [diff]));
end;

Function getUserInput(SeriesRecs: TSeriesArrPntr): TTaskRec;
var
   TaskRec: TTaskRec;
   UserInput: String;
begin
     TaskRec.FuncId := -1;
     while ( TaskRec.FuncId < 1 ) or ( TaskRec.FuncId > MAX_SERIES_NUM ) do
     begin
       writeln('Выберите функцию из предложенных');
       readln(UserInput);
       TaskRec.FuncId := StrToIntDef(UserInput, -1);
     end;
     TaskRec.FuncName := SeriesRecs^.name[TaskRec.FuncId];
     writeln('Введите длину ряда(integer)');
     readln(UserInput);
     TaskRec.TaylorRange := StrToIntDef(UserInput, -1);
     writeln('Введите значение аргумента(real)');
     readln(UserInput);
     TaskRec.ArgValue := StrToFloatDef(UserInput, 0.0);
     result := TaskRec;
end;

Var
   SeriesRecs: TSeriesArrRec;
   result: TTaskResultRec;
   TaskRec: TTaskRec;

begin
     initSeries(@SeriesRecs);
     while True = True Do
        begin
           drawMenu(@SeriesRecs);
           TaskRec := getUserInput(@SeriesRecs);
           result:= anySeries(TaskRec, @SeriesRecs);
           outputResult(result);
        end;
end.
