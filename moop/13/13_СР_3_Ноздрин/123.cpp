#include <iostream>
#include <string.h>

#include "dec.cpp"

using namespace std;

int main()
{
    Dec A, B, C;
    A.Create(1, "8");
    B.Create(2, "25");
    C.Create(2, "25");
    for(int i = 0; i < 4; i++)
    {
        C = C.Add(C); 
    }
    //cout << C.outPut() << endl;
    
    C = A.Mul(B);
    cout << C.outPut() << endl;

    return 0;
}
