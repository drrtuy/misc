#ifndef HDECIMAL

#define MAX_LENGTH 255
#define Z '0'
#define BASE 10

//
// Класс для представления unsigned decimal чисел. Внутренее представление 
// строка цифр, младший разряд слева.
//
class Dec
{
    private:
        char * _digits;
        int _length;        
        bool _overflow;
        Dec _getLongest(const Dec &Operand);
        Dec _getShortest(const Dec &Operand);
        Dec *__getLongest(const Dec &Operand);
        Dec *__getShortest(const Dec &Operand);
        char *_reverseStr(const char *input);
    public:
        Dec();
        Dec(int length, const char *digits);
        explicit Dec(int length);
        Dec(const Dec &Operand);
        ~Dec();
        void Init(int length);
        void Create(int length, const char *digits);
        char *getDigits();
        bool getOverflow();
        int getLength();
        char *outPut();
        Dec *Add(const Dec &Operand);
        Dec *Dcr(const Dec &Operand);
        Dec *Mul(const Dec &Operand);
        Dec *Div(const Dec &Operand);
        bool GrThen(const Dec &Operand);
        bool LsThen(const Dec &Operand);
        bool Eq(const Dec &Operand);
};

#endif
