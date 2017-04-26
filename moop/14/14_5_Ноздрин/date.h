#ifndef HDATE

#define HDATE

static int DAYS[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

//
// Класс представления дня в форме месяц-день
//
class Date
{
    public:
        int _month;
        int _day;
        bool _failed;
        Date(int day, int month);
        Date();
        Date(const Date &date);
        void getDiff(const Date &date);
};

#endif
