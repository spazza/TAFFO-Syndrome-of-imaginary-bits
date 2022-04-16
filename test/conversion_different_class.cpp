#ifdef SINGLE_TEST
#define BOOST_TEST_MODULE Conversion_different_classes
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
 * Test to assess the conversion among different fixed_point_t subclasses, in particular:
 *  - normal_fixed_point_t to high_fixed_point_t
 *  - normal_fixed_point_t to low_fixed_point_t
 *  - high_fixed_point_t to normal_fixed_point_t
 *  - low_fixed_point_t to normal_fixed_point_t
 * 
 * Other types of conversions are meaningless, therefore they are not tested.
 */

BOOST_AUTO_TEST_SUITE(Conversion_different_classes)

auto normal_int  = bdata::make({16, 16, 16});
auto normal_frac = bdata::make({4, 4, 4});

auto high_int_new  = bdata::make({16, 16, 16});
auto high_out_new = bdata::make({2, 4, 1});

/**
 *  Test the conversion from a normal_fixed_point_t to high_fixed_point_t
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct conversion of normal_fixed_point_t to high_fixed_point_t"))
BOOST_DATA_TEST_CASE(Normal_fp_to_high_fp_conversion, normal_int ^ normal_frac ^ high_int_new ^ high_out_new, INT, FRAC, INT_NEW, OUT_NEW) {
    // Initialize normal_fixed_point_t with the values suitable for a high_fixed_point_t
    number_generator_t gen(INT_NEW, 0, OUT_NEW);
    vector<int64_t> numbers = gen.generate_high_fixed_point(NUM_VALUES);

    for(int i = 0; i < NUM_VALUES; ++i) {
        normal_fixed_point_t fp(INT, FRAC, numbers[i]);
        normal_fixed_point_t fp_old = fp;

        fp.convert_to_normal_fixed_point_t(INT_NEW, OUT_NEW);

        BOOST_TEST(fp.getValue() == fp_old.getValue());
    }
}

auto normal_int_2  = bdata::make({4, 4, 4});
auto normal_frac_2 = bdata::make({16, 16, 16});

auto low_frac_new  = bdata::make({2, 4, 1});
auto low_out_new = bdata::make({16, 16, 16});

/**
 *  Test the conversion from a normal_fixed_point_t to low_fixed_point_t
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct conversion of normal_fixed_point_t to low_fixed_point_t"))
BOOST_DATA_TEST_CASE(Normal_fp_to_low_fp_conversion, normal_int_2 ^ normal_frac_2 ^ low_frac_new ^ low_out_new, INT, FRAC, FRAC_NEW, OUT_NEW) {

}

auto high_int  = bdata::make({16, 16, 16});
auto high_out = bdata::make({2, 2, 2});

auto normal_int_new  = bdata::make({16, 16, 16});
auto normal_frac_new = bdata::make({1, 2, 4});

/**
 *  Test the conversion from a high_fixed_point_t to normal_fixed_point_t
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct conversion of high_fixed_point_t to normal_fixed_point_t"))
BOOST_DATA_TEST_CASE(High_fp_to_normal_fp_conversion, high_int ^ high_out ^ normal_int_new ^ normal_frac_new, INT, OUT, INT_NEW, FRAC_NEW) {

}

auto low_frac  = bdata::make({16, 16, 16});
auto low_out = bdata::make({2, 2, 2});

auto normal_int_new_2  = bdata::make({1, 2, 4});
auto normal_frac_new_2 = bdata::make({16, 16, 16});

/**
 *  Test the conversion from a low_fixed_point_t to normal_fixed_point_t
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct conversion of low_fixed_point_t to normal_fixed_point_t"))
BOOST_DATA_TEST_CASE(Low_fp_to_normal_fp_conversion, low_frac ^ low_out ^ normal_int_new_2 ^ normal_frac_new_2, FRAC, OUT, INT_NEW, FRAC_NEW) {

}

BOOST_AUTO_TEST_SUITE_END()