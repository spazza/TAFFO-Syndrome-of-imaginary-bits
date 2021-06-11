#define BOOST_TEST_MODULE Sum_Test_8bit_different_range

#include "extended_fixed_point.hpp"
#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

template<int16_t INT_PART1, int16_t FRAC_PART1, int16_t INT_PART2, int16_t FRAC_PART2>
void sum_only_fractional_numbers(float v1, float v2);

using namespace boost;
namespace bdata = boost::unit_test::data;

const float values_test_1_efp1[] = {0.328125, 0.90625, 0.09375, 0.148438, 0.0390625, 0.445312, 0.570312, 0.625, 0.960938, 0.867188};
const float values_test_1_efp2[] = {0.65625, 0.40625, 0.5, 0.9375, 0.96875, 0.125, 0.1875, 0.46875, 0.40625, 0.71875};

BOOST_DATA_TEST_CASE(Sum_test_8bit_different_range_1, bdata::make(values_test_1_efp1)^bdata::make(values_test_1_efp2), v1, v2) {
    const int16_t INT_PART1 = 0;
    const int16_t FRAC_PART1 = 7;
    const int16_t INT_PART2 = -2;
    const int16_t FRAC_PART2 = 7;

    sum_only_fractional_numbers<INT_PART1, FRAC_PART1, INT_PART2, FRAC_PART2>(v1, v2);
}

template<int16_t INT_PART1, int16_t FRAC_PART1, int16_t INT_PART2, int16_t FRAC_PART2>
void sum_only_fractional_numbers(float v1, float v2) {
    const float TOLERANCE = 1e-1;

    extended_fixed_point_t<INT_PART1,FRAC_PART1> efp1(v1);
    extended_fixed_point_t<INT_PART2,FRAC_PART2> efp2(v2);
    float correct_value = v1 + v2;

    extended_fixed_point_t<INT_PART1,FRAC_PART1> test1;
    test1 = efp1 + efp2;

    std::cout << "Sum of <" << INT_PART1 << "," << FRAC_PART1 << "> + <" << INT_PART2 << "," << FRAC_PART2 << ">\n";
    std::cout << v1 << " + " << v2 << " = " << test1 << "\n";
    BOOST_TEST(std::abs(test1.getValueF() - correct_value) < TOLERANCE);   
}

// for the commutative property necessary another test, v2 + v1 ?

/*
const float values_test_2_efp1[] = {0.0078125, 0.460938, 0.289062, 0.382812, 0.640625, 0.71875, 0.15625, 0.171875, 0.492188, 0.632812};
const float values_test_2_efp2[] = {0.0625, 0.96875, 0.0625, 0.375, 0.3125, 0.3125, 0.96875, 0.5, 0.8125, 0.875};

BOOST_DATA_TEST_CASE(Sum_Test_8_bit_2, bdata::make(values_test_2_efp1)^bdata::make(values_test_2_efp2), v1, v2){
    float TOLERANCE = 1e-1;
    extended_fixed_point_t<0,7> efp1(v1);
    extended_fixed_point_t<-2,7> efp2(v2);
    float correct_value = v1 + v2;

    extended_fixed_point_t<0,7> test1;
    test1 = efp1 + efp2;

    extended_fixed_point_t<-2,7> test2;
    test2 = efp2 + efp1;

    std::cout << "Sum of " << v1 << " + " << v2 << " = " << test1 << std::endl;
    BOOST_TEST(std::abs(test1.getValueF() - correct_value) < TOLERANCE);   
}

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 
//printf("Binary value: " BYTE_TO_BINARY_PATTERN" " BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(efp1.getRaw()>>8), BYTE_TO_BINARY(efp1.getRaw()));
*/