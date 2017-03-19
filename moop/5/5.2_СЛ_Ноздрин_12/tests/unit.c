#include "unity.h"
#include "module.h"
#include <stdlib.h>
#include <stdbool.h>

/*
void testIsBool()
{
    TEST_ASSERT_EQUAL_BOOL(true, true);
    TEST_ASSERT_EQUAL_BOOL(false, false);
}
*/


void testFill() 
{
    int **input = fill( 3, 3, 3, 3);
    TEST_ASSERT_EQUAL_INT(4, input[1][1]);
    TEST_ASSERT_EQUAL_INT(6, input[2][1]);
    TEST_ASSERT_EQUAL_INT(8, input[2][2]);
    input = fill( 4, 4, 4, 4);
    TEST_ASSERT_EQUAL_INT(15, input[3][3]);
}

void testIsBottomLine()
{
    TEST_ASSERT_EQUAL_BOOL(true, isBottomLine(2, 2, 3));
    TEST_ASSERT_EQUAL_BOOL(false, isBottomLine(1, 2, 3));
}

void testIsTopLine()
{
    TEST_ASSERT_EQUAL_BOOL(true, isTopLine(0, 2, 3));
    TEST_ASSERT_EQUAL_BOOL(false, isTopLine(1, 2, 3));
}

void testIsRightSide()
{
    TEST_ASSERT_EQUAL_BOOL(true, isRightSide(0, 2, 3));
    TEST_ASSERT_EQUAL_BOOL(false, isRightSide(1, 1, 3));
}

void testIsLeftSide()
{
    TEST_ASSERT_EQUAL_BOOL(true, isLeftSide(0, 0, 3));
    TEST_ASSERT_EQUAL_BOOL(false, isLeftSide(1, 2, 3));
}
void testIsLeftBottom()
{
    TEST_ASSERT_EQUAL_BOOL(true, isLeftBottom(2, 0, 3));
    TEST_ASSERT_EQUAL_BOOL(false, isLeftBottom(1, 2, 3));
}

void testIsRightTop()
{
    TEST_ASSERT_EQUAL_BOOL(true, isRightTop(0, 2, 3));
    TEST_ASSERT_EQUAL_BOOL(false, isRightTop(1, 2, 3));
}

void testMoveAtLeftSide()
{
    int x = 0;
    int y = 0;
    int size = 5;
    enum direction_t direction = down; 
    moveAtLeftSide(&y, &x, size, &direction);
    TEST_ASSERT_EQUAL_INT(1, y);
    x = 0; y = 1; direction = up;
    moveAtLeftSide(&y, &x, size, &direction);
    TEST_ASSERT_EQUAL_INT(0, y);
    TEST_ASSERT_EQUAL_INT(1, x);
}

void testMoveAtRightSide()
{
    int size = 5;
    int x = size - 1;
    int y = 1;
    enum direction_t direction = up; 

    moveAtRightSide(&y, &x, size, &direction);
    TEST_ASSERT_EQUAL_INT(2, y);
    TEST_ASSERT_EQUAL_INT(size - 1, x);
    TEST_ASSERT_EQUAL_INT(0 , (int) direction);
    x = size - 1; y = 2; direction = up;
    moveAtRightSide(&y, &x, size, &direction);
    TEST_ASSERT_EQUAL_INT(3, y);
    TEST_ASSERT_EQUAL_INT(size - 2, x);
    TEST_ASSERT_EQUAL_INT((int) direction , (int) direction);

    size = 6; x = size - 1; y = 1; direction = up;
    moveAtRightSide(&y, &x, size, &direction);
    TEST_ASSERT_EQUAL_INT(2, y);
    TEST_ASSERT_EQUAL_INT(size - 2, x);
    TEST_ASSERT_EQUAL_INT(1 , (int) direction);
    x = size - 1; y = 2; direction = up;
    moveAtRightSide(&y, &x, size, &direction);
    TEST_ASSERT_EQUAL_INT(3, y);
    TEST_ASSERT_EQUAL_INT(x, x);
    TEST_ASSERT_EQUAL_INT((int) direction , (int) direction);

}

int main(void)

{
    UNITY_BEGIN();
    RUN_TEST(testIsLeftSide);
    RUN_TEST(testIsRightSide);
    RUN_TEST(testIsBottomLine);
    RUN_TEST(testIsTopLine);
    RUN_TEST(testIsRightTop);
    RUN_TEST(testIsLeftBottom);

    RUN_TEST(testMoveAtLeftSide);
    RUN_TEST(testMoveAtRightSide);

    RUN_TEST(testFill);
    return UNITY_END();
}
