#include <iostream>
#include <string>
#include <ios>

#include "expression.h"
#include "operation.h"

bool run = true;

//using namespace std;
using namespace matrix;

/*namespace matrix
{
    class Expression;
}*/

int main(int argc, char **argv)
{
    std::string exprStr;
    Expression *expr = NULL;
    
    std::cout << "M-CLI. Simple matrix operations interpreter." << std::endl;

    while(run)
    {    
        std::cout << "M-CLI# ";
        try
        {
            std::getline(std::cin, exprStr);
        }
        catch (std::ios_base::failure &e)
        {
            std::cout << "main() ios_base::failure code " << e.code()
            << " message " << e.what() << std::endl;
        }        
        
        expr = new Expression(exprStr);
        
        if (expr->quit())
        {
            run = false;
        }       
        else if(expr->execute())
        {
            std::cout << expr->result() << std::endl;
        }
        else
        {
            std::cout << "FAIL: " << expr->failureMsg() << std::endl;
        }
        
        //cout << exprStr << endl;
    }

    std::cout << "Quit" << std::endl;
    
    return 0;
}



