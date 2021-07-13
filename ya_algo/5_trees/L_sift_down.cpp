#include <vector>
#include <cassert>
#include <cstdint>
#include "solution.h"

using IdxType = size_t;
using DataType = int;

int siftDown(std::vector<int>& h, int idx)
{
    IdxType left = 2 * idx;
    IdxType right = left + 1;

    IdxType maxIdx = right < h.size() && h[left] < h[right] ? right : left;
    while (left < h.size() && h[idx] < h[maxIdx])
    {
        DataType buf = h[maxIdx];
        h[maxIdx] = h[idx];
        h[idx] = buf;
  
        idx = maxIdx;
        left = 2 * idx;
        right = left + 1;
        maxIdx = right < h.size() && h[left] < h[right] ? right : left;
    }
    return idx;
}
/*
int siftUp(std::vector<int>& h, int idx)
{
    if (idx == 1)
        return idx;
    IdxType parent = idx / 2;

    if (h[idx] > h[parent])
    {
        DataType buf = h[parent];
        h[parent] = h[idx];
        h[idx] = buf;
        return siftUp(h, parent);
    }
    return idx;
}
*/
int siftUp(std::vector<int>& h, int idx)
{
    if (idx == 1)
        return idx;

    IdxType parent = idx / 2;
    while (idx > 1 && h[idx] > h[parent])
    {
        DataType buf = h[parent];
        h[parent] = h[idx];
        h[idx] = buf;

        idx = parent;
        parent = idx / 2;
    }
    return idx;
}

/*
void test()
{
    std::vector<int> sample = {-1, 12, 1, 8, 3, 4, 7};
    assert(siftDown(sample, 2) == 5);
}

int main()
{
    test();
}*/
