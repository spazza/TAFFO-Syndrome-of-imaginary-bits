#define BOOST_TEST_MODULE Conversion_test

#include "extended_fixed_point.hpp"
#include <iostream>

#include <boost/test/included/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

#include <boost/test/data/test_case.hpp>
#include <boost/test/data/monomorphic.hpp>

using namespace boost::mpl;
namespace bdata = boost::unit_test::data;

// Test data structure convention:
// INT_BITS, FRAC_BITS, INT_BITS_NEW, FRAC_BITS_NEW, EFP_VALUE

typedef list<
    // PPPP to PPPP - Integer values
    // Test maintaining the overall number of bits 
    list<integral_c<int16_t, 8>, integral_c<int16_t, 0>, integral_c<int16_t, 4>, integral_c<int16_t, 4>, integral_c<int32_t, 7>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, 0>, integral_c<int16_t, 8>, integral_c<int16_t, 8>, integral_c<int32_t, 127>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, 0>, integral_c<int16_t, 16>, integral_c<int16_t, 16>, integral_c<int32_t, 32767>>,   
    // Test reducing the overall number of bits 
    list<integral_c<int16_t, 4>, integral_c<int16_t, 4>, integral_c<int16_t, 4>, integral_c<int16_t, 2>, integral_c<int32_t, 7>>,
    list<integral_c<int16_t, 8>, integral_c<int16_t, 8>, integral_c<int16_t, 8>, integral_c<int16_t, 4>, integral_c<int32_t, 127>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, 16>, integral_c<int16_t, 16>, integral_c<int16_t, 8>, integral_c<int32_t, 32767>>,
    // Test increasing the overall number of bits
    list<integral_c<int16_t, 4>, integral_c<int16_t, 4>, integral_c<int16_t, 4>, integral_c<int16_t, 8>, integral_c<int32_t, 7>>,
    list<integral_c<int16_t, 8>, integral_c<int16_t, 8>, integral_c<int16_t, 8>, integral_c<int16_t, 12>, integral_c<int32_t, 127>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, 16>, integral_c<int16_t, 16>, integral_c<int16_t, 24>, integral_c<int32_t, 32767>>,
    // Test to check the change of raw type
    list<integral_c<int16_t, 8>, integral_c<int16_t, 0>, integral_c<int16_t, 5>, integral_c<int16_t, 4>, integral_c<int32_t, 7>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, 0>, integral_c<int16_t, 9>, integral_c<int16_t, 8>, integral_c<int32_t, 127>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, 0>, integral_c<int16_t, 17>, integral_c<int16_t, 16>, integral_c<int32_t, 32767>>,
    // Test maintaining the overall number of bits with negative numbers
    list<integral_c<int16_t, 8>, integral_c<int16_t, 0>, integral_c<int16_t, 4>, integral_c<int16_t, 4>, integral_c<int32_t, -7>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, 0>, integral_c<int16_t, 8>, integral_c<int16_t, 8>, integral_c<int32_t, -127>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, 0>, integral_c<int16_t, 16>, integral_c<int16_t, 16>, integral_c<int32_t, -32767>>,
    // Test reducing the overall number of bits with negative numbers
    list<integral_c<int16_t, 4>, integral_c<int16_t, 4>, integral_c<int16_t, 4>, integral_c<int16_t, 2>, integral_c<int32_t, -7>>,
    list<integral_c<int16_t, 8>, integral_c<int16_t, 8>, integral_c<int16_t, 8>, integral_c<int16_t, 4>, integral_c<int32_t, -127>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, 16>, integral_c<int16_t, 16>, integral_c<int16_t, 8>, integral_c<int32_t, -32767>>,
    // Test increasing the overall number of bits with negative numbers
    list<integral_c<int16_t, 4>, integral_c<int16_t, 4>, integral_c<int16_t, 4>, integral_c<int16_t, 8>, integral_c<int32_t, -7>>,
    list<integral_c<int16_t, 8>, integral_c<int16_t, 8>, integral_c<int16_t, 8>, integral_c<int16_t, 12>, integral_c<int32_t, -127>>
    > test_template_parameters_PPPP_conversion; 
    // Max values in mpl::list 20

BOOST_AUTO_TEST_CASE_TEMPLATE(Conversion_test_int_PPPP, T, test_template_parameters_PPPP_conversion) {
    typedef typename at<T, int_<0>>::type INT_BITS;
    typedef typename at<T, int_<1>>::type FRAC_BITS;
    typedef typename at<T, int_<2>>::type INT_BITS_NEW;
    typedef typename at<T, int_<3>>::type FRAC_BITS_NEW;
    typedef typename at<T, int_<4>>::type EFP_VALUE;

    extended_fixed_point_t<INT_BITS::value, FRAC_BITS::value> curr_efp(EFP_VALUE::value);
    extended_fixed_point_t<INT_BITS_NEW::value, FRAC_BITS_NEW::value> new_efp = curr_efp.template convert<INT_BITS_NEW::value, FRAC_BITS_NEW::value>();

    BOOST_TEST(EFP_VALUE::value == new_efp.getValue()); 
}

// PPPP to PPPP - Floating point values
// Test:
// 1) Reduced the number of interger bits
// 2) Increased the number of integer bits
// 3) Increased the number of fractional bits
const float test_float_PPPP_parameters[] = {/* Corner case   */  0.0,
                                            /* Random values */  
                                            3.734375, 11.71875, 2.894531, 0.804688, 1.679688, 7.207031, 15.9375, 13.769531, 9.800781, 0.539062,
                                            /* Random negative values */
                                            -3.27734, -6.41406, -13.2109, -4.70312, -10.3281, -6.58203, -6.25, -9.69922, -9.69531, -15.8438};

// Explain why tolerance is necessary
BOOST_DATA_TEST_CASE(Conversion_test_float_PPPP, bdata::make(test_float_PPPP_parameters), test_value) {
    const double TOLERANCE = 1e-2;
    extended_fixed_point_t<8, 8> curr_efp(test_value);
    extended_fixed_point_t<4, 8> new_efp_first = curr_efp.template convert<4, 8>();

    BOOST_TEST(std::abs(test_value - new_efp_first.getValueFD()) < TOLERANCE);

    extended_fixed_point_t<12, 8> new_efp_second = curr_efp.template convert<12, 8>();

    BOOST_TEST(std::abs(test_value - new_efp_second.getValueFD()) < TOLERANCE);

    extended_fixed_point_t<8, 12> new_efp_third = curr_efp.template convert<8, 12>();

    BOOST_TEST(std::abs(test_value - new_efp_third.getValueFD()) < TOLERANCE);
}

typedef list<
    // Test if the value is correctly preserved, the number needs to have an amount of bits set to 0 at the end corresponding to the negative
    // value in the new efp fractional part.
    list<integral_c<int16_t, 8>, integral_c<int16_t, 4>, integral_c<int16_t, 8>, integral_c<int16_t, -2>, integral_c<int32_t, 252>>,
    list<integral_c<int16_t, 16>,  integral_c<int16_t, 8>, integral_c<int16_t, 16>, integral_c<int16_t, -4>, integral_c<int32_t, 16368>>, 
    // Same test with negative values
    list<integral_c<int16_t, 8>, integral_c<int16_t, 4>, integral_c<int16_t, 8>, integral_c<int16_t, -2>, integral_c<int32_t, -252>>,
    list<integral_c<int16_t, 16>,  integral_c<int16_t, 8>, integral_c<int16_t, 16>, integral_c<int16_t, -4>, integral_c<int32_t, -16368>>
    > test_template_parameters_PPPN_conversion;

BOOST_AUTO_TEST_CASE_TEMPLATE(Conversion_test_int_PPPN, T, test_template_parameters_PPPN_conversion) {
    typedef typename at<T, int_<0>>::type INT_BITS;
    typedef typename at<T, int_<1>>::type FRAC_BITS;
    typedef typename at<T, int_<2>>::type INT_BITS_NEW;
    typedef typename at<T, int_<3>>::type FRAC_BITS_NEW;
    typedef typename at<T, int_<4>>::type EFP_VALUE;

    extended_fixed_point_t<INT_BITS::value, FRAC_BITS::value> curr_efp(EFP_VALUE::value);
    extended_fixed_point_t<INT_BITS_NEW::value, FRAC_BITS_NEW::value> new_efp = curr_efp.template convert<INT_BITS_NEW::value, FRAC_BITS_NEW::value>();

    BOOST_TEST(curr_efp.getValue() == new_efp.getValue()); 
}


const float test_float_PPNP_parameters[] = { /* Corner case */ 0.0,
                                             /* Random values */ 

                                             /* Random negative values */

};
// Tomorrow: fix getValue to shift correctly the FRAC_BITS


BOOST_DATA_TEST_CASE(Conversion_test_float_PPNP, bdata::make(test_float_PPNP_parameters), test_value) {
    const double TOLERANCE = 1e-2;
    extended_fixed_point_t<8, 8> curr_efp(test_value);
    extended_fixed_point_t<-2, 8> new_efp_first = curr_efp.template convert<-2, 8>();

    BOOST_TEST(std::abs(curr_efp.getValue() - new_efp_first.getValueFD()) < TOLERANCE);

    // Another test case??
    extended_fixed_point_t<-4, 4> new_efp_second = curr_efp.template convert<-4, 4>();

    BOOST_TEST(curr_efp.getValue() == new_efp_second.getValue());
}