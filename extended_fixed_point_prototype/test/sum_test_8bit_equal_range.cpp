#define BOOST_TEST_MODULE Sum_Test_8bit_equal_range

#include "extended_fixed_point.hpp"
#include <iostream>
#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

template<int16_t INT_PART, int16_t FRAC_PART>
void sum_only_fractional_numbers(float v1, float v2);

template<int16_t INT_PART, int16_t FRAC_PART>
void sum_only_integer_numbers(float v1, float v2);

using namespace boost;
namespace bdata = boost::unit_test::data;

// Sum test for extended_fixed_point represented with int8_t 
// Test of sum between extended_fixed_point with the same range
// e.g. extended_fixed_point<-2,7> a, and extended_fixed_point<-2,7> 

const float values_test_1_efp1[] = {0.890625, -0.765625, 0.015625, -0.25, 0.65625, -0.171875, -0.703125, 0.484375, 0.34375, 0.515625};
const float values_test_1_efp2[] = {0.031250, 0.140625, -0.28125, 0.140625, -0.265625, 0.65625, 0.0625, 0.3125, 0.125, -0.78125};

/*
 * Sum test number 1:
 * Extended_fixed_point_1 with INT_PART = 0 and FRAC_PART = 7
 * Extended_fixed_point 2 with INT_PART = 0 and FRAC_PART = 7
 * 
 * Test executed: v1 + v2 and v2 + v1
 * Due to the approximation in the casting operations, a tolerance has been set and
 * the sum can't deviate from the exact result of value major of the tolerance
 * TOLERANCE = 1e-1
*/ 
BOOST_DATA_TEST_CASE(Sum_test_8bit_equal_range_1, bdata::make(values_test_1_efp1)^bdata::make(values_test_1_efp2), v1, v2) {
    const int16_t INT_PART = 0;
    const int16_t FRAC_PART = 7;

    sum_only_fractional_numbers<INT_PART, FRAC_PART>(v1, v2);
}

/*
 * Sum test number 2
 * Extended_fixed_point_1 with INT_PART = -2 and FRAC_PART = 7
 * Extended_fixed_point 2 with INT_PART = -2 and FRAC_PART = 7
 * 
 * Test executed: v1 + v2 and v2 + v1
 * Due to the approximation in the casting operations, a tolerance has been set and
 * the sum can't deviate from the exact result of value major of the tolerance
 * TOLERANCE = 1e-1
*/ 
BOOST_DATA_TEST_CASE(Sum_test_8bit_equal_range_2, bdata::make(values_test_1_efp1)^bdata::make(values_test_1_efp2), v1, v2) {
    const int16_t INT_PART = -2;
    const int16_t FRAC_PART = 7;

    sum_only_fractional_numbers<INT_PART, FRAC_PART>(v1, v2);
}

/*
 * Sum test number 3:
 * Extended_fixed_point_1 with INT_PART = -4 and FRAC_PART = 7
 * Extended_fixed_point 2 with INT_PART = -4 and FRAC_PART = 7
 * 
 * Test executed: v1 + v2 and v2 + v1
 * Due to the approximation in the casting operations, a tolerance has been set and
 * the sum can't deviate from the exact result of value major of the tolerance
 * TOLERANCE = 1e-1
*/ 
BOOST_DATA_TEST_CASE(Sum_test_8bit_equal_range_3, bdata::make(values_test_1_efp1)^bdata::make(values_test_1_efp2), v1, v2) {
    const int16_t INT_PART = -4;
    const int16_t FRAC_PART = 7;

    sum_only_fractional_numbers<INT_PART, FRAC_PART>(v1, v2);
}

template<int16_t INT_PART, int16_t FRAC_PART>
void sum_only_fractional_numbers(float v1, float v2) {
    const float TOLERANCE = 1e-1;

    extended_fixed_point_t<INT_PART,FRAC_PART> efp1(v1);
    extended_fixed_point_t<INT_PART,FRAC_PART> efp2(v2);
    float correct_value = v1 + v2;

    extended_fixed_point_t<INT_PART,FRAC_PART> test1, test2;
    test1 = efp1 + efp2;
    test2 = efp2 + efp1;

    std::cout << "Sum of <" << INT_PART << "," << FRAC_PART << "> + <" << INT_PART << "," << FRAC_PART << ">\n";
    std::cout << v1 << " + " << v2 << " = " << test1 << "\n";
    BOOST_TEST(std::abs(test1.getValueF() - correct_value) < TOLERANCE);   

    std::cout << v2 << " + " << v1 << " = " << test2 << "\n\n";
    BOOST_TEST(std::abs(test2.getValueF() - correct_value) < TOLERANCE);
}

const float values_test_2_efp1[] = {1.5, 0.375, -2.75, 3.9375, -1.8125, 5.1875, 1.125, 0.125, 0, 6.75};
const float values_test_2_efp2[] = {1.6875, 4.4375, 4.25, 1.6875, -1.0625, -0.5, 2.8125, -0.9375, 0.5, -0.625};

/*
 * Sum test number 4:
 * Extended_fixed_point_1 with INT_PART = 3 and FRAC_PART = 4
 * Extended_fixed_point 2 with INT_PART = 3 and FRAC_PART = 4
 * 
 * Test executed: v1 + v2 and v2 + v1
 * Due to the approximation in the casting operations, a tolerance has been set and
 * the sum can't deviate from the exact result of value major of the tolerance
 * TOLERANCE = 1e-1
*/ 
BOOST_DATA_TEST_CASE(Sum_test_8bit_equal_range_4, bdata::make(values_test_2_efp1)^bdata::make(values_test_2_efp2), v1, v2) {
    const float TOLERANCE = 1e-1;
    const int16_t INT_PART = 3;
    const int16_t FRAC_PART = 4;

    extended_fixed_point_t<INT_PART,FRAC_PART> efp1(v1);
    extended_fixed_point_t<INT_PART,FRAC_PART> efp2(v2);
    float correct_value = v1 + v2;

    extended_fixed_point_t<INT_PART,FRAC_PART> test1, test2;
    test1 = efp1 + efp2;
    test2 = efp2 + efp1;

    std::cout << "Sum of <" << INT_PART << "," << FRAC_PART << "> + <" << INT_PART << "," << FRAC_PART << ">\n";
    std::cout << v1 << " + " << v2 << " = " << test1 << "\n";
    BOOST_TEST(std::abs(test1.getValueF() - correct_value) < TOLERANCE);   

    std::cout << v2 << " + " << v1 << " = " << test2 << "\n\n";
    BOOST_TEST(std::abs(test2.getValueF() - correct_value) < TOLERANCE); 
}

const int8_t values_test_3_efp1[] = {1, 4, -15, 45, -90, 120, 0, 127, 126, 127};
const int8_t values_test_3_efp2[] = {0, -8, 25, 8, -35, 7, -128, -128, 1, 0};

/*
 * Sum test number 5:
 * Extended_fixed_point_1 with INT_PART = 7 and FRAC_PART = 0
 * Extended_fixed_point 2 with INT_PART = 7 and FRAC_PART = 0
 * 
 * Test executed: v1 + v2 and v2 + v1
*/ 
BOOST_DATA_TEST_CASE(Sum_test_8bit_equal_range_5, bdata::make(values_test_3_efp1)^bdata::make(values_test_3_efp2), v1, v2) {
    const int16_t INT_PART = 7;
    const int16_t FRAC_PART = 0;

    sum_only_integer_numbers<INT_PART, FRAC_PART>(v1, v2); 
}

/*
 * Sum test number 6:
 * Extended_fixed_point_1 with INT_PART = 7 and FRAC_PART = -2
 * Extended_fixed_point 2 with INT_PART = 7 and FRAC_PART = -2
 * 
 * Test executed: v1 + v2 and v2 + v1
*/ 
BOOST_DATA_TEST_CASE(Sum_test_8bit_equal_range_6, bdata::make(values_test_3_efp1)^bdata::make(values_test_3_efp2), v1, v2) {
    const int16_t INT_PART = 7;
    const int16_t FRAC_PART = -2;

    sum_only_integer_numbers<INT_PART, FRAC_PART>(v1, v2);
}

/*
 * Sum test number 7:
 * Extended_fixed_point_1 with INT_PART = 7 and FRAC_PART = -4
 * Extended_fixed_point 2 with INT_PART = 7 and FRAC_PART = -4
 * 
 * Test executed: v1 + v2 and v2 + v1
*/ 
BOOST_DATA_TEST_CASE(Sum_test_8bit_equal_range_7, bdata::make(values_test_3_efp1)^bdata::make(values_test_3_efp2), v1, v2) {
    const int16_t INT_PART = 7;
    const int16_t FRAC_PART = -4;

    sum_only_integer_numbers<INT_PART, FRAC_PART>(v1, v2);
}

template<int16_t INT_PART, int16_t FRAC_PART>
void sum_only_integer_numbers(float v1, float v2) {
    extended_fixed_point_t<INT_PART,FRAC_PART> efp1(v1);
    extended_fixed_point_t<INT_PART,FRAC_PART> efp2(v2);
    int8_t correct_value = v1 + v2;

    extended_fixed_point_t<INT_PART,FRAC_PART> test1, test2;
    test1 = efp1 + efp2;
    test2 = efp2 + efp1;

    std::cout << "Sum of <" << INT_PART << "," << FRAC_PART << "> + <" << INT_PART << "," << FRAC_PART << ">\n";
    std::cout << (int16_t)v1 << " + " << (int16_t)v2 << " = " << test1 << "\n";
    BOOST_TEST(test1.getValueF() == correct_value);   

    std::cout << (int16_t)v2 << " + " << (int16_t)v1 << " = " << test2 << "\n\n";
    BOOST_TEST(test2.getValueF() == correct_value);
}