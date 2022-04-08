#ifdef SINGLE_TEST
#define BOOST_TEST_MODULE Division
#include <boost/test/included/unit_test.hpp>
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include "normal_fixed_point.hpp"
#include "low_fixed_point.hpp"
#include "high_fixed_point.hpp"
#include "number_generator.hpp"

#define NUM_VALUES 10000  // Number of test for each test case

using namespace std;
namespace bdata = boost::unit_test::data;
namespace utf = boost::unit_test;

/**
 *  Test to assess the correct division between two fixed_point_t, both / and /= operators are tested.
 */

BOOST_AUTO_TEST_SUITE(Division)

auto normal_int  = bdata::make({16, 8, 12});
auto normal_frac = bdata::make({16, 16, 24});

/**
 *  Test the correct division of normal_fixed_point.
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct division of the normal_fixed_point_t"))
BOOST_DATA_TEST_CASE(Normal_fixed_point_division, normal_int ^ normal_frac, INT, FRAC) {
    number_generator_t gen(INT, FRAC, 0);
    vector<float> numbers_1 = gen.generate_fixed_point(NUM_VALUES);

    gen.setSeed(2);
    vector<float> numbers_2 = gen.generate_fixed_point(NUM_VALUES);

    // Check if the divisor is zero, in that case assign the value of the previous element of the vector
    for(int i = 0; i < NUM_VALUES; ++i) 
        if(numbers_2[i] == 0) 
            numbers_2[i] = numbers_2[i-1];
        
    for(int i = 0; i < NUM_VALUES; ++i) {

        normal_fixed_point_t fp_1(INT, FRAC, numbers_1[i]);
        normal_fixed_point_t fp_2(INT, FRAC, numbers_2[i]);
        normal_fixed_point_t res (INT, FRAC);

        res = fp_1 / fp_2;

        BOOST_TEST(res.getValueF() - numbers_1[i] / numbers_2[i] < 1e-4);

        fp_1 /= fp_2;

        BOOST_TEST(fp_1.getValueF() - numbers_1[i] / numbers_2[i] < 1e-4);
    }
}


/**
 *  Test an example to show that the division of high_fixed_point_t may work.
 */
BOOST_TEST_DECORATOR(*utf::description("Test the possible and correct division of the high_fixed_point_t"))
BOOST_AUTO_TEST_CASE(High_fixed_point_division) {
    const unsigned int INT = 12;
    const unsigned int OUT = 2;
    const int64_t dividend = 256;
    const int64_t divisor = 8;

    high_fixed_point_t fp_1(INT, OUT, dividend);
    high_fixed_point_t fp_2(INT, OUT, divisor);
    high_fixed_point_t result(INT, OUT);

    result = fp_1 / fp_2;

    BOOST_TEST(result.getValue() == dividend / divisor);

    fp_1 /= fp_2;

    BOOST_TEST(fp_1.getValue() == dividend / divisor);
}

/**
 *  Test an example to show that the division of low_fixed_point_t may work.
 */
BOOST_TEST_DECORATOR(*utf::description("Test the possible and correct division of the low_fixed_point_t"))
BOOST_AUTO_TEST_CASE(Low_fixed_point_division) {
    const unsigned int FRAC = 12;
    const unsigned int OUT = 2;
    const float dividend = 0.015625;
    const float divisor = 0.125;

    low_fixed_point_t fp_1(FRAC, OUT, dividend);
    low_fixed_point_t fp_2(FRAC, OUT, divisor);
    low_fixed_point_t result(FRAC, OUT);

    result = fp_1 / fp_2;

    BOOST_TEST(result.getValueF() == dividend / divisor);

    fp_1 /= fp_2;

    BOOST_TEST(fp_1.getValueF() == dividend / divisor);
}

BOOST_AUTO_TEST_SUITE_END()