#ifdef SINGLE_TEST
#define BOOST_TEST_MODULE Product
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
 *  Test to assess the correct product between two fixed_point_t, both * and *= operators are tested.
 */

BOOST_AUTO_TEST_SUITE(Product)

// Fourth test changed to 14 because of the limited size of the raw_t 
auto normal_int  = bdata::make({8, 8, 8, 14, 16});
auto normal_frac = bdata::make({8, 4, 16, 14, 8});

/**
 *  Test the correct product of normal_fixed_point.
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct product of the normal_fixed_point_t"))
BOOST_DATA_TEST_CASE(Normal_fixed_point_product, normal_int ^ normal_frac, INT, FRAC) {
    // Initialization of INT and FRAC divided by 2 to avoid overflows in the next operations
    number_generator_t gen(INT/2, FRAC/2, 0);
    vector<float> numbers_1 = gen.generate_fixed_point(NUM_VALUES);

    gen.setSeed(2);
    vector<float> numbers_2 = gen.generate_fixed_point(NUM_VALUES);

    for(int i = 0; i < NUM_VALUES; ++i) {

        normal_fixed_point_t fp_1(INT, FRAC, numbers_1[i]);
        normal_fixed_point_t fp_2(INT, FRAC, numbers_2[i]);
        normal_fixed_point_t res (INT, FRAC);

        res = fp_1 * fp_2;

        BOOST_TEST(res.getValueF() == numbers_1[i] * numbers_2[i]);

        fp_1 *= fp_2;

        BOOST_TEST(fp_1.getValueF() == numbers_1[i] * numbers_2[i]);
    }
}

auto high_int = bdata::make({8, 8, 16, 16, 16});
auto high_out = bdata::make({2, 4, 2, 4, 8});

/**
 *  Test the correct product of high_fixed_point.
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct product of the high_fixed_point_t"))
BOOST_DATA_TEST_CASE(High_fixed_point_product, high_int ^ high_out, INT, OUT) {
    // Initialization of INT divided by 2 to avoid overflows in the next operations
    number_generator_t gen(INT/2, 0, OUT);
    vector<int64_t> numbers_1 = gen.generate_high_fixed_point(NUM_VALUES);

    gen.setSeed(2);
    vector<int64_t> numbers_2 = gen.generate_high_fixed_point(NUM_VALUES);

    for(int i = 0; i < NUM_VALUES; ++i) {

        high_fixed_point_t fp_1(INT, OUT, numbers_1[i]);
        high_fixed_point_t fp_2(INT, OUT, numbers_2[i]);
        high_fixed_point_t res (INT, OUT);

        res = fp_1 * fp_2;

        BOOST_TEST(res.getValue() == numbers_1[i] * numbers_2[i]);

        fp_1 *= fp_2;

        BOOST_TEST(fp_1.getValue() == numbers_1[i] * numbers_2[i]);
    }
}

// Third, fourth and fifth test changed to 30 because of the limited size of the raw_t 
auto low_frac = bdata::make({8, 24, 30, 30, 30});
auto low_out = bdata::make({2, 4, 2, 4, 8});

/**
 *  Test the correct product of low_fixed_point.
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct product of the low_fixed_point_t"))
BOOST_DATA_TEST_CASE(Low_fixed_point_product, low_frac ^ low_out, FRAC, OUT) {
    // Initialization of FRAC divided by 2 to avoid overflows in the next operations
    number_generator_t gen(0, FRAC/2, OUT);
    vector<float> numbers_1 = gen.generate_low_fixed_point(NUM_VALUES);

    gen.setSeed(2);
    vector<float> numbers_2 = gen.generate_low_fixed_point(NUM_VALUES);

    for(int i = 0; i < NUM_VALUES; ++i) {

        low_fixed_point_t fp_1(FRAC, OUT, numbers_1[i]);
        low_fixed_point_t fp_2(FRAC, OUT, numbers_2[i]);
        low_fixed_point_t res (FRAC, OUT);

        res = fp_1 * fp_2;

        BOOST_TEST(res.getValueF() == numbers_1[i] * numbers_2[i]);

        fp_1 *= fp_2;

        BOOST_TEST(fp_1.getValueF() == numbers_1[i] * numbers_2[i]);
    }
}

BOOST_AUTO_TEST_SUITE_END()