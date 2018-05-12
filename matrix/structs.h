#include "stdint.h"
#include "stdio.h"

#define SIZE 100

struct MatrixT
{
    uint32_t rows;
    uint32_t cols;
    int** idata;
    double** fdata;
};

struct Matrix
{
    public:
        uint32_t rows;
        uint32_t cols;
        int** idata;
        double** fdata;
    
        Matrix() : rows(0), cols(0) { idata = new int*[SIZE]; };
        Matrix(int rows, int cols, int** idata = 0, double** fdata = 0):
            rows(rows), cols(cols), idata(idata), fdata(fdata) 
            { //printf("Matrix() %d\n", idata[0][0]); 
              //printf("Matrix() %d\n", idata[0][1]);
              //printf("Matrix() %d\n", idata[0][2]);
              };
        ~Matrix();
        Matrix &operator+(Matrix& rhs);
        char* toString();
};
