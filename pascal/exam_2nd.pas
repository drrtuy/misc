program exam_2nd;

uses
    RegExpr,
    SysUtils;
var
  Hay : string;
  RegexObj: TRegExpr;
  i : integer;

Type
    TStringPntr = ^string;
    TStringArr = array of string;
    TStringArrPntr = ^TStringArr;

function get_user_input(): TstringPntr;
var
  Hay: string;
begin
   writeln('Введите строку, в которой ищем время.');
   readln(Hay);
   result := @Hay;
end;

function split(uInp: ^string): TStringArrPntr;
var
  words: TStringArr;
begin
   words:
end;

begin


end.
