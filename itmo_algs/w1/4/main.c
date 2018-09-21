#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "main.h"

#define BUF_LEN 2097152
#define W1_T4_STR_LEN 100
#define SM_BUF 10

enum OPTS { STDOUT, STRING };

char* arr_output(void* el_arr_c, int size, enum OPTS opt);
char* arr_sort(void* el_arr_c, int size);
size_t getline_(char **lineptr, size_t *n, FILE *stream);

int main(int argc, char** argv)
{
    char* numbers_curs;
    char* log_string = NULL;
    char* sorted_arr_str = NULL;

    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");
    if (!input || !output)
        return 1;

    // get size as a first element in input.txt
    char size_str[SM_BUF];
    int size = 0;
    numbers_curs = fgets(size_str, SM_BUF, input);
    sscanf(size_str, "%d", &size); 

    // get an element string and populate array
    char* numbers_str = (char*) malloc(sizeof(char) * BUF_LEN);
    size_t numbers_str_size = BUF_LEN;
    element_t numbers[size];
    memset((void *)numbers, 0, size * sizeof(element_t));

    //numbers_str_size = getline_(&numbers_str, &numbers_str_size, input);
    numbers_curs = fgets(numbers_str, numbers_str_size, input);
    // strip a newline
    numbers_str[strlen(numbers_str) - 1] = '\0';
    numbers_curs = numbers_str;
    int i = 0;
	int rc;
    for(; i < size - 1; i++)
    {
        rc = sscanf(numbers_curs, "%lf", &(numbers[i].value));
        numbers[i].idx = i + 1; 
        // skip scanned int
        while(*numbers_curs != ' ')
            numbers_curs++;
        // skip a number of spaces
        while(*numbers_curs == ' ')
        {   
            numbers_curs++;
        }
    }
    // process the last element to omit if in the previous loop
    sscanf(numbers_curs, "%lf", &(numbers[i].value));
    numbers[i].idx = i + 1; 

    // we don't need this string memory anymore
    free(numbers_str);
 
    if(argc > 1)
        arr_output(numbers, size, STDOUT); 
    log_string = arr_sort((void *)numbers, size); 
    //sorted_arr_str = arr_output((void *)numbers, size, STRING);
    if(argc > 1)
        arr_output(numbers, size, STDOUT);
    
    if(log_string)
    {
        fputs(log_string, output);
        fputs("\n", output);
        free(log_string);
    }
    //fputs(sorted_arr_str, output);
    //fputs("\n", output);

    if(sorted_arr_str)
        free(sorted_arr_str);

    fclose(input);
    fclose(output);

    return 0;
}

char*
arr_output(void* el_arr_c, int size, enum OPTS opt)
{
    element_t* el_arr = (element_t*) el_arr_c;
    char* result = NULL; 
    char* result_curs;
    //memset(arr_string, 0, BUF_LEN);

    // Put min, 50 percentile, max in the string
    if (opt != STDOUT)
    {
       result = (char *) malloc(W1_T4_STR_LEN * sizeof(char));
       sprintf(result, "[%lf %d] [%lf %d] [%lf %d]", el_arr[0].value, el_arr[0].idx,
            el_arr[size/2].value, el_arr[size/2].idx,
            el_arr[size-1].value, el_arr[size-1].idx ); 
    }
    else
    {
        result_curs = result = (char *) malloc(BUF_LEN);
//        result_curs = result;
        int el_len = 0;

        for(int i = 0; i < size; i++)
        {
    //        printf("arr_output() el[%d]:[%lld]\n", i, el_arr[i]);
            el_len = sprintf(result_curs, "[%lf %d]", el_arr[i].value, el_arr[i].idx);
            result_curs += el_len;
    //        *result_curs = ' '; 
        }
        
        *(result_curs - 1) = '\0';
        
        if( opt == STDOUT )
        {
            printf("array : [%s]\n", result);
            free(result);
        }

    }
    return result;
}

char*
arr_sort(void* el_arr_c, int size)
{
    element_t* el_arr = (element_t*) el_arr_c;
    char* result = NULL;
    result = (char *) malloc(100 * sizeof(char));
    char* result_curs = result;
    int it, it_4_log, printed_len;
    element_t tmp;

    //printf("it for logging: [%d]\n", 1);
    //printed_len = sprintf(result_curs, "%d ", 1); 
    //result_curs += printed_len;

    for(int i = 1; i < size; i++)
    {
        it = i - 1;
        while(it >= 0 && el_arr[it].value > el_arr[it+1].value)
        {
            tmp = el_arr[it];
            el_arr[it] = el_arr[it+1];
            el_arr[it+1] = tmp;
            it--;
        }
        //it_4_log = (it == i - 1) ? i + 1 : it + 2;
        //printf("it for logging: [%d]\n", it_4_log);
        //printed_len = sprintf(result_curs, "%d ", it_4_log); 
        //result_curs += printed_len;
    }
    printed_len = sprintf(result, "%d %d %d", el_arr[0].idx, el_arr[size/2].idx,
         el_arr[size-1].idx);
    //printed_len = sprintf(result, "%d %d %d", 3, 4, 1);
    *(result + printed_len) = '\0';
    //printf("arr_sort result: [%s]\n", result);

    return result;
}

size_t getline_(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(BUF_LEN);
        if (bufptr == NULL) {
            return -1;
        }
        size = BUF_LEN;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + BUF_LEN;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}
