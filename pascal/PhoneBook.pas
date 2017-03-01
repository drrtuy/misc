program PhoneBook;

Uses
    //strutils,
    sysutils;

Const
     MAX_PHONES = 10;
     INIT_RECS = 10;
     MAX_ACTS = 6;
     INVALID_INPUT = -1;
     SAVEFILEPATH = '/Users/drrtuy/.phonebook';

Type
      TString = array [1..255] of char;
      TPhoneRec = record
        name: TString;
        numbers: array [1..MAX_PHONES] of TString;
      end;
      TPhoneRecPntr = ^TPhoneRec;
      TPhoneStore = file of TPhoneRec;
      TPhoneRecList = array of TPhoneRec;
      TPhoneRecListPntr = ^TPhoneRecList;
      TPhoneBook = record
        storeName: string;
        emptyIdx: integer;
        recs: TPhoneRecListPntr;
      end;
      TPBPntr = ^TPhoneBook;
      TAct = Function( PhoneBook: TPBPntr): integer;
      TActRec = record
        id: integer;
        name: pchar;
        func: TAct;
      end;
      TActList = array [1..MAX_ACTS] of TActRec;
      TActListPntr = ^TActList;

function SavePhoneBook(PhoneBook: TPBPntr): integer;
var
  storage: TPhoneStore;
  rec: TPhoneRec;
  i: integer = 0;
begin
  result := 0;
  {$I-}
  AssignFile(storage, SAVEFILEPATH);
  Rewrite(storage);
  for rec in PhoneBook^.recs^ do
  begin
      if rec.name[1] <> char(0) then
         begin
              write(storage, rec);
              i += 1;
         end;
  end;
  {$I+}
  if IOResult <> 0 then
     writeln('Ошибка записи на диск.')
  else
     begin
          writeln(Format('На диске %d записей', [ i ]));
          result := 1;
     end;
end;

function loadPhoneBook(): TPBPntr;
var
    PB: TPBPntr;
    storage: TPhoneStore;
    i: integer = 1;
begin
  new(PB);
  new(PB^.recs);
  SetLength(PB^.recs^, INIT_RECS);
  PB^.emptyIdx := 1;
  {$I-}
  AssignFile(storage, SAVEFILEPATH);
  Reset(storage);
  while not eof(storage) do
  begin
      read(storage, PB^.recs^[i]);
      i += 1;
  end;
  {$I+}

  result := PB;
end;

function findNextEmpty(PhoneBook: TPBPntr): integer;
begin
  result := PhoneBook^.emptyIdx + 1;
end;

function addRecord(PhoneBook: TPBPntr): integer;
var
  rec : TPhoneRecPntr;
begin
  result := 0;
  rec := @PhoneBook^.recs^[1];
  with rec^ do
  begin
    name := 'Ro';
    numbers[1] := '79062171326';
  end;
  PhoneBook^.emptyIdx := findNextEmpty(PhoneBook);
  //writeln(PhoneBook^.emptyIdx);
  SavePhoneBook(PhoneBook);
  result := 1;
end;

function listPB(PhoneBook: TPBPntr): integer;
var
  rec : TPhoneRec;
  number: string;
begin
  for rec in PhoneBook^.recs^ do
  begin
      if rec.name[1] = char(0) then
         continue;
      writeln(rec.name);

      for number in rec.numbers do
          begin
              if number[1] <> char(0) then
                 writeln(Format('%30s', [number]));
          end;
  end;

  result := 1;
end;

function changeRecord(PhoneBook: TPBPntr): integer;
begin
  result := 1;
end;

function cmpString(A: array of char; B: string): integer;
var
  i: integer = 0;
begin
     //writeln(length(B), A[0], B[1], A[1], B[2]);
     while ( i <= length(B) - 1 ) and ( A[i] = B[i+1] ) do
     begin
          i += 1;
     end;
     if i = length(B) then
        result := 1
     else
        result := 0;
end;

function findRecord(PhoneBook: TPBPntr): integer;
var
  uInp: string;
  rec: TPhoneRecPntr;
  idx: integer = 1;
begin
  result := 0;
  writeln('Введите имя или номер телефона');
  readln(uInp);
  for idx:= 1 to Length(PhoneBook^.recs^) do
  begin
      rec := @PhoneBook^.recs^[idx];
      //writeln(rec^.name, uInp);
      if cmpString(rec^.name, uInp) = 1 then
         begin
           //writeln(AnsiUpperCase(rec^.name));
           result := idx;
           break;
         end;
  end;
end;

function showRecord(PhoneBook: TPBPntr): integer;
var
  recIdx: integer;
  rec: TPhoneRecPntr;
  number: string;
begin
  recIdx := findRecord(PhoneBook);
  if ( recIdx > 0 ) and ( recIdx < Length(PhoneBook^.recs^) ) then
     begin
      rec := @PhoneBook^.recs^[recIdx];
      writeln(rec^.name);
      for number in rec^.numbers do
          begin
              if number[1] <> char(0) then
                 writeln(Format('%20s', [number]));
          end;
     end;
  result := 1;

end;

function delRecord(PhoneBook: TPBPntr): integer;
var
  recIdx, i: integer;
  rec: TPhoneRecPntr;
begin
  result := 0;
  recIdx := findRecord(PhoneBook);
  if ( recIdx > 0 ) and ( recIdx < Length(PhoneBook^.recs^) ) then
     begin
          rec := @PhoneBook^.recs^[recIdx];
          rec^.name := '';
          for i:= 1 to Length(rec^.numbers) do
              rec^.numbers[i] := '';
          PhoneBook^.emptyIdx := recIdx;
     end;
  SavePhoneBook(PhoneBook);
  result := 1;
end;

function stopIt(PhoneBook: TPBPntr): integer;
begin
  Halt(0);
  result := 1;
end;

function getActList(): TActListPntr;
begin
  new(result);
  with result^[1] do
  begin
    id := 1;
    name := 'Добавить';
    func := @addRecord;
  end;
  with result^[2] do
  begin
    id := 2;
    name := 'Изменить';
    func := @changeRecord;
  end;
  with result^[3] do
  begin
    id := 3;
    name := 'Удалить';
    func := @delRecord;
  end;
  with result^[4] do
  begin
    id := 4;
    name := 'Найти';
    func := @showRecord;
  end;
  with result^[5] do
  begin
    id := 5;
    name := 'Пролистать';
    func := @listPB;
  end;
    with result^[MAX_ACTS] do
  begin
    id := MAX_ACTS;
    name := 'Выйти';
    func := @stopIt;
  end;
end;

procedure drawMenu(Actions: TActListPntr);
var
  a: TActRec;
begin
  for a in Actions^ do
      with a do
      begin
        writeln(Format('%d) %s', [id, name]));
      end;
end;

var
  actList: TActListPntr;
  uInp: string;
  PB: TPBPntr;
  func: TAct;
begin
  actList := getActList();
  PB := loadPhoneBook();

  while True = True do  //главное меню
  begin
        drawMenu(actList);
        readln(uInp);
        if (StrToIntDef(uInp, INVALID_INPUT) < 0) or (StrToIntDef(uInp, INVALID_INPUT) > MAX_ACTS) then
           continue;
        func := actList^[StrToIntDef(uInp, MAX_ACTS)].func;
        func(PB);
  end;

end.

