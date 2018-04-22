#include "expression.h"

//using namespace matrix;

namespace matrix
{
    Expression::Expression(std::string exprStr): iIsQuitStmt(false),
    iFatalError(false), iFatalError(NULL)
    {
        // Change to something cpp-ish.
        if ( !strcasecmp(exprStr.c_str(), "quit") ) 
            iIsQuitStmt=true;
        else
            iIsQuitStmt=false;
    };
    
    Expression::~Expression() { };
            
    bool
    Expression::execute() 
    { 
        return true;
    }
    
    bool
    Expression::parse()
    {
        std::vector<std::string> fakeTokens;
        fakeTokens.push_back("[1 0; 0 1;]");
        fakeTokens.push_back("+");
        fakeTokens.push_back("[1 0; 1 0;]");
        iTopOp = *(new Operation(fakeTokens));
        iResult = iTopOp.execute()
        return true;
    }


}
