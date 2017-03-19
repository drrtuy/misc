#include "MultiFileProgram_2.h"

min_max_t *GetMinMax(float a, float b)
{
    min_max_t *result;
    result = new min_max_t;
    if (a > b) {
        result->min = b;
        result->max = a;
    } else {
        result->max = b;
        result->min = a;
    } 
    return result;
}

bool isEmbedded(min_max_t *rectang1, min_max_t *rectang2)
{
    bool result = false;
    if (rectang1->max <= rectang2->min) {
        result = true;
    } 

    return result;
}
