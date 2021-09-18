// 52561354
#include <iostream>
#include <vector>
#include <cassert>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <string_view>

// Использовал адаптивный алгоритм вычисления расстояния Левенштейна, который 
// пропускает общие префикс/суффикс в строках и работает с оставшимися подстроками.
// В dp хранится расстояние между подстроками. Переход такой же как и в классике:
// min(из трёх вариантов, получившихся путём удаления || замены || добавления) + 1, если s1(i) != s2(j).
// Для вычисления каждого последующего значения нужно всего три значения -
// сложность по памяти можно оптимизировать до O(max(s1.length(), s2.length()) по сравнению с классикой.
// Эффективная сложность по времени(если не учитывать подготовку) O(s3.length()), где s3 - различающаяся подстрока,
// полученная после подстановки.

void levenstheinDistWrapper(std::istream& in, std::ostream& out);

void levenstheinDistTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    levenstheinDistWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void levenstheinDistTestWrapper()
{
    TestInputType input = { "abacaba\nabaabc\n",};
    std::string expected = "2\n";
    levenstheinDistTest(input, expected);
    input.clear();
    expected.clear();

    input = { "innokentiy\ninnnokkentia\n" };
    expected = "3\n";
    levenstheinDistTest(input, expected);
    input.clear();
    expected.clear();

    input = { "rab\nbog\n" };
    expected = "3\n";
    levenstheinDistTest(input, expected);
    input.clear();
    expected.clear();
}

using DataType = uint64_t;
using Distance = uint16_t;

// Расстояние общей части для двух пар итераторов.
template<class I> auto commonPartLength(I abegin, I aend, I bbegin, I bend)
{
    return std::distance(abegin, std::mismatch(abegin, aend, bbegin, bend).first);
} 

// Маскируем в string_view общие префиксы и суффиксы.
static inline void dropCommonPrefixAndSuffix(std::string_view& a, std::string_view& b)
{
	auto prefix = commonPartLength(a.begin(), a.end(), b.begin(), b.end());
	a.remove_prefix(prefix);
	b.remove_prefix(prefix);

    auto suffix = commonPartLength(a.rbegin(), a.rend(), b.rbegin(), b.rend());
	a.remove_suffix(suffix);
    b.remove_suffix(suffix);
} 

void levenstheinDistWrapper(std::istream& in, std::ostream& out)
{
    std::string s1, s2;
    in >> s1;
    in >> s2;

    std::string_view a(s1);
    std::string_view b(s2);
    if (a.length() > b.length()) std::swap(a,b);
    dropCommonPrefixAndSuffix(a, b);

    size_t dpLength = b.length() + 1;
    std::vector<Distance> dpVector(dpLength);

	auto dp = dpVector.data();
    
    // осталась различающаяся часть - в худшем случае на каждом шаге увеличиваем расстояние.
    std::iota(dp, dp + dpLength, 0);
    for (size_t i = 1; i < a.length() + 1; ++i)
    {
        auto temp = dp[0]++;
		for (size_t j = 1; j < dpLength; ++j)
		{
            // Три значения для перехода динамики.
			auto p = dp[j - 1];
			auto r = dp[j];
			temp = std::min(
			    std::min(r, p) + 1,
			    temp + (a[i - 1] == b[j - 1] ? 0 : 1)
			);
			std::swap(dp[j], temp);
//            std::cout << "dpVector ";
//            for (auto el: dpVector)
//                std::cout << std::to_string(el) << " ";
//            std::cout << "\n";
		}
	}

	out << dp[dpLength - 1] << std::endl;
}

int main(int argc, char** argv)
{
//    std::ios_base::sync_with_stdio(false);
//    std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        levenstheinDistTestWrapper();
    else
        levenstheinDistWrapper(std::cin, std::cout);
    std::cout << "\n";
}
