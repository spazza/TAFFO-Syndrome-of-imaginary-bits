#ifdef SINGLE_TEST
#define BOOST_TEST_MODULE Assignment
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
 *  Test to assess the correct functioning of the assignment operator in the fixed_point, 
 *  both raw and accessors are used to verify the test.
 */

BOOST_AUTO_TEST_SUITE(Assignment)

auto normal_int  = bdata::make({8, 8, 8, 16, 16});
auto normal_frac = bdata::make({8, 4, 16, 16, 8});

/**
 *  Test the correct functioning of the assignment operator of normal_fixed_point.
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct assignment using the = operator of normal_fixed_point_t"))
BOOST_DATA_TEST_CASE(Normal_fixed_point_assignment, normal_int ^ normal_frac, INT, FRAC) {
    number_generator_t gen(INT, FRAC, 0);
    vector<float> numbers = gen.generate_fixed_point(NUM_VALUES);

    for(int i = 0; i < NUM_VALUES; ++i) {
        fixed_point_t *fp = new normal_fixed_point_t(INT, FRAC, numbers[i]);
        fixed_point_t *fp_new = new normal_fixed_point_t(INT, FRAC);
        
        fp_new = fp;

        BOOST_TEST(fp_new->getRaw() == fp->getRaw());
        BOOST_TEST(fp->getValueF() == fp_new->getValueF());
    }
}

auto high_int = bdata::make({8, 8, 16, 16, 16});
auto high_out = bdata::make({2, 4, 2, 4, 8});

/**
 *  Test the correct functioning of the assignment operator of high_fixed_point.
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct assignment using the = operator of high_fixed_point_t"))
BOOST_DATA_TEST_CASE(High_fixed_point_assignment, high_int ^ high_out, INT, OUT) {
    number_generator_t gen(INT, 0, OUT);
    vector<int64_t> numbers = gen.generate_high_fixed_point(NUM_VALUES);

    for(int i = 0; i < NUM_VALUES; ++i) {
        fixed_point_t *fp = new high_fixed_point_t(INT, OUT, numbers[i]);
        fixed_point_t *fp_new = new high_fixed_point_t(INT, OUT);
        
        fp_new = fp;

        BOOST_TEST(fp_new->getRaw() == fp->getRaw());
        BOOST_TEST(fp_new->getValue() == fp->getValue());
    }
}

auto low_frac = bdata::make({8, 8, 16, 16, 16});
auto low_out = bdata::make({2, 4, 2, 4, 8});

/**
 *  Test the correct functioning of the assignment operator of low_fixed_point.
 */
BOOST_TEST_DECORATOR(*utf::description("Test the correct assignment using the = operator of low_fixed_point_t"))
BOOST_DATA_TEST_CASE(Low_fixed_point_assignment, low_frac ^ low_out, FRAC, OUT) {
    number_generator_t gen(0, FRAC, OUT);
    vector<float> numbers = gen.generate_low_fixed_point(NUM_VALUES);

    for(int i = 0; i < NUM_VALUES; ++i) {
        fixed_point_t *fp = new low_fixed_point_t(FRAC, OUT, numbers[i]);
        fixed_point_t *fp_new = new low_fixed_point_t(FRAC, OUT);

        fp_new = fp;

        BOOST_TEST(fp_new->getRaw() == fp->getRaw());
        BOOST_TEST(fp_new->getValueF() == fp->getValueF());
    }
}

BOOST_AUTO_TEST_SUITE_END()