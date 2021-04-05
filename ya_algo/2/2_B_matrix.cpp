// Contest test run ID 48228488
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>

void gameWrapper(std::istream& in, std::ostream& out);

void testGame()
{
    std::stringstream in;
    in << "3\n";
    in << "1231\n";
    in << "2..2\n";
    in << "2..2\n";
    in << "2..2\n";
    std::stringstream ss;
    gameWrapper(in, ss);
    std::string out = ss.str();
    assert(out == "2");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "4\n";
    in << "1111\n";
    in << "9999\n";
    in << "1111\n";
    in << "9911\n";
    gameWrapper(in, ss);
    out = ss.str();
    assert(out == "1");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "4\n";
    in << "1111\n";
    in << "1111\n";
    in << "1111\n";
    in << "1111\n";
    gameWrapper(in, ss);
    out = ss.str();
    assert(out == "0");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "5\n";
    in << "1111\n";
    in << "1111\n";
    in << "1111\n";
    in << "1111\n";
    gameWrapper(in, ss);
    out = ss.str();
    assert(out == "0");
}

using GamePaneSymbol = uint16_t;
using DictVec = std::vector<GamePaneSymbol>;

void gameWrapper(std::istream& in, std::ostream& out)
{
    GamePaneSymbol k = 0;
    in >> k;
    // let k = k * 2
    GamePaneSymbol kx2 = k << 1;
    // ASCII dictionary
    // Если уменьшить размер dict, то это действительно сохранит какие-то байты,
    // но добавит лишнее вычитание внутри цикла. Т.к. в задаче ограничение по памяти
    // весьма значительное, то я выбрал оптимизацию вычислений в цикле за счет памяти.
    DictVec dict(256, 0);
    char c;
    // counting chars from the input stream in the dict
    while(in >> c)
    {
        ++dict[c];
    }
    GamePaneSymbol points = 0;
    // loop over chars sequence '1'..'9'
    for (GamePaneSymbol i = '1'; i <= '9'; ++i)
    {
        // there was a char and char counter <= original k * 2
        if (dict[i] && dict[i] <= kx2)
            ++points;
    }
    out << points;
}

int main(int argc, char** argv)
{
    // put any argument to follow unit testing path
    if (argc > 1)
        testGame();
    else
        gameWrapper(std::cin, std::cout);
    std::cout << "\n";
}
