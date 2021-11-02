#ifndef GROUP_TEST
#define BOOST_TEST_MODULE Sum
#include <boost/test/included/unit_test.hpp>
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

#include <limits>

#include "extended_fixed_point.hpp"

using namespace boost::mpl;
namespace bdata = boost::unit_test::data;

BOOST_AUTO_TEST_SUITE(Sum_test)

const int16_t int_test_array_1[] = { // Corner case
                                     0, 0, std::numeric_limits<int16_t>::min(), 
                                     // Random values
                                     5111, 13349, 8077, 29651, 32259, 31065, 3666, 8783};

const int16_t int_test_array_2[] = { // Corner case
                                     0, std::numeric_limits<int16_t>::max(), 0,
                                     // Random values
                                     9646, 8184, 30828, 20167, 17425, 22675, 4943, 4159};

BOOST_DATA_TEST_CASE(Sum_integer_same_type, bdata::make(int_test_array_1) ^ bdata::make(int_test_array_2), v1, v2) {
    extended_fixed_point_t<16,0> num1(v1);
    extended_fixed_point_t<16,0> num2(v2);
    extended_fixed_point_t<16,0> res1;

    extended_fixed_point_t<16,8> num3(v1);
    extended_fixed_point_t<16,8> num4(v2);
    extended_fixed_point_t<16,8> res2;

    extended_fixed_point_t<32,16> num5(v1);
    extended_fixed_point_t<32,16> num6(v2);
    extended_fixed_point_t<32,16> res3;

    res1 = num1 + num2;
    res2 = num3 + num4;
    res3 = num5 + num6;

    BOOST_TEST(res1 == v1 + v2);
    BOOST_TEST(num1 + num2 == v1 + v2);
}

BOOST_AUTO_TEST_SUITE_END()