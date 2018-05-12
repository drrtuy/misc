#include "expression.h"
#include "lex.tab.hpp"
#include "parser.tab.hpp"

//using namespace matrix;

extern int yydebug;

namespace matrix
{
    Expression::Expression(std::string exprStr): iFatalError(false), iDebugFlags(0)
    {
        // Change to something cpp-ish.
        if ( !strcasecmp(exprStr.c_str(), "quit") ) 
            iIsQuitStmt=true;
        else
            iIsQuitStmt=false;

        //if ( !strcasecmp(exprStr.c_str(), "pdebug") )
        //    iDebugFlags |= 1;

        iExprStr = &exprStr;
        parse();
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
    
    int
    Expression::parse()
    {
        //std::vector<std::string> fakeTokens;
        //fakeTokens.push_back("[1 0; 0 1;]");
        //fakeTokens.push_back("+");
        //fakeTokens.push_back("[1 0; 1 0;]");
        //iTopOp = new SumOp(fakeTokens);
        //yydebug = 1;
        yy_scan_string(iExprStr->c_str());
        
        return yyparse();
    }


}
