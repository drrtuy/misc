#ifndef HCLOCK

#define HCLOCK

//
// Класс представления момента времени в форме часы:минуты
//
class Clock
{
    public:
        int _minutes;
        int _hours;
        bool _failed;
        Clock(int minutes, int hours);
        Clock();
        Clock(const Clock &cl);
        void getDiff(const Clock &cl);
};

#endif
