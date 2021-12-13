#include <cstdlib>
#include <iostream>
#include <cstring>

void randomfill_o(uint64_t *out, size_t n, uint64_t x, uint64_t a, uint64_t c)
{
    for (; n; n--)
    {
        x = x * a + c;
        *out++ = x;
    }
}

//dissect to get graph labels
/*void randomfill(uint64_t *out, size_t n, uint64_t x, uint64_t a, uint64_t c)
{
1    if (n > 0)     // cmp n,0 
     {
2        x *= a;    // imul x, a
3        x += c;    // add x, c depends on 2
4        *out = x;  // mov [out], x depends on 3
5        out++;     // add out + 8
6        n--;       // dec n
    }
}
Lines 2, 3, 4 constitutes crit section IMHO
*/

constexpr const size_t vector_byte_size = 32; // AVX2
constexpr const size_t vector_size = vector_byte_size / sizeof(uint64_t);
typedef unsigned long long v8ui __attribute__ ((vector_size (vector_byte_size)));

// Re-write the algo to vectorize the execution w/o excessive penalties with small n 
void randomfill_v(uint64_t *out, size_t n, uint64_t x, uint64_t a, uint64_t c)
{
    if (!n)
        return;

    size_t vectorized_iters = n / vector_size;
    size_t vect_upper_bound = vectorized_iters * vector_size;
    size_t non_vect_iters =  n - vect_upper_bound;
    v8ui pow_of_a, poly_remainder;
    v8ui x_vector = { x, x, x, x};

    // The run function is sum(x_i in 1, n) where
    // x_i = x * a ** n + (a ** (n-1) + a ** (n-2) ... + 1) * c
    // This block fills in power of a and the sum leftover vectors. 
    if (vectorized_iters)
    {
        pow_of_a[0] = a;
        poly_remainder[0] = c; poly_remainder[1] = 0; poly_remainder[2] = 0; poly_remainder[3] = 0;
        for (uint32_t i = 1; i < vector_size; ++i)
        {
            uint32_t prev_i = i-1;
            pow_of_a[i] = pow_of_a[prev_i] * a;
            poly_remainder[i] += poly_remainder[prev_i] + c * pow_of_a[prev_i];
        }
    }
    // Main vectorize loop. NB It is hard to get the most effective code
    // out of compiler's auto-vectorization runs. Better to generate code using
    // intrinsics.
    for (size_t i = 0; i < vect_upper_bound;)
    {
        for (size_t it = 0; it < vector_size; ++it)
            out[i + it] = x_vector[it] * pow_of_a[it] + poly_remainder[it];

        for (size_t it = 0; it < vector_size; ++it)
            x_vector[it] = out[i+vector_size-1];

        i+= vector_size;
    }

    x = x_vector[vector_size - 1];

    // Remainder processing
    size_t it, cur_it;
    if (non_vect_iters)
    {
        out[vect_upper_bound] = x * a;
        it = vect_upper_bound + 1;
        out[vect_upper_bound] += c;
    }
    for (; it < n;)
    {
        out[it] = out[it-1] * a;
        cur_it = it++;
        out[cur_it] += c;
    }
}

int main()
{
    const constexpr size_t length = 15;
    uint64_t dst[length];
    memset(dst, 0, length*sizeof(decltype(dst[0])));
    randomfill_o(dst, sizeof(dst)/sizeof(dst[0]), 1, 2, 3);
    for (size_t i = 0; i < length; ++i)
        std::cout << dst[i] << " ";
    std::cout << std::endl;
    
    memset(dst, 0, length*sizeof(decltype(dst[0])));
    randomfill_v(dst, sizeof(dst)/sizeof(dst[0]), 1, 2, 3);
    for (size_t i = 0; i < length; ++i)
        std::cout << dst[i] << " ";
    std::cout << std::endl;
}
