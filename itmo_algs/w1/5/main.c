#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#define BUF_LEN 2097152
#define SM_BUF 256

char number_buffer_[SM_BUF];

enum OPTS { STDOUT, STRING };

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
char* arr_sort(long long int* int_arr, int size, FILE* output);
uint8_t arr_is_sorted(long long int* int_arr, int size);
int int_to_buffer_(unsigned value, int pos);
void qsort_(long long int* int_arr, int left, int right, FILE* output);

int main(int argc, char** argv)
{
    char* numbers_curs;
    char* log_string;
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

    //printf("size is %d\n", size);

    char numbers_str[BUF_LEN];
    long long int numbers[size];
    //memset((void *)numbers, 0, size * sizeof(long long int));
    //memset(numbers_str, 0x20, BUF_LEN);

    numbers_curs = fgets(numbers_str, BUF_LEN, input);
    // strip a newline
    memset(numbers_str + strlen(numbers_str) - 1, 0, 1);
    numbers_curs = numbers_str;
    for(int i = 0; i < size; i++)
    {
        sscanf(numbers_curs, "%lld", &numbers[i]);
        while(*numbers_curs != ' ')
            numbers_curs++;
        while(*numbers_curs == ' ')
        {   
            numbers_curs++;
        }
    }

    qsort_(numbers, 0, size - 1, output); 
    sorted_arr_str = arr_output(numbers, size, STRING);

    fputs(sorted_arr_str, output);
    fputs("\n", output);

//    free(log_string);
//    free(sorted_arr_str);

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

/*char*
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

	uint8_t is_sorted = arr_is_sorted(int_arr, size);
    int pos = SM_BUF - 1;

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
                pos = SM_BUF - 1;
                fputs("Swap elements at indices ", output);
                pos = int_to_buffer_(it + 2, pos);
                fputs(number_buffer_ + pos, output);
                //fputc(' ', output);
                fputs(" and ", output);
                pos = int_to_buffer_(it + 3, SM_BUF - 1);
                fputs(number_buffer_ + pos, output);
                fputs(".\n", output);
                //printed_len = sprintf(result, "Swap elements at indices %d and %d.\n",
                //    it + 2, it + 3);
                //*(result + printed_len) = '\0';
                //fputs(result, output);
                
			}
        }
    }

	if ( is_sorted == 1 )
	{
		result_cursor = result;
		for(uint16_t iter = 0; iter < size/2; iter++)
		{
			//printf("arr_sort() is_sorted: [%d]\n", is_sorted);
			result_cursor += sprintf(result_cursor, 
					"Swap elements at indices %d and %d.\n", iter + 1, size - iter);
		}
		*(result_cursor + 1) = '\0';
		fputs(result, output);
	}

    fputs("No more swaps needed.\n", output);
    //result[printed_len] = '\0';
    //fputs(result, output);

    return result;
}*/

void 
qsort_(long long int* int_arr, int left, int right, FILE* output)
{
    int i = left, j = right, buf;
    int pos;
    //long long int key = ( int_arr[(left + right - 2) / 2] + 
    //    int_arr[left] + int_arr[right] ) / 3;
    long long int key = int_arr[(left + right) / 2];
    //printf("qsort_() left [%d] right [%d] key [%lld]\n", left, right, key);
    do
    {
        while ( int_arr[i] < key )
            i++;
        while ( key < int_arr[j] )
            j--;
        //printf("qsort_() i [%d] j [%d]\n", i, j);
        if ( i <= j )
        {
            //printf("qsort_() swap\n");
            buf = int_arr[i];
            int_arr[i] = int_arr[j];
            int_arr[j] = buf;
            fputs("Swap elements at indices ", output);
            if ( i > j )
            {
                pos = int_to_buffer_(j , 255);
                fputs(number_buffer_ + pos, output);
                fputs(" and ", output);
                pos = int_to_buffer_(i, 255);
                fputs(number_buffer_ + pos, output);
                fputs(".\n", output);
            }
            else
            {
                pos = int_to_buffer_(i , 255);
                fputs(number_buffer_ + pos, output);
                fputs(" and ", output);
                pos = int_to_buffer_(j, 255);
                fputs(number_buffer_ + pos, output);
                fputs(".\n", output);
            }
            i++, j--;
        }
    } while ( i < j );
    
    if ( left < j )
        qsort_(int_arr, left, j, output);
    if ( i < right )
        qsort_(int_arr, i, right, output);
}

uint8_t arr_is_sorted(long long int* int_arr, int size)
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

int int_to_buffer_(unsigned value, int pos) 
{
    while (value >= 65536) {
        unsigned q = value / 100;
        unsigned r = value - ((q << 6) + (q << 5) + (q << 2));
        value = q;
        number_buffer_[--pos] = digit_ones_[r];
        number_buffer_[--pos] = digit_tens_[r];
    }
    while (1) {
        unsigned q = (value * 52429) >> (16 + 3);
        unsigned r = value - ((q << 3) + (q << 1));
        number_buffer_[--pos] = digit_ones_[r];
        value = q;
        if (value == 0) {
            break;
        }
    }
    return pos;
}
