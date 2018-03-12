#ifndef RANDOM_H_asdfjhw34inxth
#define RANDOM_H_asdfjhw34inxth


// C++ only code goes here
#ifdef __cplusplus

#include <iostream>
#include <random>

namespace pcs
{
inline double gen_rand_nr()
{
    static std::random_device dev;
    static std::mt19937 mt{dev()};
    static std::uniform_real_distribution<double> dist{0.0, 1.0};
    return dist(mt);
}
} // pcs

#endif

// mixed C/C++ code goes here
#ifdef __cplusplus
extern "C"
{
#endif

double pcs_gen_rand_nr();

#ifdef __cplusplus
}
#endif

#endif
