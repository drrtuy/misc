#include "structs.h"
#include "stdio.h"
#include "string.h"


class Matrix;

Matrix&
Matrix::operation(Matrix& rhs, char op)
{
    Matrix* result = new Matrix();

    if(this->rows == 1)
    {
        for(int i = 0; i < this->cols; i++)
        {
            if(!i)
                result->idata[0] = new int[SIZE];
            switch(op)
            {
            case '+':
                result->idata[0][i] = this->idata[0][i] + rhs.idata[0][i];
                break;
            
            case '-':
            
                result->idata[0][i] = this->idata[0][i] - rhs.idata[0][i];
                break;
            }
        }
        result->rows = this->rows;
        return *result;
    }

    for(int j = 0; j < this->rows; j++)
    {
        for(int i = 0; i < this->cols; i++)
        {
            if(!i)
                result->idata[j] = new int[SIZE];
            switch(op) {
            case '+':
                result->idata[0][i] = this->idata[0][i] + rhs.idata[0][i];
                break;
            case '-':
                result->idata[0][i] = this->idata[0][i] - rhs.idata[0][i];
                break;
            }
        }
    }
    result->rows = this->rows;
    result->cols = this->cols;
    return *result;
}

Matrix&
Matrix::operator+(Matrix& rhs)
{
    return operation(rhs, '+');
}

Matrix&
Matrix::operator-(Matrix& rhs)
{
     return operation(rhs, '-');
}


Matrix&
Matrix::operator*(Matrix& rhs)
{
    Matrix* result = new Matrix();

    if(this->rows == 0)
    {
        for(int i = 0; i < this->cols; i++)
        {
            if(!i)
                result->idata[0] = new int[SIZE];
            result->idata[0][0] = this->idata[0][i] * rhs.idata[i][0];
        }

        result->rows = this->rows;
        return *result;
    }

    for(int j = 0; j < this->rows; j++)
    {
        result->idata[j] = new int[SIZE];
        for(int it = 0; it < rhs.cols; it++)
        {
            result->idata[j][it] = 0;
            for(int iter = 0; iter < rhs.rows; iter++)
            {
                result->idata[j][it] += this->idata[j][iter] * rhs.idata[iter][it];
            }
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
    for(j = 0; j < this->rows; j++)
    {
        if(this->empty)
            continue;
        for(i = 0; i < this->cols; i++)
        {
            bytes = sprintf(result+totBytes, " %d", this->idata[j][i]);  
            totBytes += bytes;
        }
        if(!this->cols)
        {
            bytes = sprintf(result+totBytes, " %d", this->idata[j][0]);  
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

bool
Matrix::compDimensions(Matrix& rhs, char op)
{
    if ( op == '+' || op == '-')
        return this->rows != rhs.rows || this->cols != rhs.cols;
    else if ( op == '*' )
    {
        fprintf(stderr, "got here %d %d\n", this->cols, rhs.rows);
        return this->cols != rhs.rows;
    }
}
