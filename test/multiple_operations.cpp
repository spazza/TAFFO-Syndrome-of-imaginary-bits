#ifdef SINGLE_TEST
#define BOOST_TEST_MODULE Multiple_operations
#include <boost/test/included/unit_test.hpp>
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include "normal_fixed_point.hpp"
#include "low_fixed_point.hpp"
#include "high_fixed_point.hpp"
#include "number_generator.hpp"

#define NUM_VALUES 100  // Number of test for each test case

using namespace std;
namespace bdata = boost::unit_test::data;
namespace utf = boost::unit_test;

BOOST_AUTO_TEST_SUITE(Multiple_operation)

auto normal_int  = bdata::make({14, 14, 20, 8, 8});
auto normal_frac = bdata::make({14, 8, 8, 14, 20});

/**
 *  Test multiple successive operations on normal_fixed_point.
 */
BOOST_TEST_DECORATOR(*utf::description("Test multiple operations on normal_fixed_point_t"))
BOOST_DATA_TEST_CASE(Normal_fixed_point_successive_operations, normal_int ^ normal_frac, INT, FRAC) {
    // Divide the range to make the overflow less likely
    number_generator_t gen(INT/2, FRAC/2, 0);
    vector<float> numbers_1 = gen.generate_fixed_point(NUM_VALUES);

    gen.setSeed(2);
    vector<float> numbers_2 = gen.generate_fixed_point(NUM_VALUES);

    gen.setSeed(3);
    vector<float> numbers_3 = gen.generate_fixed_point(NUM_VALUES);

    gen.setSeed(4);
    vector<float> numbers_4 = gen.generate_fixed_point(NUM_VALUES);

    // Check if the fourth factor is zero, in that case assign the value of the previous element of the vector
    for(int i = 0; i < NUM_VALUES; ++i) 
        if(numbers_4[i] == 0) 
            numbers_4[i] = gen.generate_fixed_point(1)[0];
        
    for(int i = 0; i < NUM_VALUES; ++i) {

        normal_fixed_point_t fp_1(INT, FRAC, numbers_1[i]);
        normal_fixed_point_t fp_2(INT, FRAC, numbers_2[i]);
        normal_fixed_point_t fp_3(INT, FRAC, numbers_3[i]);
        normal_fixed_point_t fp_4(INT, FRAC, numbers_4[i]);
        normal_fixed_point_t res (INT, FRAC);

        res = ((fp_1 + fp_2) * fp_3) / fp_4 ;

        BOOST_TEST(res.getValueF() - (((numbers_1[i] + numbers_2[i]) * numbers_3[i]) / numbers_4[i]) < 1e-2);
    }
}

auto high_int = bdata::make({16, 16, 16});
auto high_out = bdata::make({1, 2, 4});

/**
 *  Test multiple successive operations on high_fixed_point.
 */
BOOST_TEST_DECORATOR(*utf::description("Test multiple operations on high_fixed_point_t"))
BOOST_DATA_TEST_CASE(High_fixed_point_successive_operations, high_int ^ high_out, INT, OUT) {
    // Divide the range to make the overflow less likely
    number_generator_t gen(INT/2, 0, OUT);
    vector<int64_t> numbers_1 = gen.generate_high_fixed_point(NUM_VALUES);

    gen.setSeed(2);
    vector<int64_t> numbers_2 = gen.generate_high_fixed_point(NUM_VALUES);

    gen.setSeed(3);
    vector<int64_t> numbers_3 = gen.generate_high_fixed_point(NUM_VALUES);

    gen.setSeed(4);
    vector<int64_t> numbers_4 = gen.generate_high_fixed_point(NUM_VALUES);

    // Check if the fourth factor is zero, in that case assign the value of the previous element of the vector
    for(int i = 0; i < NUM_VALUES; ++i) 
        if(numbers_4[i] == 0) 
            numbers_4[i] = gen.generate_high_fixed_point(1)[0];
        
    for(int i = 0; i < NUM_VALUES; ++i) {

        high_fixed_point_t fp_1(INT, OUT, numbers_1[i]);
        high_fixed_point_t fp_2(INT, OUT, numbers_2[i]);
        high_fixed_point_t fp_3(INT, OUT, numbers_3[i]);
        high_fixed_point_t fp_4(INT, OUT, numbers_4[i]);
        high_fixed_point_t res (INT, OUT);

        res = ((fp_1 + fp_2) * fp_3) / fp_4 ;

        BOOST_TEST(res.getValue() - (((numbers_1[i] + numbers_2[i]) * numbers_3[i]) / numbers_4[i]) < 1e2);
    }
}

auto low_frac = bdata::make({16, 16, 16});
auto low_out = bdata::make({1, 2, 4});

/**
 *  Test multiple successive operations on low_fixed_point.
 */
BOOST_TEST_DECORATOR(*utf::description("Test multiple operations on low_fixed_point_t"))
BOOST_DATA_TEST_CASE(Low_fixed_point_successive_operations, low_frac ^ low_out, FRAC, OUT) {
    // Divide the range to make the overflow less likely
    number_generator_t gen(0, FRAC/2, OUT);
    vector<float> numbers_1 = gen.generate_low_fixed_point(NUM_VALUES);

    gen.setSeed(2);
    vector<float> numbers_2 = gen.generate_low_fixed_point(NUM_VALUES);

    gen.setSeed(3);
    vector<float> numbers_3 = gen.generate_low_fixed_point(NUM_VALUES);

    gen.setSeed(4);
    vector<float> numbers_4 = gen.generate_low_fixed_point(NUM_VALUES);

    // Check if the fourth factor is zero, in that case assign the value of the previous element of the vector
    for(int i = 0; i < NUM_VALUES; ++i) 
        if(numbers_4[i] == 0) 
            numbers_4[i] = gen.generate_low_fixed_point(1)[0];
        
    for(int i = 0; i < NUM_VALUES; ++i) {

        low_fixed_point_t fp_1(FRAC, OUT, numbers_1[i]);
        low_fixed_point_t fp_2(FRAC, OUT, numbers_2[i]);
        low_fixed_point_t fp_3(FRAC, OUT, numbers_3[i]);
        low_fixed_point_t fp_4(FRAC, OUT, numbers_4[i]);
        low_fixed_point_t res (FRAC, OUT);

        res = ((fp_1 + fp_2) * fp_3) / fp_4 ;

        BOOST_TEST(res.getValueF() - (((numbers_1[i] + numbers_2[i]) * numbers_3[i]) / numbers_4[i]) < 1e-2);
    }
}


BOOST_AUTO_TEST_SUITE_END()