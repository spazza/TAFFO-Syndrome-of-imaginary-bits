#ifdef SINGLE_TEST
#define BOOST_TEST_MODULE Logical_operators
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

/**
 *  Test to assess the correct functioning of the logical operators (<, >, <=, >=, ==, !=)
 */

BOOST_AUTO_TEST_SUITE(Logical_operators)

auto normal_int  = bdata::make({8, 8, 8, 16, 16});
auto normal_frac = bdata::make({8, 4, 16, 16, 8});

/**
 *  Test the correct functioning of the logical operators of normal_fixed_point_t
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct functioning of the logical operators (<, >, <=, >=, ==, !=) of normal_fixed_point_t"))
BOOST_DATA_TEST_CASE(Normal_fixed_point_logical_operators, normal_int ^ normal_frac, INT, FRAC) {
    number_generator_t gen(INT, FRAC, 0);
    vector<float> numbers_1 = gen.generate_fixed_point(NUM_VALUES);
    vector<float> numbers_2 = gen.generate_fixed_point(NUM_VALUES);

    // Fix the vectors such that the lower is in the first and the greater in the second.
    for(int i = 0; i < NUM_VALUES; ++i) 
        if(numbers_1[i] > numbers_2[i]) {
            float temp   = numbers_1[i];
            numbers_1[i] = numbers_2[i];
            numbers_2[i] = temp;
        }

    for(int i = 0; i < NUM_VALUES; ++i) {
        normal_fixed_point_t fp_lower(INT, FRAC, numbers_1[i]);
        normal_fixed_point_t fp_greater(INT, FRAC, numbers_2[i]);
        
        bool res1 = fp_lower <  fp_greater;
        bool res2 = fp_lower <=  fp_greater;
        BOOST_TEST(res1);
        BOOST_TEST(res2);

        bool res3 = fp_greater >  fp_lower;
        bool res4 = fp_greater >= fp_lower;
        BOOST_TEST(res3);
        BOOST_TEST(res4);

        // Reusing the previous values
        normal_fixed_point_t fp_equal(INT, FRAC, numbers_1[i]);
        normal_fixed_point_t fp_unequal(INT, FRAC, numbers_2[i]);

        bool res5 = fp_lower == fp_equal;
        bool res6 = fp_lower != fp_unequal;
        BOOST_TEST(res5);
        BOOST_TEST(res6);

        bool res7 = fp_lower <= fp_equal;
        bool res8 = fp_lower >= fp_equal;
        BOOST_TEST(res7);
        BOOST_TEST(res8);
    }
}

auto high_int = bdata::make({8, 8, 16, 16, 16});
auto high_out = bdata::make({2, 4, 2, 4, 8});

/**
 *  Test the correct functioning of the logical operators of high_fixed_point_t
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct functioning of the logical operators (<, >, <=, >=, ==, !=) of high_fixed_point_t"))
BOOST_DATA_TEST_CASE(High_fixed_point_logical_operators, high_int ^ high_out, INT, OUT) {
    number_generator_t gen(INT, 0, OUT);
    vector<int64_t> numbers_1 = gen.generate_high_fixed_point(NUM_VALUES);
    vector<int64_t> numbers_2 = gen.generate_high_fixed_point(NUM_VALUES);

    // Fix the vectors such that the lower is in the first and the greater in the second.
    for(int i = 0; i < NUM_VALUES; ++i) 
        if(numbers_1[i] > numbers_2[i]) {
            float temp   = numbers_1[i];
            numbers_1[i] = numbers_2[i];
            numbers_2[i] = temp;
        }

    for(int i = 0; i < NUM_VALUES; ++i) {
        high_fixed_point_t fp_lower(INT, OUT, numbers_1[i]);
        high_fixed_point_t fp_greater(INT, OUT, numbers_2[i]);
        
        bool res1 = fp_lower <  fp_greater;
        bool res2 = fp_lower <=  fp_greater;
        BOOST_TEST(res1);
        BOOST_TEST(res2);

        bool res3 = fp_greater >  fp_lower;
        bool res4 = fp_greater >= fp_lower;
        BOOST_TEST(res3);
        BOOST_TEST(res4);

        // Reusing the previous values
        high_fixed_point_t fp_equal(INT, OUT, numbers_1[i]);
        high_fixed_point_t fp_unequal(INT, OUT, numbers_2[i]);

        bool res5 = fp_lower == fp_equal;
        bool res6 = fp_lower != fp_unequal;
        BOOST_TEST(res5);
        BOOST_TEST(res6);

        bool res7 = fp_lower <= fp_equal;
        bool res8 = fp_lower >= fp_equal;
        BOOST_TEST(res7);
        BOOST_TEST(res8);
    }
}

auto low_frac = bdata::make({10, 12, 16, 16, 16});
auto low_out = bdata::make({2, 4, 2, 4, 8});

/**
 *  Test the correct functioning of the logical operators of low_fixed_point_t
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct functioning of the logical operators (<, >, <=, >=, ==, !=) of low_fixed_point_t"))
BOOST_DATA_TEST_CASE(Low_fixed_point_logical_operators, low_frac ^ low_out, FRAC, OUT) {
    number_generator_t gen(0, FRAC, OUT);
    vector<float> numbers_1 = gen.generate_low_fixed_point(NUM_VALUES);
    vector<float> numbers_2 = gen.generate_low_fixed_point(NUM_VALUES);
    
    // Fix the vectors such that the lower is in the first and the greater in the second.
    for(int i = 0; i < NUM_VALUES; ++i) {
        if(numbers_1[i] > numbers_2[i]) {
            float temp   = numbers_1[i];
            numbers_1[i] = numbers_2[i];
            numbers_2[i] = temp;
        }
    }

    for(int i = 0; i < NUM_VALUES; ++i) {
        low_fixed_point_t fp_lower(FRAC, OUT, numbers_1[i]);
        low_fixed_point_t fp_greater(FRAC, OUT, numbers_2[i]);
        
        bool res1 = fp_lower <  fp_greater;
        bool res2 = fp_lower <=  fp_greater;
        BOOST_TEST(res1);
        BOOST_TEST(res2);

        bool res3 = fp_greater >  fp_lower;
        bool res4 = fp_greater >= fp_lower;
        BOOST_TEST(res3);
        BOOST_TEST(res4);

        // Reusing the previous values
        low_fixed_point_t fp_equal(FRAC, OUT, numbers_1[i]);
        low_fixed_point_t fp_unequal(FRAC, OUT, numbers_2[i]);

        bool res5 = fp_lower == fp_equal;
        bool res6 = fp_lower != fp_unequal;
        BOOST_TEST(res5);
        BOOST_TEST(res6);

        bool res7 = fp_lower <= fp_equal;
        bool res8 = fp_lower >= fp_equal;
        BOOST_TEST(res7);
        BOOST_TEST(res8);
    }
}

BOOST_AUTO_TEST_SUITE_END()