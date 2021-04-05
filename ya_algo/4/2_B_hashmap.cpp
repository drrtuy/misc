// 50167959
// Код не изменился - номер запуска тоже.
/*
    HashMap с open addressing в качестве collision avoidance. Пробирование с помощью
    двойного хэширования. В качестве хэш функций взял миксеры из некриптографических
    Murmur3C и xxHash. Номер корзины вычисляется как остаток от деления хэша на capacity
    вектора, используемого для хранения - capacity это ближайшее к требуемому простое
    число из списка.
    Вектор хранит таплы типа BucketType: {K, V, hash}.
    Средняя временная сложность операций O(1).
    Пространственная сложность O(n).
    Сложность rehashing, наступающего при достижении 0.85 от capacity, равна O(n) по времени и памяти.
*/

#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <sstream>
#include <algorithm>

void HashMapWrapper(std::istream& in, std::ostream& out);

void HashMapTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    HashMapWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void HashMapTestWrapper()
{
    TestInputType input = { "10\n", "get 1\n", "put 1 10\n", "put 2 4\n", "get 1\n", "get 2\n", "delete 2\n", "get 2\n", "put 1 5\n", "get 1\n", "delete 2\n" };
    std::string expected = "None\n10\n4\n4\nNone\n5\nNone\n";
    HashMapTest(input, expected);
    input.clear();
    expected.clear();

    input = { "8\n", "get 9\n", "delete 9\n", "put 9 1\n", "get 9\n", "put 9 2\n", "get 9\n", "put 9 3\n", "get 9\n"};
    expected = "None\nNone\n1\n2\n3\n";
    HashMapTest(input, expected);
    input.clear();
    expected.clear();
}

using HashMapKVType = uint32_t;
using HashType = uint32_t;
using IdxElemType = size_t;
static const std::string getCmd("get");
static const std::string putCmd("put");
static const std::string deleteCmd("delete");
static const std::string noneMsg("None");
static const std::string emptyMsg("");

namespace detail
{
static constexpr const size_t primeList[] =
{
    2llu, 3llu, 5llu, 7llu, 11llu, 13llu, 17llu, 23llu, 29llu, 37llu, 47llu,
    127llu, 151llu, 197llu, 251llu, 313llu, 397llu,
	499llu, 631llu, 797llu, 1009llu, 1259llu, 1597llu, 2011llu, 2539llu,
	3203llu, 4027llu, 5087llu, 6421llu, 8089llu, 10193llu, 12853llu, 16193llu,
	20399llu, 25717llu, 32401llu, 40823llu, 51437llu, 64811llu, 81649llu,
	102877llu, 129607llu, 163307llu, 205759llu, 259229llu, 326617llu,
	411527llu, 518509llu, 653267llu, 823117llu, 1037059llu, 1306601llu,
	1646237llu, 2074129llu, 2613229llu, 3292489llu, 4148279llu, 5226491llu,
	6584983llu, 8296553llu, 10453007llu, 13169977llu, 16593127llu, 20906033llu,
	26339969llu, 33186281llu, 41812097llu, 52679969llu, 66372617llu,
	83624237llu, 105359939llu, 132745199llu, 167248483llu, 210719881llu,
	265490441llu, 334496971llu, 421439783llu, 530980861llu, 668993977llu,
	842879579llu, 1061961721llu
};
// Ближайшее к искомому простое число нужно, чтобы не пропускать ячейки.
// Я не стал это писать - это, как бы, понятно.
// Для ускорения поиска следующего простого при небольших входных данных hash map 
// маленьких размеров стоит поделить список на две части, чтобы искать
// следующее простое в массиве меньшего размера. Я взял из исходного кода sherwood_map,
// но, так как, я увеличил capacity по-умолчанию - эта оптимизация менее актуальна.
size_t nextPrime(size_t size)
{
	auto small_end = std::begin(primeList) + 8;
	auto result = std::lower_bound(std::begin(primeList), small_end, size);
	if (result == small_end) return *std::lower_bound(small_end, std::end(primeList), size);
	else return *result;
}

#define XXH_PRIME32_2  0x85EBCA77U  /*!< 0b10000101111010111100101001110111 */
#define XXH_PRIME32_3  0xC2B2AE3DU  /*!< 0b11000010101100101010111000111101 */
inline HashType XXH32_avalanche(HashType h32)
{
    h32 ^= h32 >> 15;
    h32 *= 0x85EBCA77U;
    h32 ^= h32 >> 13;
    h32 *= 0xC2B2AE3DU;
    h32 ^= h32 >> 16;
    return(h32);
}

// Murmur 3c 32 hash mixer
inline uint32_t MM3_fmix(uint32_t h)
{
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;

    return h | 0x00000001;
}

}

class HashMap
{
public:
    HashMap(size_t capacity = 100): mSize(0)
    {
        BucketType emptyBucket = { 0, 0, emptyHash };
        mEntries = std::vector<BucketType>(detail::nextPrime(capacity), emptyBucket);
    }

    std::string put(const HashMapKVType key, const HashMapKVType value)
    {
        if (mSize + 1 > mEntries.capacity() * mLoadFactor)
            grow();

        HashType hash = 0;
        BucketIter bucketIter = _probe(key, hash);
        *bucketIter = { key, value, hash };
        ++mSize;
        return emptyMsg;
    }

    std::string get(const HashMapKVType key)
    {
        BucketIter bucketIter = _probe(key);
        return bucketIter->hash != emptyHash
            ? std::to_string(bucketIter->value)
            : noneMsg;
    }

    std::string erase(const HashMapKVType key)
    {
        BucketIter bucketIter = _probe(key);
        if (bucketIter->hash != emptyHash)
        {
            bucketIter->hash = deletedHash;
            return std::to_string(bucketIter->value);
        }

        return noneMsg;
    }

private:
    struct BucketType
    {
        HashMapKVType key;
        HashMapKVType value;
        HashType hash;
    };

    using BucketIter = std::vector<BucketType>::iterator;
    // Два magic-а для функционирования _probe.
    static constexpr size_t emptyHash = std::numeric_limits<HashMapKVType>::max();
    static constexpr size_t deletedHash = std::numeric_limits<HashMapKVType>::max() - 1;

    void grow()
    {
        size_t newSize = detail::nextPrime(mEntries.capacity() * 2);
        BucketType emptyBucket = { 0, 0, emptyHash };
        std::vector<BucketType> newEntries = std::vector<BucketType>(newSize, emptyBucket);
        mEntries.swap(newEntries);
        for (auto& entry: newEntries)
        {
            HashType hash = entry.hash;
            switch (hash)
            {
                case deletedHash:
                case emptyHash:
                    break;
                default:
                {
                    BucketIter bucketIter = _probe(entry.key, entry.hash);
                    *bucketIter = entry;
                    break;
                }
            }
        }
    }

    inline BucketIter _probe(HashMapKVType key)
    {
        HashType unused = 0;
        return _probe(key, unused);
    }

    inline BucketIter _probe(HashMapKVType key, HashType& aHash)
    {
        size_t i = 0;
        size_t bucketIdx = 0;
        HashType hash = 0;
        BucketIter iter;
        // Годная оптимизация.
        auto hash1 = _hash1(key);
        do
        {
            // opt
            iter = mEntries.begin();
            hash = hash1 + _hash2(i++);
            bucketIdx = hash % mEntries.size();
            std::advance(iter, bucketIdx);
        } while (iter->hash != emptyHash && (iter->hash == deletedHash || iter->key != key));
        aHash = hash;
        return iter; 
    }

    HashType _hash1(const HashMapKVType key)
    {
        return detail::MM3_fmix(key);
    }

    HashType _hash2(const HashMapKVType key)
    {
        return detail::XXH32_avalanche(key);
    }

    std::vector<BucketType> mEntries;
    size_t mSize;
    float mLoadFactor = 0.85;
};

void HashMapWrapper(std::istream& in, std::ostream& out)
{
    size_t n = 0;
    in >> n;
    HashMap hashmap;
    for (size_t i = 0; i < n; ++i)
    {
        std::string commandString;
        HashMapKVType key = 0;
        in >> commandString >> key;
        if (commandString == putCmd) 
        {
            HashMapKVType value = 0;
            in >> value;
            out << hashmap.put(key, value);
        }
        else if (commandString == getCmd)
        {
            out << hashmap.get(key) << "\n" ;
        }
        else if (commandString == deleteCmd)
        {
            out << hashmap.erase(key) << "\n";
        }
    }
}

int main(int argc, char** argv)
{
    //std::ios_base::sync_with_stdio(false);
    //std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
    {
        HashMapTestWrapper();
    }
    else
        HashMapWrapper(std::cin, std::cout);
    std::cout << "\n";
}
