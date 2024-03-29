#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define ARR_SIZE 1

/*@ predicate
    isSorted{L}(int* arr, integer a, integer b) =
    a == b || \forall integer i, j; a <= i <= b ==> arr[i-1] <= arr[i];

    predicate
    pairsAreSortedAtOddPositions{L}(int* arr, integer a, integer b) =
      \forall integer i; a <= i <= b && isOdd(i) ==> arr[i-1] <= arr[i];

    predicate
    pairsAreSortedAtEvenPositions{L}(int* arr, integer a, integer b) =
      \forall integer i; a <= i <= b && isEven(i) ==> arr[i-1] <= arr[i]; 

    predicate
    isOdd{L}(integer n) =
        \abs(n) % 2 == 1;

    predicate
    isEven{L}(integer n) =
        \abs(n) % 2 == 0;
*/

/*@ requires 0 <= n <= INT_MAX;
  @ requires \valid_read(arr+(0.. n-1));
  @ assigns arr[0..n-1];
  @ ensures 1 == n ==> isSorted(arr, 0, 0);
  @ ensures 2 <= n ==> isSorted(arr, 0, n-1);
  @ ensures isSorted(arr, 0, n-1);
  @ ensures \forall integer i; 0 <= n <= n-1 ==> (\exists int j; arr[i] == \old(arr[j])); 
 */
void oddeven_rl(int *arr, int n) {
    int i, tmp, cnt = 1;
    //@ ghost int state = 1;
    /*@ loop invariant 0 <= n <= INT_MAX;
      @ loop invariant n == 1 ==> isSorted(arr, 0, 0);
      @ loop invariant state != 1 ==> -2 <= i <= n-2;
      @ loop invariant state != 1 && -1 <= i < n-2 && isOdd(i) ==> pairsAreSortedAtOddPositions(arr, i+2, n-1);
      @ loop invariant state != 1 && 0 <= i < n-2 && isEven(i) ==> pairsAreSortedAtEvenPositions(arr, i+2, n-1);
      @ loop assigns arr[0..n-1], i, tmp, cnt;
      @ loop variant cnt;
     */
    // индекс мин уменьшается
    while (cnt > 0) {
        cnt = 0;
        //@ ghost state = 2;
        //@ assert state != 1;
        //@ assert cnt == 0;
        //@ assert 0 <= n <= INT_MAX;
        /*@ loop invariant 0 <= n;
          @ loop invariant state != 1;
          @ loop invariant isOdd(n-1) ==> isOdd(i);
          @ loop invariant isEven(n-1) ==> isEven(i);
          @ loop invariant -1 <= i <= n-1;
          @ loop invariant -1 <= i < n-1 && isOdd(i) ==> pairsAreSortedAtOddPositions(arr, i + 2, n-1);
          @ loop invariant 0 <= i < n-1 && isEven(i) ==> pairsAreSortedAtEvenPositions(arr, i + 2, n-1);
          @ loop invariant 0 <= cnt;
          @ loop assigns arr[0..n-1], tmp, cnt;
          @ loop variant i;
         */
        for (i = n-1; i > 0; i -= 2) {
        L1:
            if (arr[i] < arr[i - 1]) {
                //@assert arr[i] < arr[i-1];
                //@assert 0 < i <= n-1;
                tmp = arr[i];
                //@assert tmp == arr[i] && tmp < arr[i-1];
                arr[i] = arr[i - 1];
                //@assert arr[i] == arr[i-1] && arr[i] > tmp;
                arr[i - 1] = tmp;
                //@ assert arr[i-1] == tmp && arr[i-1] <= arr[i];
                ++cnt;
                //@assert 0 < i <= n-1;
                //@assert isOdd(i) ==> pairsAreSortedAtOddPositions(arr, i, n-1);
                //@assert isEven(i) ==> pairsAreSortedAtEvenPositions(arr, i, n-1);
                //@assert cnt == \at(cnt, L1) + 1;
            }
            //@assert 0 < i <= n-1;
            //@assert arr[i-1] <= arr[i];
            //@assert isOdd(i) ==> pairsAreSortedAtOddPositions(arr, i, n-1);
            //@assert isEven(i) ==> pairsAreSortedAtEvenPositions(arr, i, n-1);
        }
        //@assert 0 <= n <= INT_MAX;
        //@assert isOdd(n-1) <==> i == -1;
        //@assert isEven(n-1) <==> i == 0;
        //@assert -1 <= i < n-1 && isOdd(i) ==> pairsAreSortedAtOddPositions(arr, i+2, n-1);
        //@assert -1 == i ==> pairsAreSortedAtOddPositions(arr, 1, n-1);
        //@assert 0 <= i < n-1 && isEven(i) ==> pairsAreSortedAtEvenPositions(arr, i+2, n-1);
        //@assert 0 == i ==> pairsAreSortedAtEvenPositions(arr, 2, n-1);
        //@assert n == 1 ==> isSorted(arr, 0, 0);
        //assert state != 1;
        
        /*@ loop invariant 0 <= n;
          @ loop invariant state != 1;
          @ loop invariant isOdd(n-2) <==> isOdd(i);
          @ loop invariant isEven(n-2) <==> isEven(i);
          @ loop invariant -2 <= i <= n-2;
          @ loop invariant -1 <= i < n-2 && isOdd(i) ==> pairsAreSortedAtOddPositions(arr, i + 2, n-2);
          @ loop invariant -2 < i < n-2 && isEven(i) ==> pairsAreSortedAtEvenPositions(arr, i + 2, n-2);
          @ loop assigns arr[0..n-2], tmp, cnt;
          @ loop variant i;
         */
        for (i = n - 2; i > 0; i -= 2) {
        L2:
            if (arr[i] < arr[i - 1]) {
                //@assert arr[i] < arr[i-1];
                //@assert 0 < i <= n-2;
                tmp = arr[i];
                //@assert tmp == arr[i] && tmp < arr[i-1];
                arr[i] = arr[i - 1];
                //@assert arr[i] == arr[i-1] && arr[i] > tmp;
                arr[i - 1] = tmp;
                //@ assert arr[i-1] == tmp && arr[i-1] <= arr[i];
                ++cnt;
                //@assert 0 < i <= n-2;
                //@assert isOdd(i) ==> pairsAreSortedAtOddPositions(arr, i, n-2);
                //@assert isEven(i) ==> pairsAreSortedAtEvenPositions(arr, i, n-2);
                //@assert cnt == \at(cnt, L2) + 1;
            }
            //@assert 0 < i <= n-2;
            //@assert arr[i-1] <= arr[i];
            //@assert isOdd(i) ==> pairsAreSortedAtOddPositions(arr, i, n-2);
            //@assert isEven(i) ==> pairsAreSortedAtEvenPositions(arr, i, n-2);
        }
        //@assert 0 <= n <= INT_MAX;
        //@assert -2 <= i <= n-2;
        //@assert isOdd(n-2) <==> -1 == i;
        //@assert isEven(n-2) ==> 0 == i || i == -2;
        //@assert -1 <= i < n-2 && isOdd(i) ==> pairsAreSortedAtOddPositions(arr, i+2, n-2);
        //@assert 0 <= i < n-2 && isEven(i) ==> pairsAreSortedAtEvenPositions(arr, i+2, n-2);
        //@assert n == 1 ==> isSorted(arr, 0, 0);
    }
    //@assert n == 1 ==> isSorted(arr,0, 0);
}

int main()
{
    int arr[ARR_SIZE] = { 0 };
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

