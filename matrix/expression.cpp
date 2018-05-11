#include "expression.h"

//using namespace matrix;

namespace matrix
{
    Expression::Expression(std::string exprStr): iFatalError(false)
    {
        // Change to something cpp-ish.
        if ( !strcasecmp(exprStr.c_str(), "quit") ) 
            iIsQuitStmt=true;
        else
            iIsQuitStmt=false;

        iExprStr = &exprStr;
    };
    
    Expression::~Expression() { };
            
    bool
    Expression::execute() 
    {
        if (parse())
        {
            if ( iResult = iTopOp->execute() )
                return true;
        }
        //return true;
        return false;
    }
    
    bool
    Expression::parse()
    {
        std::vector<std::string> fakeTokens;
        fakeTokens.push_back("[1 0; 0 1;]");
        fakeTokens.push_back("+");
        fakeTokens.push_back("[1 0; 1 0;]");
        iTopOp = new SumOp(fakeTokens);
        return true;
    }


}
