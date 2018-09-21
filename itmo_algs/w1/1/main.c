#include "stdio.h"
#include "string.h"
#include "stdint.h"

int main()
{

    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("output.txt", "w");
    if (!input || !output)
        return 1;

    char str[128];
    long long int a,b;

    fgets(str, 128, input);
    sscanf(str, "%lld %lld", &a, &b); 
    
    //printf("result %ld %ld %ld\n", a, b, a + b * b);
    
    memset(str, 0, 128);
    sprintf(str, "%lld\n", a + b * b);

    fputs(str, output);

    fclose(input);
    fclose(output);

    return 0;
}
