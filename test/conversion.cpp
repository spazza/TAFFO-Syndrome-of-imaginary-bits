#ifdef SINGLE_TEST
#define BOOST_TEST_MODULE Conversion
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
 *  Test to assess the conversion of a fixed_point_t to each other possible fixed_point_t type
 */

BOOST_AUTO_TEST_SUITE(Conversion)

auto normal_int  = bdata::make({16, 16, 16, 16, 16});
auto normal_frac = bdata::make({16, 16, 16, 16, 16});

auto normal_int_new  = bdata::make({16, 16, 16, 12, 20});
auto normal_frac_new = bdata::make({16, 12, 20, 16, 16});

/**
 *  Test the conversion from a normal_fixed_point_t to normal_fixed_point_t
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct conversion of normal_fixed_point_t to normal_fixed_point_t"))
BOOST_DATA_TEST_CASE(Normal_fixed_point_conversion, normal_int ^ normal_frac ^ normal_int_new ^ normal_frac_new, INT, FRAC, INT_NEW, FRAC_NEW) {
    unsigned int int_init, frac_init;

    // Select the lower parameters to initialize without losses the fixed_point_t
    int_init  = INT > INT_NEW ? INT_NEW : INT;
    frac_init = FRAC > FRAC_NEW ? FRAC_NEW : FRAC;

    number_generator_t gen(int_init, frac_init, 0);
    vector<float> numbers = gen.generate_fixed_point(NUM_VALUES);

    for(int i = 0; i < NUM_VALUES; ++i) {
        normal_fixed_point_t fp(INT, FRAC, numbers[i]);
        normal_fixed_point_t fp_old = fp;

        fp.convert_to_normal_fixed_point_t(INT_NEW, FRAC_NEW);

        BOOST_TEST(fp.getValueF() == fp_old.getValueF());
    }
}

auto high_int = bdata::make({16, 16, 16, 16, 16});
auto high_out = bdata::make({4, 4, 4, 4, 4});

auto high_int_new = bdata::make({16, 16, 16, 12, 20});
auto high_out_new = bdata::make({4, 8, 2, 4, 4});

/**
 *  Test the conversion from a high_fixed_point_t to high_fixed_point_t
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct conversion of high_fixed_point_t to high_fixed_point_t"))
BOOST_DATA_TEST_CASE(High_fixed_point_conversion, high_int ^ high_out ^ high_int_new ^ high_out_new, INT, OUT, INT_NEW, OUT_NEW) {
    unsigned int int_init, out_init;

    // Select the lower parameters to initialize without losses the fixed_point_t
    int_init  = INT > INT_NEW ? INT_NEW : INT;
    out_init = OUT > OUT_NEW ? OUT : OUT_NEW;

    number_generator_t gen(int_init, 0, out_init);
    vector<int64_t> numbers = gen.generate_high_fixed_point(NUM_VALUES);

    for(int i = 0; i < NUM_VALUES; ++i) {
        high_fixed_point_t fp(INT, OUT, numbers[i]);
        high_fixed_point_t fp_old = fp;

        fp.convert_to_high_fixed_point_t(INT_NEW, OUT_NEW);

        BOOST_TEST(fp.getValue() == fp_old.getValue());
    }
}

auto low_frac = bdata::make({16, 16, 16, 16, 16});
auto low_out  = bdata::make({4, 4, 4, 4, 4});

auto low_frac_new = bdata::make({16, 16, 16, 12, 20});
auto low_out_new  = bdata::make({4, 8, 2, 4, 4});

/**
 *  Test the conversion from a low_fixed_point_t to low_fixed_point_t
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct conversion of low_fixed_point_t to low_fixed_point_t"))
BOOST_DATA_TEST_CASE(Low_fixed_point_conversion, low_frac ^ low_out ^ low_frac_new ^ low_out_new, FRAC, OUT, FRAC_NEW, OUT_NEW) {
    unsigned int frac_init, out_init;

    // Select the lower parameters to initialize without losses the fixed_point_t
    frac_init  = FRAC > FRAC_NEW ? FRAC_NEW : FRAC;
    out_init = OUT > OUT_NEW ? OUT : OUT_NEW;

    number_generator_t gen(0, frac_init, out_init);
    vector<float> numbers = gen.generate_low_fixed_point(NUM_VALUES);

    for(int i = 0; i < NUM_VALUES; ++i) {
        low_fixed_point_t fp(FRAC, OUT, numbers[i]);
        low_fixed_point_t fp_old = fp;

        fp.convert_to_low_fixed_point_t(FRAC_NEW, OUT_NEW);

        BOOST_TEST(fp.getValueF() == fp_old.getValueF());
    }
}

BOOST_AUTO_TEST_SUITE_END()