#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define BUF_LEN 50000
#define SM_BUF 10

enum OPTS { STDOUT, STRING };

char* arr_output(long long int* int_arr, int size, enum OPTS opt);
char* arr_sort(long long int* int_arr, int size);

int main(int argc, char* argv)
{
    char* numbers_curs;
    char* log_string;
    char* sorted_arr_str;

    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");
    if (!input || !output)
        return 1;


    char size_str[SM_BUF];
    int size = 0;
    int rc;
    numbers_curs = fgets(size_str, SM_BUF, input);
    sscanf(size_str, "%d", &size); 

    //printf("size is %d\n", size);

    char numbers_str[BUF_LEN];
    long long int numbers[size];
    memset((void *)numbers, 0, size * sizeof(long long int));
    //memset(numbers_str, 0x20, BUF_LEN);

    numbers_curs = fgets(numbers_str, BUF_LEN, input);
    // strip a newline
    memset(numbers_str + strlen(numbers_str) - 1, 0, 1);
    numbers_curs = numbers_str;
    for(int i = 0; i < size; i++)
    {
        sscanf(numbers_curs, "%lld", &numbers[i]);
        //printf("number %d: %lld\n", i, numbers[i]);
        //printf("number_curs 0 [%s]\n", numbers_curs);
        // skip scanned int
        while(*numbers_curs != ' ')
            numbers_curs++;
        //printf("number_curs 1 [%s]\n", numbers_curs);
        // skip a number of spaces
        while(*numbers_curs == ' ')
        {   
            //printf("numbers_curs 1.5 [%s]\n", numbers_curs);
            numbers_curs++;
        }
        //printf("number_curs 2 [%s]\n", numbers_curs);
    }

    //printf("result %lld %lld %lld\n", numbers[3], numbers[8], numbers[9]);
 
    //if(argc > 1)
    //    arr_output(numbers, size, STDOUT); 
    log_string = arr_sort(numbers, size); 
    sorted_arr_str = arr_output(numbers, size, STRING);
    //if(argc > 1)
    //    arr_output(numbers, size, STDOUT);
    
    fputs(log_string, output);
    fputs("\n", output);
    fputs(sorted_arr_str, output);
    fputs("\n", output);

    free(log_string);
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
    //memset(arr_string, 0, BUF_LEN);

    int int_len = 0;
    //int_len = sprintf(arr_str_curs, "%lld ", int_arr[0]);
    //printf("array 1 : int_len: [%d], [%s]\n", int_len, arr_string);
    //printf("array 0 : [%s]\n", arr_str_curs);
    // replace null with a space
    arr_str_curs += int_len;

//    printf("arr_output() el[%d]:[%lld]\n", 0, int_arr[0]);

    for(int i = 0; i < size; i++)
    {
//        printf("arr_output() el[%d]:[%lld]\n", i, int_arr[i]);
        int_len = sprintf(arr_str_curs, "%lld ", int_arr[i]);
        arr_str_curs += int_len;
//        *arr_str_curs = ' '; 
    }
    
    *(arr_str_curs - 1) = '\0';
    
    if( opt == STDOUT )
    {
        printf("array : [%s]\n", arr_string);
        free(arr_string);
    }

    return arr_string;
}

char*
arr_sort(long long int* int_arr, int size)
{
    char* result = NULL;
    result = (char *) calloc(size, sizeof(char) * 5);
    char* result_curs = result;
    int it, it_4_log, tmp, printed_len;

    //printf("it for logging: [%d]\n", 1);
    printed_len = sprintf(result_curs, "%d ", 1); 
    result_curs += printed_len;

    for(int i = 1; i < size; i++)
    {
        it = i - 1;
        while(it >= 0 && int_arr[it] > int_arr[it+1])
        {
            tmp = int_arr[it];
            int_arr[it] = int_arr[it+1];
            int_arr[it+1] = tmp;
            it--;
        }
        it_4_log = (it == i - 1) ? i + 1 : it + 2;
        //printf("it for logging: [%d]\n", it_4_log);
        printed_len = sprintf(result_curs, "%d ", it_4_log); 
        result_curs += printed_len;
    }
    *(--result_curs) = '\0';

    //printf("logged ids: [%s]\n", result);

    return result;
}
