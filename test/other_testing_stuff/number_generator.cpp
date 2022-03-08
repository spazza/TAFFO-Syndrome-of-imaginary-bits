#include "number_generator.hpp"

using namespace std;

number_generator_t::number_generator_t(int int_bits, int frac_bits, int out_bits) 
    : number_generator_t(int_bits, frac_bits, out_bits, DEFAULT_SEED) {}

number_generator_t::number_generator_t(int int_bits, int frac_bits, int out_bits, int seed) 
    : int_bits(int_bits), frac_bits(frac_bits), out_bits(out_bits), seed(seed) {
        random_number_generator = mt19937(seed);
}

void number_generator_t::setSeed(int seed) { this->seed = seed; }

vector<float> number_generator_t::generate_fixed_point(int num_values) {
    return generate_fixed_point(num_values, true);
}

vector<float> number_generator_t::generate_fixed_point(int num_values, bool neg) {
    vector<float> numbers(num_values);
    uniform_int_distribution<mt19937::result_type> dist01(0,1);

    for(int i = 0; i < num_values; ++i) {

        for(int k = 0; k < int_bits; ++k) 
            numbers[i] += dist01(random_number_generator) * pow(2, k);
    
        for(int k = 0; k < frac_bits; ++k) 
            numbers[i] += dist01(random_number_generator) * pow(2, -k); 
        
        if(neg)
            numbers[i] *= dist01(random_number_generator) == 0 ? 1 : -1;
    }

    return numbers;
}

vector<int64_t> number_generator_t::generate_high_fixed_point(int num_values) {
    return generate_high_fixed_point(num_values, true);
}

vector<int64_t> number_generator_t::generate_high_fixed_point(int num_values, bool neg) {
    vector<int64_t> numbers(num_values);
    uniform_int_distribution<mt19937::result_type> dist01(0,1);

    for(int i = 0; i < num_values; ++i) {
        for(int k = out_bits; k < (int_bits + out_bits); ++k) 
            numbers[i] += dist01(random_number_generator) * pow(2, k);
        if(neg)
            numbers[i] *= dist01(random_number_generator) == 0 ? 1 : -1;
    }
    
    return numbers;
}

vector<float> number_generator_t::generate_low_fixed_point(int num_values) {
    return generate_low_fixed_point(num_values, true);
}

vector<float> number_generator_t::generate_low_fixed_point(int num_values, bool neg) {
    vector<float> numbers(num_values);
    uniform_int_distribution<mt19937::result_type> dist01(0,1);

    for(int i = 0; i < num_values; ++i) {
        for(int k = 0; k < (frac_bits - out_bits); ++k) 
             numbers[i] += dist01(random_number_generator) * pow(2, k); 

        if(neg)
            numbers[i] *= dist01(random_number_generator) == 0 ? 1 : -1;

        int64_t one = ((int64_t)1) << frac_bits;
        numbers[i] /= one;
    }

    return numbers;
}