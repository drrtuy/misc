#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

//#include "edx-io.h"

#define BUF_LEN 2097152
#define SM_BUF 60
#define eprintf(level, args...) if ( debug >= level ) printf (args)

typedef long long int lli;

enum OPTS { STDOUT, STRING };

char* arr_output(lli* int_arr, int size, enum OPTS opt);
char* arr_sort(lli* int_arr, int size, FILE* output);
uint8_t arr_is_sorted(lli* int_arr, int size);
lli* merge_sort(lli* arr, uint32_t b, uint32_t e);
lli* merge(lli* a1, lli* a2, uint32_t l1, uint32_t l2);

int debug = 0;

int main(int argc, char* argv)
{
    char* numbers_curs;
    char* log_string;
    char* sorted_arr_str;

    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");
    if (!input || !output)
        return 1;

    debug = argc - 1;

    char size_str[SM_BUF];
    int size = 0;
    int rc;
    numbers_curs = fgets(size_str, SM_BUF, input);
    sscanf(size_str, "%d", &size); 

    eprintf(1, "main() size: [%d]\n", size);

    char numbers_str[BUF_LEN];
    lli numbers[size];
    memset((void *)numbers, 0, size * sizeof(lli));

    numbers_curs = fgets(numbers_str, BUF_LEN, input);
    // strip a newline
    numbers_str[strlen(numbers_str)-1] = '\0';
    //memset(numbers_str + strlen(numbers_str) - 1, 0, 1);
    numbers_curs = numbers_str;
    for(int i = 0; i < size; i++)
    {
        sscanf(numbers_curs, "%lld", &numbers[i]);
        // skip scanned int
        while(*numbers_curs != ' ')
            numbers_curs++;
        // skip a number of spaces
        while(*numbers_curs == ' ')
        {   
            numbers_curs++;
        }
    }

    if(debug)
    {
        arr_output(numbers, size, STDOUT);
        arr_output(merge_sort(numbers, 1, size), size , STDOUT);
    }
    /*
    lli tmp_arr[3] = { 5LL, 1LL, 4LL };
    if(debug)
    {
        arr_output(tmp_arr, 3, STDOUT);
        arr_output(merge_sort(tmp_arr, 1, 3), 3 , STDOUT);
    }
    
    lli tmp_arr2[2] = { 5LL, 1LL };
    if(debug)
    {
        arr_output(tmp_arr2, 2, STDOUT);
        arr_output(merge_sort(tmp_arr2, 1, 2), 2 , STDOUT);
    }*/
    
    //log_string = arr_sort(numbers, size, output); 
    //sorted_arr_str = arr_output(numbers, size, STRING);
    //if(argc > 1)
    //    arr_output(numbers, size, STDOUT);
    
    //fputs(log_string, output);
    //fputs("\n", output);

    //fputs(sorted_arr_str, output);
    fputs("\n", output);

    free(log_string);
    free(sorted_arr_str);

    fclose(input);
    fclose(output);

    return 0;
}

char*
arr_output(lli* int_arr, int size, enum OPTS opt)
{
    char* arr_string = (char *) malloc(BUF_LEN);
    char* arr_str_curs = arr_string;

    int int_len = 0;
//    arr_str_curs += int_len;

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

char*
arr_sort(lli* int_arr, int size, FILE* output)
{
    char* result = NULL;
    uint16_t lower_indices[100];
    uint16_t higher_indices[100];
    int idx = 0;
    result = (char *) malloc(BUF_LEN * sizeof(char));
    char* result_cursor = result;
    int it = 0, tmp, printed_len = 0, total_len = 0;
	int it_4_log = 0;
	uint8_t is_sorted = arr_is_sorted(int_arr, size);

    for(int i = 1; i < size; i++)
    {
        it = i - 1;
        while(it >= 0 && int_arr[it] > int_arr[it+1])
        {
            //printf("arr_sort i: %d it: %d\n", i, it);
            tmp = int_arr[it];
            int_arr[it] = int_arr[it+1];
            int_arr[it+1] = tmp;
            it--;
			if (is_sorted == 0)
			{
				lower_indices[idx] = it + 2;
				higher_indices[idx++] = it + 3;
			}
			
            if(is_sorted == 0 && idx == 62)
            {
                printed_len = sprintf(result_cursor, "some string");
                result_cursor += printed_len;
                total_len += printed_len;
                printed_len = 0;
                idx = 0;
            }

            if ( is_sorted == 0 && total_len + 2000 > BUF_LEN )
            {
                *(result_cursor + 1) = '\0';
                fputs(result, output);
                result_cursor = result;
                total_len = 0;
            }
        }
    }
	
	if ( is_sorted == 0 && total_len )
	{
		*(result_cursor + 1) = '\0';
		fputs(result, output);
		result_cursor = result;
		total_len = 0;
	}
    
	if ( is_sorted == 1 )
	{
		result_cursor = result;
		for(uint16_t iter = 0; iter < size/2; iter++)
		{
			result_cursor += sprintf(result_cursor, 
					"Swap elements at indices %d and %d.\n", iter + 1, size - iter);
		}
		*(result_cursor + 1) = '\0';
		fputs(result, output);
	}

	if ( is_sorted == 0 && ( total_len || idx ) )
	{
		if(idx)
		{
			for(int ite = 0; ite < idx; ite++) 
			{
				
				printed_len = sprintf(result_cursor, "Swap elements at indices %d and %d.\n",
					lower_indices[ite], higher_indices[ite]);
					//printf("sort() %s\n", result_cursor);
					result_cursor += printed_len;
					//printf("sort() %s\n", result_cursor);
			}
		}
		//printf("sort 2() %s\n", result);
		*(result_cursor + 1) = '\0';
		fputs(result, output);
		result_cursor = result;
		total_len = 0;
	}
	
    printed_len = sprintf(result, "No more swaps needed.\n"); 
    result[printed_len] = '\0';
    fputs(result, output);

    return result;
}

lli*
merge(lli* a1, lli* a2, uint32_t l1, uint32_t l2)
{
    if (!l1 )
        l1 = 1;
    if (!l2 )
        l2 = 1;
    lli* merge_result = calloc(l1 + l2, sizeof(lli));

    
    eprintf(3, "merge() merge_result %p\n", merge_result);
    eprintf(3, "merge() l1 [%d]\tl2[%d]\n", l1, l2);

    uint32_t i1 = 0, i2 = 0, res_it = 0;
    while ( i1 < l1 || i2 < l2 )
    {
        if ( i2 == l2 || ( i1 < l1 && a1[i1] <= a2[i2] ) )
        {
            eprintf(2, "merge() set from a1 merge_result[%d] = %d\n", res_it, a1[i1]);
            merge_result[res_it] = a1[i1], res_it++, i1++;
        }
        else
        {
            eprintf(2, "merge() set from a2 merge_result[%d] = %d\n", res_it, a2[i2]);
            merge_result[res_it] = a2[i2], res_it++, i2++;
        }
    }

    eprintf(2, "merge() free a1: [%p]\ta2: [%p]\n", a1);
    if ( l1 > 1 )
        free(a1);
    if ( l2 > 1 )
        free(a2);   

    return merge_result;
}

//
// b - index starting from 1
// e - index with max = length(arr)
// returns sorted array or a part of it
//
lli*
merge_sort(lli* arr, uint32_t b, uint32_t e)
{
    eprintf(2, "merge_sort() b [%d] e [%d]\n", b, e);
    if ( b == e )
    {
        return arr;
    }
        
    uint32_t m = ( e + b ) / 2;
    eprintf(2, "merge_sort() m [%d] \n", m);
    lli* a1 = merge_sort(arr, b, m);
    lli* a2 = merge_sort(&arr[m + 1 - b], m + 1, e);
    lli* result = merge(a1, a2, m + 1 - b, e - m);

    return result;   
}

uint8_t arr_is_sorted(lli* int_arr, int size)
{
	uint8_t result = 1;
	for(size--; size > 0; size--)
	{
		if(int_arr[size] > int_arr[size-1])
		{
			result = 0;
			break;
		}
	}
	return result;
}
