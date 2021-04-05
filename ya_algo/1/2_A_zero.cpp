// Contest test run ID 48282105
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <limits>

void closestZeroDistanceWrapper(std::istream& in, std::ostream& out);

void TestTheClosestZero()
{
    std::stringstream in;
    in << "5\n";
    in << "0 1 4 9 0\n";
    std::stringstream ss;
    closestZeroDistanceWrapper(in, ss);
    std::string out = ss.str();
    assert(out == "0 1 2 1 0 ");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "6\n";
    in << "0 7 9 4 8 20\n";
    closestZeroDistanceWrapper(in, ss);
    out = ss.str();
    assert(out == "0 1 2 3 4 5 ");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "6\n";
    in << "0 0 0 4 8 0\n";
    closestZeroDistanceWrapper(in, ss);
    out = ss.str();
    assert(out == "0 0 0 1 1 0 ");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "1\n";
    in << "0\n";
    closestZeroDistanceWrapper(in, ss);
    out = ss.str();
    assert(out == "0 ");

    in.str(""); in.clear(); ss.str(""); ss.clear(); out.clear();
    in << "5\n";
    in << "0 0 0 0 0\n";
    closestZeroDistanceWrapper(in, ss);
    out = ss.str();
    assert(out == "0 0 0 0 0 ");
}

using HouseNumber = int32_t;
using HouseNumberVec = std::vector<HouseNumber>;

void closestZeroDistanceWrapper(std::istream& in, std::ostream& out)
{
    HouseNumber n = 0;
    HouseNumber tmp = 0;
    HouseNumberVec street, zeroes;
    in >> n;
    street.reserve(n);
    // there is enough memory according with the contest task
    // description
    zeroes.reserve(n);
    // populate both street and zeroes reading from in
    for (HouseNumber i = 0; i < n; ++i)
    {
        in >> tmp;
        if (!tmp)
            zeroes.push_back(i);
        street.push_back(tmp);
    }

    // Переписал логику без функции. IMHO больше букв получилось.
    // Кстати, цикл в функции прошлой версии покрывал 3ий случай из
    // TestTheClosestZero.
    // Для 0 явно выводим 0 и, если это последовательность 0, увеличиваем
    // lastClosest, указывающий на ближайщий 0.
    // Если не 0, то расстояние = min(dist(pos, lastClosest), dist(pos, lastClosest+1),
    // if street[i] isn't 0
    //auto currentClosestZero = zeroes.begin();
    HouseNumberVec::size_type lastClosest = 0;
    for (HouseNumber pos = 0; pos < n; ++pos)
    {
        if (!street[pos])
        {
            out << "0 ";
            if (pos && !street[pos - 1])
                ++lastClosest;
        }
        else
        {
            // Больше нулей не будет - возвращаем расстояние до последнего нуля.
            if (pos > zeroes.back())
                out << pos - zeroes.back() << " ";
            else
            {
                HouseNumber distance = std::abs(zeroes[lastClosest] - pos);
                if (lastClosest < zeroes.size() - 1)
                {
                    HouseNumber nextZeroDistance = std::abs(zeroes[lastClosest + 1] - pos);
                    if (distance >= nextZeroDistance)
                    {
                        out << nextZeroDistance << " ";
                        ++lastClosest;
                    }
                    else
                    {
                        out << distance << " ";
                    }
                }
                else
                {
                    out << distance << " ";
                }
            }
        }
    }
}

int main(int argc, char** argv)
{

    // put any argument to follow unit testing path
    if (argc > 1)
        TestTheClosestZero();
    else
    {
        // Т.к. задача проходит тесты, в том числе и по таймингам,
        // я применял рекомендации по ускорению IO, описанные здесь:
        // https://codeforces.com/blog/entry/5217?locale=ru
        // В этой задаче без sync_with_stdio я не вписываюсь
        // в выделенное на runtime время: 396ms(без) vs 246ms(с)
        // Я проверю рекомендованный выше алгоритм без этой строки,
        // но с учетом моих рассуждений я не думаю, что код пройдет
        // по ограничению по времени.
        std::ios_base::sync_with_stdio(false);
        closestZeroDistanceWrapper(std::cin, std::cout);
    }
    std::cout << "\n";
}
