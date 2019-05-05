#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

#include "edx-io.h"

#define BUF_LEN 2097152

enum OPTS { STDOUT, STRING };

int
comp_(const void *, const void *);
char*
arr_output(uint32_t* int_arr, int size, enum OPTS opt);
uint32_t find_extrem(uint32_t** pointer_array, uint32_t** pointer_array_ends, uint32_t size);

int main(int argc, char** argv)
{
    uint32_t i = 0;

    edx_open();
    uint32_t size_a = edx_next_i32();
    uint32_t size_b = edx_next_i32();

    uint32_t arr_a[size_a];
    uint32_t arr_b[size_b];
    uint32_t source_arr[size_a*size_b];
 
    for(i = 0;i < size_a ; i++)
    {
        arr_a[i] = edx_next_i32();
    }

    for(i = 0;i < size_b ; i++)
    {
        arr_b[i] = edx_next_i32();
    }

    uint32_t* small_side = ( size_a > size_b ) ? arr_b : arr_a;
    uint32_t* big_side = ( size_a <= size_b ) ? arr_b : arr_a;

    uint32_t small_size = ( size_a > size_b ) ? size_b : size_a;
    uint32_t big_size = ( size_a <= size_b ) ? size_b : size_a;

    qsort(small_side, small_size, sizeof(uint32_t), &comp_);
    qsort(big_side, big_size, sizeof(uint32_t), &comp_);

    uint32_t* multi_results[small_size];
    uint32_t* multi_results_ptr[small_size];
    uint32_t counter = 0;
    uint32_t finish = small_size * big_size;
    uint32_t* multi_results_ends[small_size];

    // array for testing
 //   uint32_t sorted_array[finish];

    // allocate memory
    for(i = 0;i < small_size ; i++)
    {
        multi_results[i] = (uint32_t *) malloc(sizeof(uint32_t) * big_size);
        multi_results_ptr[i] = multi_results[i];
        multi_results_ends[i] = multi_results_ptr[i] + big_size;
    }

    for(i = 0;i < small_size ; i++)
    {
        for(uint32_t it = 0; it < big_size; it++)
        {
           multi_results[i][it] = small_side[i] * big_side[it];
        }
    }

    uint64_t sum_of_10th = 0;
    uint64_t extrem = 0;

    while(counter < finish)
    {
        //sorted_array[counter] = find_extrem(multi_results_ptr, multi_results_ends, small_size);
        extrem = find_extrem(multi_results_ptr, multi_results_ends, small_size);
        if ( !(counter % 10) )
        {
//            printf("sum of 10th: %ld\n", sum_of_10th);
            //sum_of_10th += sorted_array[counter];
            sum_of_10th += extrem;
        }
        counter++;
    }

//    arr_output(big_side, big_size, STDOUT);
//    arr_output(small_side, small_size, STDOUT);

/*    for(i = 0;i < small_size ; i++)
    {
        arr_output(multi_results[i], big_size, STDOUT);
    }

    arr_output(sorted_array, finish, STDOUT);

    printf("sum of 10th: %ld\n", sum_of_10th);
*/
    //edx_print_i32(big_side[it]*small_side[i]); edx_print_char(' ');
    //edx_println_char(' ');
    edx_println_i32(sum_of_10th);
 
    edx_close();
    return 0;
}

int
comp_(const void *left, const void *right)
{
    return (*((const uint32_t*) left) - *((const uint32_t*) right));
}

char*
arr_output(uint32_t* int_arr, int size, enum OPTS opt)
{
    char* arr_string = (char *) malloc(BUF_LEN);
    char* arr_str_curs = arr_string;

    int int_len = 0;
    arr_str_curs += int_len;

    for(int i = 0; i < size; i++)
    {
        int_len = sprintf(arr_str_curs, "%d ", int_arr[i]);
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

uint32_t find_extrem(uint32_t** pointer_array, uint32_t** pointer_array_ends, uint32_t size)
{
    uint32_t result = 4294967295; uint32_t max_values_idx = 0;
    for(int i = 0; i < size; i ++)
    {
        if ( pointer_array[i] < pointer_array_ends[i] && result >= *pointer_array[i] )
        {
            result = *pointer_array[i]; max_values_idx = i;
        }
    }
    pointer_array[max_values_idx]++;
    return result;
}
