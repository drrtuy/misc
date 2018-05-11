#ifndef H_MATRIX_OPERAND
#define H_MATRIX_OPERAND

#include <string>

namespace matrix
{
    class Operand
    {
        private:
            std::string iResult;
            
        public:
            Operand() { };
            Operand(std::string tokenStr): iResult(tokenStr) { };
            ~Operand() { };
        
        friend std::ostream &operator<<(std::ostream &stream, const Operand &op) { stream << op.iResult; }
    
    };

}

#endif

