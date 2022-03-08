#ifndef NUMBER_GENERATOR_HPP
#define NUMBER_GENERATOR_HPP

#define DEFAULT_SEED 1234

#include <random>
#include <vector>
#include <cstdint>

using namespace std;

struct number_generator_t {

public:

    number_generator_t(int int_bits, int frac_bits, int out_bits);

    number_generator_t(int int_bits, int frac_bits, int out_bits, int seed);

    void setSeed(int seed);

    vector<float> generate_fixed_point(int num_values);

    vector<float> generate_fixed_point(int num_values, bool neg);

    vector<float> generate_low_fixed_point(int num_values);

    vector<float> generate_low_fixed_point(int num_values, bool neg);

    vector<int64_t> generate_high_fixed_point(int num_values);

    vector<int64_t> generate_high_fixed_point(int num_values, bool neg);

private:

    mt19937 random_number_generator;

    int int_bits;

    int frac_bits;

    int out_bits;

    int seed;
};

#endif