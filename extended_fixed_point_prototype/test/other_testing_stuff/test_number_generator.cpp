#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>

void test_selection();
void generate_test_values(int, int, int, int, int);

/**
 * Program to generate random numbers specifying the amount of integer and fractional bits
 */

int main() {
    test_selection();
}

void test_selection(){
    int num_generated_values;
    int num_integer_bits;
    int num_fractional_bits;
    int num_discarded_integer_bits;
    int num_discarded_fractional_bits;

    printf("*************************************\n");
    printf("*           TEST GENERATOR          *\n");
    printf("*************************************\n\n\n");

    printf("Number of values to generate\n");
    printf("> ");
    scanf("%d",&num_generated_values);

    printf("Number of bits in the integer part\n");
    printf("> ");
    scanf("%d", &num_integer_bits);

    printf("Number of bits in the fractional part\n");
    printf("> ");
    scanf("%d", &num_fractional_bits);

    printf("Number of zero bits in the integer part starting from left\n");
    printf("> ");
    scanf("%d", &num_discarded_integer_bits);

    printf("Number of zero bits in the fractional part starting from left\n");
    printf("> ");
    scanf("%d", &num_discarded_fractional_bits);

    generate_test_values(num_generated_values, num_integer_bits, num_fractional_bits, num_discarded_integer_bits, num_discarded_fractional_bits);
}

void generate_test_values(int num_generated_values, int num_integer_bits, int num_fractional_bits, int num_discarded_integer_bits, int num_discarded_fractional_bits) {
    srand(time(NULL));
    std::vector<double> generated_random_numbers(num_generated_values);
    
    for(int i = 0; i < num_generated_values; ++i){
        // Integer part computation
        for(int k = num_discarded_integer_bits; k < num_integer_bits; ++k)
            generated_random_numbers[i] += (rand() % 2) * pow(2, k);    
        // Fractional part computation
        for(int k = num_discarded_fractional_bits + 1; k <= num_fractional_bits; ++k)
            generated_random_numbers[i] += (rand() % 2) * pow(2 , -k);
    }

    for(int i = 0; i < num_generated_values; ++i)
        printf("%f\n", generated_random_numbers[i]);

    std::ofstream out_file("./test/other_testing_stuff/random_numbers.txt");

    for(int i = 0; i < num_generated_values; ++i)
        out_file << std::setprecision(6) << generated_random_numbers[i] << ", ";
        
    out_file.close();
}