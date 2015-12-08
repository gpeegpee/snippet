#include <vector>
#include <stdint.h>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <cfloat>
#include <fstream>
#include <ostream>
#include <string>
#include <sstream>
#include <time.h>  

using namespace std;


#ifndef _MSC_VER
#   define UNLIKELY(expr) __builtin_expect(!!(expr), 0)
#   define LIKELY(expr)   __builtin_expect(!!(expr), 1)
#else
#   define UNLIKELY(expr) (expr)
#   define LIKELY(expr)   (expr)
#endif


#if defined(__GNUC__) || defined(__HP_aCC) || defined(__clang__)
    #define INLINE inline __attribute__((always_inline))
#else
    #define INLINE __forceinline
#endif


// Force clang to use conditional move instead of branches. For other types of T than 64-bit integers, please
// rewrite the assembly or use the ternary operator below instead.
template <class T> INLINE size_t choose(T a, T b, size_t src1, size_t src2)
{
#if defined(__clang__) && defined(__x86_64)
    size_t res = src1;
    asm("cmpq %1, %2; cmovaeq %4, %0"
        :
    "=q" (res)
        :
        "q" (a),
        "q" (b),
        "q" (src1),
        "q" (src2),
        "0" (res)
        :
        "cc");
    return res;
#else
    return b >= a ? src2 : src1;
#endif
}


template <class T> INLINE size_t fast_upper_bound0(const vector<T>& vec, T value)
{
    return std::upper_bound(vec.begin(), vec.end(), value) - vec.begin();
}


template <class T> INLINE size_t fast_upper_bound1(const vector<T>& vec, T value)
{
    size_t size = vec.size();
    size_t i = 0;
    size_t size_2 = size;

    while (size_2 > 0) {
        size_t half = size_2 / 2;
        size_t mid = i + half;
        T probe = vec[mid];
        if (value >= probe) {
            i = mid + 1;
            size_2 -= half + 1;
        }
        else {
            size_2 = half;
        }
    }
    return i;
}


template <class T> INLINE size_t fast_upper_bound2(const vector<T>& vec, T value)
{
    size_t m_len = vec.size();
    size_t low = -1;
    size_t high = m_len;

    while (high - low > 1) {
        size_t probe = (low + high) / 2;
        T v = vec[probe];
        if (v > value)
            high = probe;
        else 
            low = probe;
    }

    if (high == m_len) 
        return m_len;
    else 
        return high;
}


template <class T> INLINE size_t fast_upper_bound3(const vector<T>& vec, T value)
{
    size_t size = vec.size();
    size_t low = 0;

    while (size > 0) {
        size_t half = size / 2;
        size_t other_half = size - half;
        size_t probe = low + half;
        size_t other_low = low + other_half;
        T v = vec[probe];
        size = half;
        // clang won't use conditional move here, so we have made a choose() function instead
        // low = v <= value ? other_low : low; 
        low = choose(v, value, low, other_low);
    }

    return low;
}


template <class T> INLINE size_t fast_upper_bound4(const vector<T>& vec, T value)
{
    size_t size = vec.size();
    size_t low = 0;

    while (size >= 8) {
        size_t half = size / 2;
        size_t other_half = size - half;
        size_t probe = low + half;
        size_t other_low = low + other_half;
        T v = vec[probe];
        size = half;
        low = choose(v, value, low, other_low);

        half = size / 2;
        other_half = size - half;
        probe = low + half;
        other_low = low + other_half;
        v = vec[probe];
        size = half;
        low = choose(v, value, low, other_low);

        half = size / 2;
        other_half = size - half;
        probe = low + half;
        other_low = low + other_half;
        v = vec[probe];
        size = half;
        low = choose(v, value, low, other_low);
    }

    while (size > 0) {
        size_t half = size / 2;
        size_t other_half = size - half;
        size_t probe = low + half;
        size_t other_low = low + other_half;
        T v = vec[probe];
        size = half;
        low = choose(v, value, low, other_low);
    };

    return low;
}


template<int version, class T> INLINE void benchmark(const vector<T>& v, ostream& out)
{
    const size_t iterations = 1000000;
    unsigned long long best = 0;

    // We take best of 10; a run that is slower than the fastest must be affected by outside disturbance.
    for (size_t bestof = 0; bestof < 10; bestof++)
    {
        unsigned long long ticks = clock();

        for (size_t iter = 0; iter < iterations; iter++) {
            // Chose an index to search for. Our random number generation must be super fast because the 
            // benchmarked work that comes after is relatively short
            T findval = v[(iter * 980944451) % v.size()];

            // Volatile to prevent the compiler from optimizing away the search because result is unused
            volatile size_t match = 0;
            static_cast<void>(match);

            if (version == 0)
                match = fast_upper_bound0(v, findval);
            else if (version == 1)
                match = fast_upper_bound1(v, findval);
            else if (version == 2)
                match = fast_upper_bound2(v, findval);
            else if (version == 3)
                match = fast_upper_bound3(v, findval);
            else if (version == 4)
                match = fast_upper_bound4(v, findval);
            else
                assert(false);

            // Compare with std::upper_bound() to verify that our implementations work correctly. 
            // Important: Compile with -DNDEBUG for gcc and clang when benchmarking
            size_t expected = std::upper_bound(v.begin(), v.end(), findval) - v.begin();
            static_cast<void>(expected);
            assert(match == expected);
        }

        // Note, this can wrap over, giving a bad timing once in a while. Be aware.
        ticks = clock() - ticks; 
        if (best == 0 || ticks < best)
            best = ticks;
    }

    if (version == 0)
        out << "    stl      : ";
    else
        out << "    version " << version << ": ";

    out << (double)best / CLOCKS_PER_SEC * 1000  << " miliseconds\n";
}


int main(int argc, char* argv[])
{
    // Our vector to search in. We use size_t because it's 32 bits on 32-bit CPUs and 64 bits on 64-bit CPUs
    vector<size_t> v;

    for (size_t size = 8 * 1024; size <= 8 * 1024; size *= 8) {
        cerr << "size = " << size << ":\n";

        // size_t value = 0; // Use this if the 2 lines below won't compile
        typedef decltype(v)::value_type T;
        T value = T(0);
        
        // Fill the vector with random values that are sorted increasingly
        for (size_t t = 0; t < size; t++) {
            v.push_back(value);
            value += (rand() % 1000) + 1;
        }

        benchmark<0>(v, cerr);
        benchmark<1>(v, cerr);
        benchmark<2>(v, cerr);
        benchmark<3>(v, cerr);
        benchmark<4>(v, cerr); 
        cerr << "\n";
    }
	return 0;
}


