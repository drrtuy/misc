#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "edx-io.h"

#define BUF_LEN 2097152
#define SM_BUF 256
#define eprintf(level, args...) if ( debug >= level ) printf (args)

typedef long long int lli;

enum OPTS { STDOUT, STRING };
FILE* input;
FILE* output;
char number_buffer[SM_BUF];

lli counter = 0;

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

char* arr_output(lli* int_arr, int size, enum OPTS opt);
char* arr_sort(lli* int_arr, int size, FILE* output);
uint8_t arr_is_sorted(lli* int_arr, int size);
lli* merge_sort(lli* arr, uint32_t b, uint32_t e);
lli* merge(lli* a1, lli* a2, uint32_t l1, uint32_t l2);
int int_to_buffer_(unsigned value, int pos);

int debug = 0;

int main(int argc, char** argv)
{
    char* numbers_curs;
    char* sorted_arr_str;

    debug = argc - 1;
    edx_open();
    int size = edx_next_i32();
    
    lli numbers[size];
    for(int i = 0; i < size; i++)
    {
        numbers[i] = edx_next_i64();
    }
    
    merge_sort(numbers, 1, size);
    edx_println_i64(counter);    
    
    edx_close();
    
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

lli*
merge(lli* a1, lli* a2, uint32_t l1, uint32_t l2)
{
    if (!l1 )
        l1 = 1;
    if (!l2 )
        l2 = 1;
        
    lli* merge_result = malloc((l1+l2) * sizeof(lli));

    uint32_t i1 = 0, i2 = 0, res_it = 0;
    while ( i1 < l1 || i2 < l2 )
    {
        if ( i2 == l2 || ( i1 < l1 && a1[i1] <= a2[i2] ) )
        {
            merge_result[res_it] = a1[i1], res_it++, i1++;
        }
        else
        {
            if ( i1 < l1 )
                counter += l1 - i1; 
            merge_result[res_it] = a2[i2], res_it++, i2++;
        }
    }

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
    //eprintf(2, "merge_sort() b [%d] e [%d]\n", b, e);

    if ( b == e )
    {
        return arr;
    }
        
    uint32_t m = ( e + b ) / 2;
    //eprintf(2, "merge_sort() m [%d] \n", m);
    lli* a1 = merge_sort(arr, b, m);
    lli* a2 = merge_sort(&arr[m + 1 - b], m + 1, e);
    lli* result = merge(a1, a2, m + 1 - b, e - m);

    //int printed_len = sprintf(number_buffer, "%d %d %lld %lld\n", b, e, result[0], result[e-b]);
    //eprintf(2, "merge_sort() moves %s\n", moves);
    //number_buffer[printed_len] = '\0';
    //fputs(number_buffer, output);    

    return result;   
}

uint8_t arr_is_sorted(lli* int_arr, int size)
{
	uint8_t result = 1;
	for(size--; size > 0; size--)
	{
		if(int_arr[size] < int_arr[size-1])
		{
			result = 0;
            //printf("unsorted\n");
			break;
		}
	}
    //
	return result;
}

int int_to_buffer_(unsigned value, int pos) 
{
    while (value >= 65536) {
        unsigned q = value / 100;
        unsigned r = value - ((q << 6) + (q << 5) + (q << 2));
        value = q;
        number_buffer[--pos] = digit_ones_[r];
        number_buffer[--pos] = digit_tens_[r];
    }
    while (1) {
        unsigned q = (value * 52429) >> (16 + 3);
        unsigned r = value - ((q << 3) + (q << 1));
        number_buffer[--pos] = digit_ones_[r];
        value = q;
        if (value == 0) {
            break;
        }
    }
    return pos;
}
