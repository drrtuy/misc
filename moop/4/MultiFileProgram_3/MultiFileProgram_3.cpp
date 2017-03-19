#include "MultiFileProgram_3.h"

//
//Функция склеивает результат склонения цифр разрядов по падежам.
// 
//
//arg1 int
//
//out struct word_numb_t
//
word_numb_t *translate(int number)
{
    word_numb_t *result, *ones, *tens, *hunds;
    result = new word_numb_t;
    int divBy100Remind;

    divBy100Remind = number % 100;
       
    ones = getOnesEndings(number);

    if ( number / 10 >= 1 ) {
        tens = getTensEndings(number);
        if ( number / 10 >= 10 ) {
            hunds = getHundsEndings(number);
        }
    }


    for (int caseId = 0; caseId < CASE_NUMBER; caseId++) {
        if (number / 10 >= 10 ) { //3 цифры

            if ((divBy100Remind) >= 11 && (divBy100Remind <= 19)) {
                result->cases[caseId] = hunds->cases[caseId] + " " +\
tens->cases[caseId];
            } else {
                result->cases[caseId] = hunds->cases[caseId] + " " +\
tens->cases[caseId] + " " + ones->cases[caseId];
            } //конец блока, описывающего число из 3х цифр 

        } else if (number / 10 >= 1) { //2 цифры

            if ((number >= 11) && (number <= 19)) { //числа от 11 до 19
                result->cases[caseId] = tens->cases[caseId];
            } else { //числа от 1 до 10 и и от 20 до 99
            result->cases[caseId] = tens->cases[caseId] + " " +\
 ones->cases[caseId];            
            } //конец блока, описывающего число из 2х цифр 

        } else { //1 цифра
            result->cases[caseId] = ones->cases[caseId];
        }
    } 


    return result;
}

//
//Функция заполняет word_num_t нужными окончаниями для буквенного представления
//разряда единиц в числе. 
//
//arg1 int
//
//out struct word_numb_t
//
word_numb_t *getOnesEndings(int number)
{
    int ones;
    word_numb_t *result;
    string base;
    result = new word_numb_t;
    const string bases[10] = {
        " ",
        " ",
        "дв",
        "тр",
        "четыр",
        "пят",
        "шест",
        "сем",
        "восем",
        "девят"
    };

    ones = number % 10;
    result->base = base = bases[ones];
    switch (ones) {
    case 1: 
        result->cases[0] = "один";
        result->cases[1] = "одного";
        result->cases[2] = "одному";
        result->cases[3] = "один";
        result->cases[4] = "одним";
        result->cases[5] = "одном";
        break;
    case 2:
        result->cases[0] = base + "а";
        result->cases[1] = base + "ух";
        result->cases[2] = base + "ум";
        result->cases[3] = base + "а";
        result->cases[4] = base + "умя";
        result->cases[5] = base + "ух";
        break;
    }

    if ((ones == 3) || (ones == 4)) {
        result->cases[0] = base + "и";
        result->cases[1] = base + "ех";
        result->cases[2] = base + "ем";
        result->cases[3] = base + "и";
        result->cases[4] = base + "емя";
        result->cases[5] = base + "ех";
    }

    if (ones >= 5) {
        result->cases[0] = base + "ь";
        result->cases[1] = base + "и";
        result->cases[2] = base + "и";
        result->cases[3] = base + "ь";
        result->cases[4] = base + "ью";
        result->cases[5] = base + "и";
    }

    return result;
}

//
//Функция заполняет word_num_t нужными окончаниями для буквенного представления
//разряда десятков в числе. 
//
//arg1 int
//
//out struct word_numb_t
word_numb_t *getTensEndings(int number)
{
    int tens;
    word_numb_t *result;
    string base;
    result = new word_numb_t;

    string bases[10] = {
        " ",
        "одиннадацат",
        "двадцат",
        "тридцат",
        "сорок",
        "пят",
        "шест",
        "сем",
        "восем",
        "девяност"
    };

    switch (number % 100) {
    case 12:
        bases[1] = "двенадцат"; break;
    case 13:
        bases[1] = "тринадцат"; break;
    case 14:
        bases[1] = "четырнадцат"; break;
    case 15:
        bases[1] = "пятнадцат"; break;
    case 16:
        bases[1] = "шестнадцат"; break;
    case 17:
        bases[1] = "семнадцат"; break;
    case 18:
        bases[1] = "восемнадцат"; break;
    case 19:
        bases[1] = "девятнадцат"; break;
    }

    tens = (number / 10) % 10;
    result->base = base = bases[tens];

    switch (tens) {
    case 1: 
        result->cases[0] = base + "ь";
        result->cases[1] = base + "и";
        result->cases[2] = base + "и";
        result->cases[3] = base + "ь";
        result->cases[4] = base + "ью";
        result->cases[5] = base + "и";
        break;
    case 4:
        result->cases[0] = base + " ";
        result->cases[1] = base + "а";
        result->cases[2] = base + "а";
        result->cases[3] = base + " ";
        result->cases[4] = base + "а";
        result->cases[5] = base + "а";
        break;
    case 9:
        result->cases[0] = base + "о";
        result->cases[1] = base + "а";
        result->cases[2] = base + "а";
        result->cases[3] = base + "о";
        result->cases[4] = base + "о";
        result->cases[5] = base + "о";
        break;
    }
        

    if ((tens == 2) || (tens == 3)) {
        result->cases[0] = base + "ь";
        result->cases[1] = base + "и";
        result->cases[2] = base + "и";
        result->cases[3] = base + "ь";
        result->cases[4] = base + "ью";
        result->cases[5] = base + "и";
    }

    if ((tens >= 5) && (tens < 9)) {
        result->cases[0] = base + "ьдесят";
        result->cases[1] = base + "идесяти";
        result->cases[2] = base + "идесяти";
        result->cases[3] = base + "ьдесят";
        result->cases[4] = base + "идесятью";
        result->cases[5] = base + "идесяти";
    }

    return result;
}

//
//Функция заполняет word_num_t нужными окончаниями для буквенного представления
//разряда сотен в числе. 
//
//arg1 int
//
//out struct word_numb_t
//
word_numb_t *getHundsEndings(int number)
{
    word_numb_t *result;
    result = new word_numb_t;
    int hunds;
    string base;

    string bases[10] = {
        " ",
        "ст",
        "дв",
        "тр",
        "четыр",
        "пят",
        "шест",
        "сем",
        "восем",
        "девят"
    };

    hunds = number / 100;
    result->base = base = bases[hunds];


    switch (hunds) {
    case 1: 
        result->cases[0] = base + "о";
        result->cases[1] = base + "a";
        result->cases[2] = base + "а";
        result->cases[3] = base + "о";
        result->cases[4] = base + "а";
        result->cases[5] = base + "а";
        break;
    case 2:
        result->cases[0] = base + "ести";
        result->cases[1] = base + "ухсот";
        result->cases[2] = base + "ухстам";
        result->cases[3] = base + "ести";
        result->cases[4] = base + "ухстами";
        result->cases[5] = base + "ухстах";
        break;
    case 3:
        result->cases[0] = base + "иста";
        result->cases[1] = base + "ехсот";
        result->cases[2] = base + "ехстам";
        result->cases[3] = base + "иста";
        result->cases[4] = base + "емстами";
        result->cases[5] = base + "ехстах";
        break;
    case 4:
        result->cases[0] = base + "еста";
        result->cases[1] = base + "ехсот";
        result->cases[2] = base + "емстам";
        result->cases[3] = base + "еста";
        result->cases[4] = base + "емстами";
        result->cases[5] = base + "ехстах";
        break;
    }
        
    if (hunds >= 5) {
        result->cases[0] = base + "ьсот";
        result->cases[1] = base + "иста";
        result->cases[2] = base + "истам";
        result->cases[3] = base + "ьсот";
        result->cases[4] = base + "ьюстами";
        result->cases[5] = base + "ьюстах";
    }

    return result;
}

