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
 *  - Greater than among different extended_fixed_point, integer values
 *  - Greater than among different extended_fixed_point, floating point values
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

// Test can't be performed the floating point value for certain coversion is erased and the two values will be not completely equal.

/*

const float equality_floating_point_values[] = {9.22265e-06, 1.22702e-06, 2.96859e-06, 6.48946e-06, 5.30155e-06, 3.29106e-06, 4.39677e-06, 1.49612e-05, 1.27051e-05, 1.22534e-05 };

BOOST_DATA_TEST_CASE(Equality_floating_point_values, bdata::make(equality_floating_point_values), test_value) {
    const double TOLERANCE = 1e-9;
    extended_fixed_point_t<31, 31> value_1(test_value);
    extended_fixed_point_t<63, 63> value_2(test_value);
    extended_fixed_point_t<-8, 63> value_3(test_value);
    extended_fixed_point_t<-16, 31> value_4(test_value);

    // Equality among all the types of extended_fixed_point
    
    BOOST_TEST(value_1 - value_2 < TOLERANCE);
    BOOST_TEST(value_1 - value_3 < TOLERANCE);
    BOOST_TEST(value_1 - value_4 < TOLERANCE);
    BOOST_TEST(value_2 - value_3 < TOLERANCE);
    BOOST_TEST(value_2 - value_3 < TOLERANCE);
    BOOST_TEST(value_3 - value_4 < TOLERANCE);
}
*/

// Greater than among different extended_fixed_point - Integer values

typedef list <
    // High extended_fixed_point and normal extended_fixed_point
    list<integral_c<int16_t, 8>, integral_c<int16_t, -4>, integral_c<int16_t, 10>, integral_c<int16_t, 6>, integral_c<int32_t, 112>, integral_c<int32_t, 90>>,
    list<integral_c<int16_t, 10>, integral_c<int16_t, -8>, integral_c<int16_t, 16>, integral_c<int16_t, 4>, integral_c<int32_t, 14080>, integral_c<int32_t, 5120>>,
    // High extended fixed_point and high extended_fixed_point
    list<integral_c<int16_t, 6>, integral_c<int16_t, -2>, integral_c<int16_t, 8>, integral_c<int16_t, -3>, integral_c<int32_t, 104>, integral_c<int32_t, 40>>,
    list<integral_c<int16_t, 8>, integral_c<int16_t, -4>, integral_c<int16_t, 14>, integral_c<int16_t, -2>, integral_c<int32_t, 80>, integral_c<int32_t, 48>>,
    // Extended fixed_point and Extended_fixed_point
    list<integral_c<int16_t, 6>, integral_c<int16_t, 3>, integral_c<int16_t, 8>, integral_c<int16_t, 2>, integral_c<int32_t, 30>, integral_c<int32_t, 11>>,
    list<integral_c<int16_t, 8>, integral_c<int16_t, 6>, integral_c<int16_t, 14>, integral_c<int16_t, 12>, integral_c<int32_t, 121>, integral_c<int32_t, 105>>
    > greater_than_integer_test_values;

BOOST_AUTO_TEST_CASE_TEMPLATE(Greater_than_integer_values, T, greater_than_integer_test_values) {
    typedef typename at<T, int_<0>>::type INT_BITS_1;
    typedef typename at<T, int_<1>>::type FRAC_BITS_1;
    typedef typename at<T, int_<2>>::type INT_BITS_2;
    typedef typename at<T, int_<3>>::type FRAC_BITS_2;
    typedef typename at<T, int_<4>>::type EFP_VALUE_1;
    typedef typename at<T, int_<5>>::type EFP_VALUE_2;

    extended_fixed_point_t<INT_BITS_1::value, FRAC_BITS_1::value> efp_1(EFP_VALUE_1::value);
    extended_fixed_point_t<INT_BITS_2::value, FRAC_BITS_2::value> efp_2(EFP_VALUE_2::value);

    BOOST_TEST(efp_1 > efp_2);
}

// Greater than among different extended_fixed_point - Floating point values

const float greater_than_floating_point_values_1[] = {0.016612, 0.009782, 0.014076, 0.002332, 0.001123};
const float greater_than_floating_point_values_2[] = {0.004042, 0.005891, 0.01024, 0.0010982, 0.00103};

BOOST_DATA_TEST_CASE(Greater_than_floating_point_values, bdata::make(greater_than_floating_point_values_1) ^ bdata::make(greater_than_floating_point_values_2), v1, v2) {
    // extended_fixed_point and extended_fixed_point
    extended_fixed_point_t<31, 31> value_1(v1);
    extended_fixed_point_t<31, 64> value_2(v2);

    BOOST_TEST(value_1 > value_2);

    // Low extended_fixed_point and extended_fixed_point
    extended_fixed_point_t<-4, 31> value_3(v1);
    extended_fixed_point_t<4, 48> value_4(v2);

    BOOST_TEST(value_3 > value_4);

    // Low extended_fixed_point and low extended_fixed_point
    extended_fixed_point_t<-4, 48> value_5(v1);
    extended_fixed_point_t<-8, 48> value_6(v2);

    BOOST_TEST(value_5 > value_6);
}

// Less than among different extended_fixed_point - Integer values

typedef list <
    // High extended_fixed_point and normal extended_fixed_point
    list<integral_c<int16_t, 8>, integral_c<int16_t, -4>, integral_c<int16_t, 10>, integral_c<int16_t, 6>, integral_c<int32_t, 112>, integral_c<int32_t, 352>>,
    list<integral_c<int16_t, 10>, integral_c<int16_t, -8>, integral_c<int16_t, 16>, integral_c<int16_t, 4>, integral_c<int32_t, 14080>, integral_c<int32_t, 27648>>,
    // High extended fixed_point and high extended_fixed_point
    list<integral_c<int16_t, 6>, integral_c<int16_t, -2>, integral_c<int16_t, 8>, integral_c<int16_t, -3>, integral_c<int32_t, 24>, integral_c<int32_t, 48>>,
    list<integral_c<int16_t, 8>, integral_c<int16_t, -4>, integral_c<int16_t, 14>, integral_c<int16_t, -2>, integral_c<int32_t, 80>, integral_c<int32_t, 376>>,
    // Extended fixed_point and Extended_fixed_point
    list<integral_c<int16_t, 6>, integral_c<int16_t, 3>, integral_c<int16_t, 8>, integral_c<int16_t, 2>, integral_c<int32_t, 15>, integral_c<int32_t, 18>>,
    list<integral_c<int16_t, 8>, integral_c<int16_t, 6>, integral_c<int16_t, 14>, integral_c<int16_t, 12>, integral_c<int32_t, 70>, integral_c<int32_t, 93>>
    > less_than_integer_test_values;

BOOST_AUTO_TEST_CASE_TEMPLATE(Less_than_integer_values, T, less_than_integer_test_values) {
    typedef typename at<T, int_<0>>::type INT_BITS_1;
    typedef typename at<T, int_<1>>::type FRAC_BITS_1;
    typedef typename at<T, int_<2>>::type INT_BITS_2;
    typedef typename at<T, int_<3>>::type FRAC_BITS_2;
    typedef typename at<T, int_<4>>::type EFP_VALUE_1;
    typedef typename at<T, int_<5>>::type EFP_VALUE_2;

    extended_fixed_point_t<INT_BITS_1::value, FRAC_BITS_1::value> efp_1(EFP_VALUE_1::value);
    extended_fixed_point_t<INT_BITS_2::value, FRAC_BITS_2::value> efp_2(EFP_VALUE_2::value);

    BOOST_TEST(efp_1 < efp_2);
}

// Less than among different extended_fixed_point - Floating point values

const float less_than_floating_point_values_1[] = {0.000234246, 0.000174403, 0.000625074, 0.000672102, 0.000018239 };
const float less_than_floating_point_values_2[] = {0.00026049, 0.0002891, 0.00078901, 0.00090982, 0.00014562};

BOOST_DATA_TEST_CASE(Less_than_floating_point_values, bdata::make(less_than_floating_point_values_1) ^ bdata::make(less_than_floating_point_values_2), v1, v2) {
    // extended_fixed_point and extended_fixed_point
    extended_fixed_point_t<31, 31> value_1(v1);
    extended_fixed_point_t<31, 64> value_2(v2);

    BOOST_TEST(value_1 < value_2);

    // Low extended_fixed_point and extended_fixed_point
    extended_fixed_point_t<-4, 31> value_3(v1);
    extended_fixed_point_t<4, 48> value_4(v2);

    BOOST_TEST(value_3 < value_4);

    // Low extended_fixed_point and low extended_fixed_point
    extended_fixed_point_t<-4, 48> value_5(v1);
    extended_fixed_point_t<-8, 48> value_6(v2);

    BOOST_TEST(value_5 < value_6);
}