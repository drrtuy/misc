#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define BUF_LEN 2097152
#define SM_BUF 60

enum OPTS { STDOUT, STRING };

char* arr_output(long long int* int_arr, int size, enum OPTS opt);
char* arr_sort(long long int* int_arr, int size, FILE* output);

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
    long long int numbers[4999];
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
    //printf("size is %d\n", size);
    log_string = arr_sort(numbers, size, output); 
    sorted_arr_str = arr_output(numbers, size, STRING);
    //if(argc > 1)
    //    arr_output(numbers, size, STDOUT);
    
    //fputs(log_string, output);
    //fputs("\n", output);

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
arr_sort(long long int* int_arr, int size, FILE* output)
{
    //printf("size is %d\n", size);
    char* result = NULL;
    uint16_t lower_indices[100];
    uint16_t higher_indices[100];
    int idx = 0;
    result = (char *) malloc(BUF_LEN * sizeof(char));
    char* result_cursor = result;
    int it = 0, tmp, printed_len = 0, total_len = 0;

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
            lower_indices[idx] = it + 2;
			higher_indices[idx++] = it + 3;
            if(idx == 62)
            {
                printed_len = sprintf(result_cursor,
                    "Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n\
Swap elements at indices %d and %d.\nSwap elements at indices %d and %d.\n",
lower_indices[0], higher_indices[0], lower_indices[1], higher_indices[1],
lower_indices[2], higher_indices[2], lower_indices[3], higher_indices[3],
lower_indices[4], higher_indices[4], lower_indices[5], higher_indices[5],
lower_indices[6], higher_indices[6], lower_indices[7], higher_indices[7],
lower_indices[8], higher_indices[8], lower_indices[9], higher_indices[9],
lower_indices[10], higher_indices[10], lower_indices[11], higher_indices[11],
lower_indices[12], higher_indices[12], lower_indices[13], higher_indices[13],
lower_indices[14], higher_indices[14], lower_indices[15], higher_indices[15],
lower_indices[16], higher_indices[16], lower_indices[17], higher_indices[17],
lower_indices[18], higher_indices[18], lower_indices[19], higher_indices[19],
lower_indices[20], higher_indices[20], lower_indices[21], higher_indices[21],
lower_indices[22], higher_indices[22], lower_indices[23], higher_indices[23],
lower_indices[24], higher_indices[24], lower_indices[25], higher_indices[25],
lower_indices[26], higher_indices[26], lower_indices[27], higher_indices[27],
lower_indices[28], higher_indices[28], lower_indices[29], higher_indices[29],
lower_indices[30], higher_indices[30], lower_indices[31], higher_indices[31],
lower_indices[32], higher_indices[32], lower_indices[33], higher_indices[33],
lower_indices[34], higher_indices[34], lower_indices[35], higher_indices[35],
lower_indices[36], higher_indices[36], lower_indices[37], higher_indices[37],
lower_indices[38], higher_indices[38], lower_indices[39], higher_indices[39],
lower_indices[40], higher_indices[40], lower_indices[41], higher_indices[41],
lower_indices[42], higher_indices[42], lower_indices[43], higher_indices[43],
lower_indices[44], higher_indices[44], lower_indices[45], higher_indices[45],
lower_indices[46], higher_indices[46], lower_indices[47], higher_indices[47],
lower_indices[48], higher_indices[48], lower_indices[49], higher_indices[49],
lower_indices[50], higher_indices[50], lower_indices[51], higher_indices[51],
lower_indices[52], higher_indices[52], lower_indices[53], higher_indices[53],
lower_indices[54], higher_indices[54], lower_indices[55], higher_indices[55],
lower_indices[56], higher_indices[56], lower_indices[57], higher_indices[57],
lower_indices[58], higher_indices[58], lower_indices[59], higher_indices[59],
lower_indices[60], higher_indices[60], lower_indices[61], higher_indices[61]);
                result_cursor += printed_len;
                total_len += printed_len;
                printed_len = 0;
                idx = 0;
            }

            if ( total_len + 2000 > BUF_LEN )
            {
                *(result_cursor + 1) = '\0';
                fputs(result, output);
                result_cursor = result;
                total_len = 0;
            }
        }
        
        //it_4_log = (it == i - 1) ? i + 1 : it + 2;
        //printf("it for logging: [%d]\n", it_4_log);
    }

	if ( total_len || idx )
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
