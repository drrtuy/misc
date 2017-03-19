#ifndef FUNCTIONS
#define FUNCTIONS

#define CASE_NUMBER 6

#include <iostream>

using std::string;

//Структура для представления склонения числительных по падежам.
typedef struct {
    int     number;
    string cases[6]; //окончание для цифры разряда в различных падежах.
    string base; //неизменная основа слова.
}   word_numb_t;
    
word_numb_t *translate(int number);
word_numb_t *getOnesEndings(int number);
word_numb_t *getTensEndings(int number);
word_numb_t *getHundsEndings(int number);

#endif
