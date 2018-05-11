#include <string>
#include "operation.h"
#include "operand.h"

//using namespace matrix;

namespace matrix
{
    Operation::Operation(strVectorT tokens)
    {
        lhs = new Operand(tokens[0]);
        rhs = new Operand(tokens[2]);
        if(tokens[1] == "+")
            type = SUM;
        else if(tokens[1] == "-")
            type = DEC;       
    }
    //Operation::Operation(Operand *lhs, opType, Operand *rhs) { }
    
    Operand* 
    SumOp::execute()
    {
        Operand *result = NULL;
        result = new Operand("[1 1; 1 1;]");
        return result;
    }
}
