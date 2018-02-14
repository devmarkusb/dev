#ifndef RANDOM_H_asdfjhw34inxth
#define RANDOM_H_asdfjhw34inxth

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
