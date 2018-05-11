#include "structs.h"
#include "stdio.h"
#include "string.h"


class Matrix;

Matrix&
Matrix::operator+(Matrix& rhs)
{
    Matrix* result = new Matrix();
    if(this->rows != rhs.rows || this->cols != rhs.cols)
    { 
        return *result;
    }
    
    if(this->rows == 0)
    {
        for(int i = 0; i < this->cols; i++)
        {
            if(!i)
                result->idata[0] = new int[SIZE];
            result->idata[0][i] = this->idata[0][i] + rhs.idata[0][i];
        }
        result->rows = this->rows;
        return *result;
    }
    
    for(int j = 0; j <= this->rows; j++)
    {
        for(int i = 0; i <= this->cols; i++)
        {
            if(!i)
                result->idata[j] = new int[SIZE];
            result->idata[j][i] = this->idata[j][i] + rhs.idata[j][i];
        }
    }
    result->rows = this->rows;
    result->cols = this->cols;
    return *result;
}   
char*
Matrix::toString()
{
    int bytes = 0;
    char* result = new char[SIZE];
    memset(result, 0, SIZE);
    result[0]='[';
    int totBytes = 1;
    int j,i = 0;
    for(j = 0; j <= this->rows; j++)
    {
        for(i = 0; i < this->cols; i++)
        {
            bytes = sprintf(result+totBytes, " %d", this->idata[j][i]);  
            totBytes += bytes;
        }
        if(j < this->rows)
        {
            bytes = sprintf(result+totBytes, ";"); totBytes+=1;
        }
        else
        {
            sprintf(result+totBytes, " "); totBytes+=1;
        }
    }   
    result[totBytes] = ']';
    return result;
}
