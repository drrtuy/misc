#ifndef FUNCTIONS
#define FUNCTIONS

typedef struct {
    float min;
    float max;
} min_max_t;

min_max_t *GetMinMax(float a, float b);
bool isEmbedded(min_max_t *rectang1, min_max_t *rectang2);

#endif
