#include <clocale>
#include "MultiFileProgram_3.h"

using namespace std;

word_numb_t *translate(int number);
word_numb_t *getOnesEndings(int number);
word_numb_t *getTensEndings(int number);
word_numb_t *getHundsEndings(int number);

int main() 
{
    int number = 0;
    word_numb_t *result;
    
    const string case_names[6] = {
        "Именительный: ",
        "Родительный: ",
        "Дательный: ",
        "Винительный: ",
        "Творительный: ",
        "Предложный: "
    };
   

    setlocale(LC_ALL, ""); 
    
    for(;;){
        cout << "Введите число от 1 до 9:" << endl;
        cin >> number;

        if ((number < 1) || (number >999)) {
            continue;
        }

        result = translate(number);

        for (int caseId = 0; caseId < CASE_NUMBER; caseId++) {
            cout << case_names[caseId] + result->cases[caseId] << endl;
        } 
        cout << endl;
    } 
    return 0;

}
