// 50268896
// Индекс это map<индексированное слово, map<номер документа, кол-во вхождений слова>>.
// Сначала индексируем документы, затем проходим по индексу со списком уникальных слов
// из запроса и подсчитываем релевантность, суммируя вхождения слов поискового запроса
// в очередном документе индекса. Перед выдачей сортируем пары <номер документа, релевантность>
// по невозрастанию релевантности и неубыванию номера.
// Сложность по CPU O(n*m + k*p), где n - кол-во индексируемых документов, m - сред. кол-во слов в документе,
//      k - кол-во запросов, n - среднее кол-во уникальных слов в запросе.
// Сложность по RAM O(n*p + r), где q - кол-во индексируемых документов, p - сред. кол-во символов в документе,
// r - максимальная длина поискового запроса в байтах.
#include <iostream>
#include <vector>
#include <array>
#include <cassert>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cstdio>

constexpr size_t TOP_DOCUMENTS_TO_SEARCH = 5UL;

void IndexWrapper(std::istream& in, std::ostream& out);
class Index
{
  private:
    using DocWordCounterType = std::unordered_map<uint64_t, uint64_t>;
    using IndexType = std::unordered_map<std::string, DocWordCounterType>;
    using DocIdx = int64_t;
    using RelevancyMap = std::unordered_map<DocIdx, size_t>;
    using UniqueWordSet = std::unordered_set<std::string>;

  public:
    struct DocRelevancy
    {
        DocIdx docIdx;
        size_t relevancy;

        bool operator<(const DocRelevancy& rhs)
        {
            if (relevancy == rhs.relevancy)
                return docIdx < rhs.docIdx;
            return relevancy > rhs.relevancy;
        }
    };

  private:
    std::string findTop5(const RelevancyMap& docRelevancyMap)
    {
        std::ostringstream oss;
        std::vector<DocRelevancy> docRelevancyVec;
        for (const auto& [docIdx, relevancy]: docRelevancyMap)
            docRelevancyVec.push_back({docIdx, relevancy});
        // А то я думаю, почему dtor docRelevancyVec падает.
        // Тайминг на последнем тесте снизились процентов на 8 с partial_sort.
        auto middle = docRelevancyVec.begin();
        size_t elementsNumber = std::min(docRelevancyVec.size(), TOP_DOCUMENTS_TO_SEARCH);
        std::advance(middle, elementsNumber);
        std::partial_sort(docRelevancyVec.begin(), middle, docRelevancyVec.end());
        for (size_t i = 0; i < elementsNumber; ++i)
            oss << docRelevancyVec[i].docIdx << " ";
        return oss.str();
    }

    IndexType mIndex;

  public:
    Index() { };
    void put(const std::string& doc, size_t docIdx)
    {
        std::istringstream iss(doc);
        std::string word;
        while(iss >> word)
            ++mIndex[word][docIdx];
    }

    std::string search(const std::string& query)
    {
        std::istringstream iss(query);
        std::string word;
        RelevancyMap docRelevancyMap;
        UniqueWordSet queryWordSet;

        while (iss >> word)
            queryWordSet.insert(word);

        for (auto& uniqueWord: queryWordSet)
        {
            for (const auto& [docIdx, count]: mIndex[uniqueWord])
                docRelevancyMap[docIdx] += count;
        }
        return findTop5(docRelevancyMap); 
    }
};

void IndexTest(std::vector<std::string>& input, std::string& expected)
{
    std::stringstream in;
    std::stringstream ss;
    for (auto& e: input)
        in << e;
    IndexWrapper(in, ss);
    std::string out = ss.str();
    std::cout << out;
    assert(out == expected);
}

using TestInputType = std::vector<std::string>;
void IndexTestWrapper()
{
    Index::DocRelevancy r = { 1, 2 };
    Index::DocRelevancy l = { 2, 2 };
    assert(!(l < r));

    r = { 1, 3 };
    l = { 2, 2 };
    assert(!(l < r));

    TestInputType input = {"3\n","i love coffee\n","coffee with milk and sugar\n","free tea for everyone\n","3\n","i like black coffee without milk\n","everyone loves new year\n","mary likes black coffee without milk\n",};
    std::string expected = "1 2 \n3 \n2 1 \n";
    IndexTest(input, expected);
    input.clear();
    expected.clear();

    input = { "6\n", "buy flat in moscow\n", "rent flat in moscow\n", "sell flat in moscow\n", "want flat in moscow like crazy\n", "clean flat in moscow on weekends\n", "renovate flat in moscow\n", "1\n", "flat in moscow for crazy weekends\n" }; 
    expected = "4 5 1 2 3 \n";
    IndexTest(input, expected);
    input.clear();
    expected.clear();

    input = { "1\n", "buy buy flat in moscow\n", "1\n", "flat flat in buy buy buy moscow for crazy weekends\n" }; 
    expected = "1 \n";
    IndexTest(input, expected);
    input.clear();
    expected.clear();
}

void IndexWrapper(std::istream& in, std::ostream& out)
{
    // Имена переменных даны в задании, IMHO это "говорящие" имена переменных
    // для имеющего контекст после прочтения задания.
    size_t n = 0;
    size_t m = 0;
    in >> n >> std::ws;
    Index index;
    for (size_t i = 1; i <= n; ++i)
    {
        std::string doc;
        std::getline(in, doc);
        index.put(doc, i);
    }
    
    in >> m >> std::ws;
    for (size_t i = 1; i <= m; ++i)
    {
        std::string query;
        std::getline(in, query);
        out << index.search(query) << "\n";
    }
}

int main(int argc, char** argv)
{
    //std::ios_base::sync_with_stdio(false);
    //std::cin.tie(NULL);
    // put any argument to follow unit testing path
    if (argc > 1)
        IndexTestWrapper();
    else
        IndexWrapper(std::cin, std::cout);
    std::cout << "\n";
}
