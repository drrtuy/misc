#ifndef H_MATRIX_EXPRESSION
#define H_MATRIX_EXPRESSION

#include <string>
#include <string.h>

#include "operation.h"

namespace matrix
{ 
    /* 
     * Represents an expression. 
     */
    class Expression
    {
        private:
            bool iIsQuitStmt;
            std::string* iExprStr;
            matrix::SumOp* iTopOp;
            matrix::Operand* iResult;
            bool iFatalError;
            std::string iErrorMsg;
            
            bool parse();
        
        public:
            Expression(): iIsQuitStmt(false), iFatalError(false)
             { };
            // Check for non ASCII chars
            Expression(std::string exprStr);
            ~Expression();
            
            inline bool quit() { return iIsQuitStmt; }
            inline Operand result() { return *iResult; }
            inline std::string failureMsg()
            { 
                if(iFatalError)
                    return iErrorMsg;
            }
            
            bool execute();    
    };
}

#endif
