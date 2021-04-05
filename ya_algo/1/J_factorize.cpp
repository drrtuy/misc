#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <cassert>
#include <sstream>

using namespace std;

void factorizeWrapper(uint32_t n, ostream& out);

void TestFactorize()
{
    uint32_t in = 8;
    std::stringstream ss; 
    factorizeWrapper(in, ss);
    string out = ss.str();
    assert(out == "2 2 2 ");

    in = 13;
    ss.str("");
    ss.clear();
    factorizeWrapper(in, ss);
    out.assign(ss.str());
    assert(out == "13 ");

    in = 100;
    ss.str("");
    ss.clear();
    factorizeWrapper(in, ss);
    out.assign(ss.str());
    assert(out == "2 2 5 5 ");
}


template <class T>
T sq_root (const T& n)
{
    return (T) floor (sqrt ((double) n));
}

template <class T>
bool even(const T& n)
{
    return (n & 1) == 0;
}

template <class T, class T2>
const vector<T>& get_primes (const T & b, T2 & pi)
{
    static vector<T> primes;
    static T counted_b;

    if (counted_b >= b)
        pi = T2 (upper_bound (primes.begin(), primes.end(), b) - primes.begin());
    else
    {
        if (counted_b == 0)
        {
            primes.push_back (2);
            counted_b = 2;
        }

        T first = counted_b == 2 ? 3 : primes.back()+2;
        for (T cur=first; cur<=b; ++++cur)
        {
            bool cur_is_prime = true;
            for (auto iter = primes.begin(), end = primes.end();
                iter != end; ++iter)
            {
                const T & div = *iter;
                if (div * div > cur)
                    break;
                if (cur % div == 0)
                {
                    cur_is_prime = false;
                    break;
                }
            }
            if (cur_is_prime)
                primes.push_back (cur);
        }

        counted_b = b;
        pi = (T2) primes.size();
    }
    return primes;
}

template <class T, class T2>
T2 prime_div_trivial (const T& n, T2 m)
{
    // сначала проверяем тривиальные случаи
    if (n == 2 || n == 3)
        return 1;
    if (n < 2)
        return 0;
    if (even (n))
        return 2;
    // генерируем простые от 3 до m
    T2 pi;
    const vector<T2>& primes = get_primes (m, pi);
    // делим на все простые
    for (auto iter=primes.begin(), end=primes.end(); iter!=end; ++iter)
    {
        const T2& div = *iter;
        if (div * div > n)
            break;
        else
            if (n % div == 0)
                return div;
    }

    if (n < m*m)
        return 1;
    return 0;
}

template <class T>
bool isprime(T n)
{
    if (n == 1)
        return false;
    for (T i = 2; i * i <= n; ++i)
    {
        if (!(n % i))
            return false;
    }
    return true;
}

template <class T, class T2>
void factorize (const T & n, map<T,unsigned> & result, T2 unused)
{
    if (n == 1)
        ;
    else
    {
        // проверяем, не простое ли число
        if (isprime(n))
            ++result[n];
        else
        // если число достаточно маленькое, то его разлагаем простым перебором
        {
            T div = prime_div_trivial (n, 31622); // поиск простых до sqrt(10^9)
            ++result[div];
            factorize (n / div, result, unused);
        }
    }
}

void factorizeWrapper(uint32_t n, ostream& out)
{
    map<uint32_t, uint32_t> result;
    factorize(n, result, 0);
    for (auto& v: result)
    {
        for (size_t i = 0; i < v.second; ++i)
        {
            out << v.first << " ";
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    uint32_t n;
    cin >> n;

    factorizeWrapper(n, cout);
    cout << "\n";

//    TestFactorize();
}
