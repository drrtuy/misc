#ifndef HBITSTRING

//
// Класс поддерживает операции с битовыми строками: Or, And, Xor, Not. 
// Внутренее представление битовых строк - char* из символов '1' и '0'.
// Операции представляют собой проход по строкам с конца в начало и получение
// битовой строки в зависимости от значения разряда/-ов операнда/-ов.
// 

class BitString
{
    private: 
        char *_bits;
        int _length;
    public:
        BitString();
        BitString(const BitString &bs);
        explicit BitString(int length);
        BitString(int length, const char *bits);
        ~BitString();
        void init(int _length, const char *bitString);
        void create(int _length);
        char *outPut(const char *msg);
        void stdoutPut(const char *msg);
        BitString &operator=(const BitString &bitString);
        BitString &operator&(const BitString &bitString);
        BitString &operator|(const BitString &bitString);
        BitString &operator^(const BitString &bitString);
        BitString &operator!();
};

#endif
