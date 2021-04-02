#define BOOST_TEST_MODULE Sum_Test_8_bits
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

#include "extended_fixed_point.hpp"
#include <vector>
#include <iostream>

#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

using namespace boost;
namespace bdata = boost::unit_test::data;

// Extended fixed point represented with int8_t  

/*
 * Sum test number 1:
 * Extended_fixed_point_1 with INT_PART = 0 and FRAC_PART = 7
 * Extended_fixed_point 2 with INT_PART = 0 and FRAC_PART = 7
*/  

const float values_test_1_efp1[] = {0.1, 0.5, 0.2, 0.128, 0.128, 0.43};
const float values_test_1_efp2[] = {0.1, 0.05, 0.03, 0.01, 0.128, 0.54};

BOOST_DATA_TEST_CASE(Sum_Test_8_bit_1, bdata::make(values_test_1_efp1)^bdata::make(values_test_1_efp2), v1, v2) {
    float TOLERANCE = 1e-1;
    extended_fixed_point_t<0,7> efp1(v1);
    extended_fixed_point_t<0,7> efp2(v2);
    float correct_value = v1 + v2;

    extended_fixed_point_t<0,7> test1, test2;
    test1 = efp1 + efp2;
    test2 = efp2 + efp1;

    std::cout << "Sum of " << v1 << " + " << v2 << " = " << test1 << std::endl;
    BOOST_TEST(std::abs(test1.getValueF() - correct_value) < TOLERANCE);   

    std::cout << "Sum of " << v2 << " + " << v1 << " = " << test2 << std::endl;
    BOOST_TEST(std::abs(test2.getValueF() - correct_value) < TOLERANCE);  
}

BOOST_DATA_TEST_CASE(Sum_Test_8_bit_2, bdata::make(values_test_1_efp1)^bdata::make(values_test_1_efp2), v1, v2) {
    float TOLERANCE = 1e-1;
    extended_fixed_point_t<-2,7> efp1(v1);
    extended_fixed_point_t<-2,7> efp2(v2);
    float correct_value = v1 + v2;

    extended_fixed_point_t<-2,7> test1, test2;
    test1 = efp1 + efp2;
    test2 = efp2 + efp1;

    std::cout << "Sum of " << v1 << " + " << v2 << " = " << test1 << std::endl;
    BOOST_TEST(std::abs(test1.getValueF() - correct_value) < TOLERANCE);   

    std::cout << "Sum of " << v2 << " + " << v1 << " = " << test2 << std::endl;
    BOOST_TEST(std::abs(test2.getValueF() - correct_value) < TOLERANCE);  
}

BOOST_DATA_TEST_CASE(Sum_Test_8_bit_3, bdata::make(values_test_1_efp1)^bdata::make(values_test_1_efp2), v1, v2) {
    float TOLERANCE = 1e-1;
    extended_fixed_point_t<-4,7> efp1(v1);
    extended_fixed_point_t<-4,7> efp2(v2);
    float correct_value = v1 + v2;

    extended_fixed_point_t<-4,7> test1, test2;
    test1 = efp1 + efp2;
    test2 = efp2 + efp1;

    std::cout << "Sum of " << v1 << " + " << v2 << " = " << test1 << std::endl;
    BOOST_TEST(std::abs(test1.getValueF() - correct_value) < TOLERANCE);   

    std::cout << "Sum of " << v2 << " + " << v1 << " = " << test2 << std::endl;
    BOOST_TEST(std::abs(test2.getValueF() - correct_value) < TOLERANCE);  
}





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
*/

