#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define BUF_LEN 2097152
#define SM_BUF 256

char number_buffer_[SM_BUF];

enum OPTS { STDOUT, STRING };

int counter = 0;
int size_gl = 0;
long long int* int_pnt;

char digit_tens_[] = {
        48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
        49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
        50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
        51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
        52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
        53, 53, 53, 53, 53, 53, 53, 53, 53, 53,
        54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
        55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
        56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
        57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
};

char digit_ones_[] = {
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
};


char* arr_output(long long int* int_arr, int size, enum OPTS opt);
void qsort_(long long int* int_arr, int left, int right, FILE* output);

int main(int argc, char** argv)
{
    char* numbers_curs;
    char* sorted_arr_str;

    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");
    if (!input || !output)
        return 1;

    number_buffer_[SM_BUF - 1] = '\0';
    
    char size_str[SM_BUF];
    int size = 0;
    
    numbers_curs = fgets(size_str, SM_BUF, input);
    sscanf(size_str, "%d", &size);


    char numbers_str[BUF_LEN];
    long long int numbers[size];
    int_pnt = numbers;
    size_gl = size;
    memset((void *)numbers, 0, size * sizeof(long long int));
    //memset(numbers_str, 0x20, BUF_LEN);

    numbers_curs = fgets(numbers_str, BUF_LEN, input);
    numbers_curs = numbers_str;
    for(int i = 0; i < size; i++)
    {
        numbers[i] = i + 1;
        sscanf(numbers_curs, "%lld", &numbers[i]);
        while(*numbers_curs != ' ')
            numbers_curs++;
        while(*numbers_curs == ' ')
        {   
            numbers_curs++;
        }
    }

    //arr_output(numbers, size, STDOUT);
    qsort_(numbers, 0, size - 1, output);
    
    sorted_arr_str = arr_output(numbers, size, STRING);

    fputs(sorted_arr_str, output);
    fputs("\n", output);

    free(sorted_arr_str);

    fclose(input);
    fclose(output);

    return 0;
}

char*
arr_output(long long int* int_arr, int size, enum OPTS opt)
{
    char* arr_string = (char *) malloc(BUF_LEN);
    char* arr_str_curs = arr_string;

    int int_len = 0;
    arr_str_curs += int_len;

    for(int i = 0; i < size; i++)
    {
        int_len = sprintf(arr_str_curs, "%lld ", int_arr[i]);
        arr_str_curs += int_len;
    }
    
    *(arr_str_curs - 1) = '\0';
    
    if( opt == STDOUT )
    {
        printf("array : [%s]\n", arr_string);
        free(arr_string);
    }

    return arr_string;
}

void 
qsort_(long long int* int_arr, int left, int right, FILE* output)
{
    int i = left, j = right, buf;
    long long int key = int_arr[(left + right) / 2];
    do
    {
        while ( int_arr[i] < key )
        {
            i++, counter++;
        }
        while ( key < int_arr[j] )
        {
            j--, counter++;
        }
        if ( i <= j )
        {
            buf = int_arr[i];
            int_arr[i] = int_arr[j];
            int_arr[j] = buf;
            i++, j--;
        }
    } while ( i < j );

    if ( left < j )
    {
        qsort_(int_arr, left, j, output);
    }
    if ( i < right )
    {
        qsort_(int_arr, i, right, output);
    }
}
