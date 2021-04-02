#define BOOST_TEST_MODULE Raw_value_constructor_initialization

#include "extended_fixed_point.hpp"
#include <typeinfo>
#include <limits>

#include <boost/test/included/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

using namespace boost;
namespace bdata = boost::unit_test::data;

const int32_t integer_values[] = {0, 1, -1, std::numeric_limits<int32_t>::max(), std::numeric_limits<int32_t>::min()};

BOOST_DATA_TEST_CASE(Raw_value_integer_assignment, bdata::make(integer_values), value) {
    extended_fixed_point_t<31,0> efp1(value);
    extended_fixed_point_t<31,-31> efp2(value);

    BOOST_TEST(efp1.getRaw() == value);
    BOOST_TEST(efp2.getRaw() == value);

    extended_fixed_point_t<31,31> efp3(value);
    
    BOOST_TEST(efp3.getRaw() == static_cast<int64_t>(value) << 31);
}

const float float_values[] = {0.0, 0.1, -0.1, 100.001, -100.001, std::numeric_limits<float>::max(), std::numeric_limits<float>::min()};

BOOST_DATA_TEST_CASE(Raw_value_float_assignment, bdata::make(float_values), value) {
    extended_fixed_point_t<31, 31> efp(value);
    int64_t one = ((int64_t)1) << 31;

    BOOST_TEST(efp.getRaw() == (int64_t) (value * one));
}

const float float_values_neg_frac[] = {0.0, 0.1, -0.1, std::numeric_limits<float>::epsilon()};

BOOST_DATA_TEST_CASE(Raw_value_float_assignment_neg_frac, bdata::make(float_values_neg_frac), value) {
    extended_fixed_point_t<-31, 31> efp(value);
    int32_t one = ((int32_t)1) << 31;

    BOOST_TEST(efp.getRaw() == (int32_t) (value * one));
}
