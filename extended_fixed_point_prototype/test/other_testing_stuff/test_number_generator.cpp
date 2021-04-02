#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

int main(int argc, char *argv[]) {
    
    if(argc == 3) {
        srand(time(NULL));
        int num_values = atoi(argv[1]);
        int num_bits = atoi(argv[2]);

        std::vector<double> generated_random_numbers(num_values);
    
        for(int i = 0; i < num_values; ++i)
            for(int j = 1 ; j <= num_bits; ++j)
                generated_random_numbers[i] += (rand() % 2) * pow(2 , -j);
        
        for(int i = 0; i < num_values; ++i)
            printf("%f\n", generated_random_numbers[i]);

        std::ofstream out_file("./test/other_testing_stuff/random_numbers.txt");

        for(int i = 0; i < num_values; ++i)
            out_file << generated_random_numbers[i] << ", ";
        
        out_file.close();

    } else {
        printf("Wrong command line input (Num of necessary values) (Num of bits)\n");
    }
}