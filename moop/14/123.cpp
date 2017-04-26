#include <iostream>
#include <clocale>
using namespace std;
// Виды исключений
enum TimeToSecEXvar { HOURNEGATIV, MINNEGATIV, HOUR24, MIN60 };
struct TimeToSecException // Тип исключений
{
TimeToSecEXvar exvar; // вид исключения
int incorrectValue; // неправильное значение
// Конструктор исключения типа TimeToSecException
TimeToSecException(TimeToSecEXvar _exvar, int _incorrectValue):
exvar(_exvar), incorrectValue(_incorrectValue) {}
};
int TimeToSec(int hour, int min)
{
// Проверка условий ----------------------
if (hour < 0 )
throw hour; // возбужение исключения типа int
//throw TimeToSecException(HOURNEGATIV, hour);
if (hour > 24 )
throw TimeToSecException(HOUR24, hour);
if (min < 0 )
throw TimeToSecException(MINNEGATIV, min);
if (min > 59 )
throw TimeToSecException(MIN60, min);
// Решение задачи -----------------------
int sec = (hour * 60 + min) * 60;
return sec;
}
int main()
{
setlocale(LC_CTYPE, "Russian");
int h, m;
int s;
met:
try {
cout << "Введите исходные данные:" << endl;
cout << "Часов = ";
cin >> h;
cout << "Минут = ";
cin >> m;
s = TimeToSec(h, m);
}
// Обработчик исключений типа TimeToSecException
catch ( TimeToSecException &except ) {

switch (except.exvar)
{
//case HOURNEGATIV: // Это исключение не возбуждается
// cout << "Отрицательные часы: " << except.incorrectValue << endl;
// break;
case MINNEGATIV:
cout << "Отрицательные минуты: " << except.incorrectValue << endl;
break;
case HOUR24:
cout << "Часов > 24: " << except.incorrectValue << endl;
break;
case MIN60:
cout << "Минут > 59: " << except.incorrectValue << endl;
break;
}
goto met;
}
// Обработчик исключений типа int
catch ( int negHour ) {
cout << "Отрицательные часы: " << negHour << endl;
goto met;
}
cout << h << ":" << m << " = " << s << " сек." << endl;
return 0;
}
