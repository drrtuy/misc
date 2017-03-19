#include "unity.h"
#include "module.h"
#include <stdlib.h>

void test_one() 
{
    double **input;
    input = (double **) (malloc (sizeof(double *) * 4));
    for (int i = 0; i < 4; i++) { 
        input[i] = (double *) (malloc (sizeof(double) * 2));
    }
    input[0][0] = 1; input[0][1] = 5;
    input[1][0] = 2; input[1][1] = 6;
    input[2][0] = 3; input[2][1] = 7;
    input[3][0] = 4; input[3][1] = 8;
    swapCols(input, 0, 1, 4, 2);
    TEST_ASSERT_EQUAL_FLOAT(5.0, input[0][0]); 
    TEST_ASSERT_EQUAL_FLOAT(1.0, input[0][1]); 
    TEST_ASSERT_EQUAL_FLOAT(1.0, input[3][1]); 
}

int main(void)

{
    UNITY_BEGIN();
    RUN_TEST(test_one);
    return UNITY_END();
}
