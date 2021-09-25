#include <stdlib.h>
#include <stdio.h>

#define ARR_SIZE 5

/*@ predicate
    isSorted{L}(int* arr, integer n) =
        \forall integer i, j; 0 <= i < j < n ==> arr[i] <= arr[j];

    predicate
    isOdd{L}(integer n) =
        n % 2 == 1;

    predicate
    isEven{L}(integer n) =
        n % 2 == 0;
*/

/*@ requires n > 0;
  @ requires \valid_read(arr+(0.. n-1));
  @ ensures isSorted(arr, n);
  @ ensures \forall integer i; 0 <= n < n-1 ==> (\exists int j; arr[i] == \old(arr[j])); 
 */
void oddeven_rl(int *arr, int n) {
    int i, tmp, cnt = 1;
    /*@ loop invariant cnt > 0;
      @ loop invariant isOdd(n) ==> (\forall integer i; (0 < i < n && isOdd(i)) ==> arr[i-1] <= arr[i]);
      @ loop invariant isEven(n) ==> (\forall integer i; (0 < i < n && isEven(i)) ==> arr[i-1] <= arr[i]);
      @ loop assigns *arr, i, tmp;
      @ loop variant cnt;
     */
    while (cnt > 0) {
        cnt = 0;
        /*@ loop invariant 0 < i < n;
          @ loop invariant isOdd(n) ==> (\forall integer i; (0 < i < n && isEven(i)) ==> arr[i-1] <= arr[i]);
          @ loop invariant isEven(n) ==> (\forall integer i; (0 < i < n && isOdd (i)) ==> arr[i-1] <= arr[i]);
          @ loop assigns *arr, i, tmp;
          @ loop variant n-i;
         */
        for (i = n - 1; i > 0; i -= 2) {
            if (arr[i] < arr[i - 1]) {
                tmp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = tmp;
                ++cnt;
            }
        }
        /*@ loop invariant 0 < i < n;
          @ loop invariant isOdd(n) ==> (\forall integer i; (0 < i < n && isOdd(i)) ==> arr[i-1] <= arr[i]);
          @ loop invariant isEven(n) ==> (\forall integer i; (0 < i < n && isEven(i)) ==> arr[i-1] <= arr[i]);
          @ loop assigns *arr, i, tmp;
          @ loop variant n-i;
         */
        for (i = n - 2; i > 0; i -= 2) {
            if (arr[i] < arr[i - 1]) {
                tmp = arr[i];
                arr[i] = arr[i - 1];
                arr[i - 1] = tmp;
                ++cnt;
            }
        }
    }
}
/*
int main()
{
    int arr[ARR_SIZE] = { 5, 4, 1, 3, 2 };
    printf("initial array \n");
    for (size_t i = 0; i < ARR_SIZE; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    oddeven_rl(arr, ARR_SIZE);
    printf("sorted array \n");
    for (size_t i = 0; i < ARR_SIZE; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
*/
