#ifdef SINGLE_TEST
#define BOOST_TEST_MODULE Creation
#include <boost/test/included/unit_test.hpp>
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>

#include "number_generator.hpp"
#include "normal_fixed_point.hpp"
#include "low_fixed_point.hpp"
#include "high_fixed_point.hpp"

#define NUM_VALUES 100  // Number of test for each test case

using namespace std;
namespace bdata = boost::unit_test::data;
namespace utf = boost::unit_test;

/**
 *  Test to assess the correct initilization of the raw value in the fixed_point, in this way
 *  also accessor functions are tested.
 */

BOOST_AUTO_TEST_SUITE(Creation)

auto normal_int  = bdata::make({8, 8, 8, 16, 16});
auto normal_frac = bdata::make({8, 4, 16, 16, 8});

/**
 *  Test the correct initialization of normal_fixed_point.
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct initialization and the accessors of the normal_fixed_point_t"))
BOOST_DATA_TEST_CASE(Normal_fixed_point_creation, normal_int ^ normal_frac, INT, FRAC) {
    number_generator_t gen(INT, FRAC, 0);
    vector<float> numbers = gen.generate_fixed_point(NUM_VALUES);

    for(int i = 0; i < NUM_VALUES; ++i) {
        normal_fixed_point_t fp(INT, FRAC, numbers[i]);
        BOOST_TEST(fp.getValueF() == numbers[i]);
    }
}

auto high_int = bdata::make({8, 8, 16, 16, 16});
auto high_out = bdata::make({2, 4, 2, 4, 8});

/**
 *  Test the correct initialization of high_fixed_point.
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct initialization and the accessors of the high_fixed_point_t"))
BOOST_DATA_TEST_CASE(High_fixed_point_creation, high_int ^ high_out, INT, OUT) {
    number_generator_t gen(INT, 0, OUT);
    vector<int64_t> numbers = gen.generate_high_fixed_point(NUM_VALUES);

    for(int i = 0; i < NUM_VALUES; ++i) {
        high_fixed_point_t fp(INT, OUT, numbers[i]);
        BOOST_TEST(fp.getValue() == numbers[i]);
    }
}

auto low_frac = bdata::make({8, 24, 32, 32, 32});
auto low_out = bdata::make({2, 4, 2, 4, 8});

/**
 *  Test the correct initialization of low_fixed_point.
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct initialization and the accessors of the low_fixed_point_t"))
BOOST_DATA_TEST_CASE(Low_fixed_point_creation, low_frac ^ low_out, FRAC, OUT) {
    number_generator_t gen(0, FRAC, OUT);
    vector<float> numbers = gen.generate_low_fixed_point(NUM_VALUES);

    for(int i = 0; i < NUM_VALUES; ++i) {
        low_fixed_point_t fp(FRAC, OUT, numbers[i]);
        BOOST_TEST(fp.getValueF() == numbers[i]);
    }
}

BOOST_AUTO_TEST_SUITE_END()