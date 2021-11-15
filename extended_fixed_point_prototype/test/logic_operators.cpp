#ifndef GROUP_TEST
#define BOOST_TEST_MODULE Logic_operators
#include <boost/test/included/unit_test.hpp>
#endif

#include <boost/test/unit_test.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

#include "extended_fixed_point.hpp"

using namespace boost::mpl;
namespace bdata = boost::unit_test::data;

/**
 * Test necessary to check the correct behaviour of logic operators. In particular, equality, greater than, less than.
 * Operations among same type of extended_fixed_point are discarded because they should be trivial.
 *
 * Test list:
 *  - Equality among different extended_fixed_point, integer values
 *  - Equality among different extended_fixed_point, floating point values
 *  - Grater than among different extended_fixed_point, integer values
 *  - Grater than among different extended_fixed_point, floating point values
 *  - Less than among different extended_fixed_point, integer values
 *  - Less than among different extended_fixed_point, floating point values
 */

// Equality among different extended_fixed_point - Integer values

typedef list <
    // High extended_fixed_point and normal extended_fixed_point
    list<integral_c<int16_t, 8>, integral_c<int16_t, -4>, integral_c<int16_t, 10>, integral_c<int16_t, 6>, integral_c<int32_t, 112>>,
    list<integral_c<int16_t, 10>, integral_c<int16_t, -8>, integral_c<int16_t, 16>, integral_c<int16_t, 4>, integral_c<int32_t, 14080>>,
    // High extended fixed_point and high extended_fixed_point
    list<integral_c<int16_t, 6>, integral_c<int16_t, -2>, integral_c<int16_t, 8>, integral_c<int16_t, -3>, integral_c<int32_t, 104>>,
    list<integral_c<int16_t, 8>, integral_c<int16_t, -4>, integral_c<int16_t, 14>, integral_c<int16_t, -2>, integral_c<int32_t, 80>>,
    // Extended fixed_point and Extended_fixed_point
    list<integral_c<int16_t, 6>, integral_c<int16_t, 3>, integral_c<int16_t, 8>, integral_c<int16_t, 2>, integral_c<int32_t, 30>>,
    list<integral_c<int16_t, 8>, integral_c<int16_t, 6>, integral_c<int16_t, 14>, integral_c<int16_t, 12>, integral_c<int32_t, 121>>
    > equality_integer_test_values;

BOOST_AUTO_TEST_CASE_TEMPLATE(Equality_integer_values, T, equality_integer_test_values) {
    typedef typename at<T, int_<0>>::type INT_BITS_1;
    typedef typename at<T, int_<1>>::type FRAC_BITS_1;
    typedef typename at<T, int_<2>>::type INT_BITS_2;
    typedef typename at<T, int_<3>>::type FRAC_BITS_2;
    typedef typename at<T, int_<4>>::type EFP_VALUE;

    extended_fixed_point_t<INT_BITS_1::value, FRAC_BITS_1::value> efp_1(EFP_VALUE::value);
    extended_fixed_point_t<INT_BITS_2::value, FRAC_BITS_2::value> efp_2(EFP_VALUE::value);

    BOOST_TEST(efp_1 == efp_2);
}

// Equality among different extended_fixed_point - Floating point values

const float equality_floating_point_values[] = {9.22265e-06, 1.22702e-06, 2.96859e-06, 6.48946e-06, 5.30155e-06, 3.29106e-06, 4.39677e-06, 1.49612e-05, 1.27051e-05, 1.22534e-05 };

BOOST_DATA_TEST_CASE(Equality_floating_point_values, bdata::make(equality_floating_point_values), test_value) {
    //const double TOLERANCE = 1e-9;
    extended_fixed_point_t<31, 31> value_1(test_value);
    extended_fixed_point_t<63, 63> value_2(test_value);
    extended_fixed_point_t<-8, 63> value_3(test_value);
    extended_fixed_point_t<-16, 31> value_4(test_value);

    /*
    //BOOST_TEST(value_1 == value_2);
    //BOOST_TEST(value_1 == value_3);
    //BOOST_TEST(value_1 == value_4);
    //BOOST_TEST(value_2 == value_3);
    //BOOST_TEST(value_2 == value_4);
    //BOOST_TEST(value_3 == value_4);

    BOOST_TEST(value_1 - value_2 < TOLERANCE);
    BOOST_TEST(value_1 - value_3 < TOLERANCE);
    BOOST_TEST(value_1 - value_4 < TOLERANCE);
    BOOST_TEST(value_2 - value_3 < TOLERANCE);
    BOOST_TEST(value_2 - value_3 < TOLERANCE);
    BOOST_TEST(value_3 - value_4 < TOLERANCE);*/
}

