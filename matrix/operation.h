#ifndef H_MATRIX_OPERATION

#define H_MATRIX_OPERATION

#include <string>
#include <vector>

#include "operand.h"

typedef std::vector<std::string> strVectorT;

namespace matrix
{ 
    /*
     * Represents operation
     */
    class Operation
    {
        typedef enum {
            NOOP,
            SUM,
            DEC
        } opType;
        private:
            Operand *rhs;
            Operand *lhs;
            opType type;
        
        public:
            Operation() { };
            Operation(strVectorT);
            //Operation(Operand *lhs, opType, Operand *rhs);
            virtual ~Operation() { };
            
            virtual Operand* execute() { };
            //inline Operand* result() { return iResult; };
    };
    
    class SumOp: public Operation
    {
        public:
            SumOp() { };
            SumOp(strVectorT tokens): Operation::Operation(tokens) {};
            ~SumOp() { };
            Operand* execute();
    };
    
}
#endif
