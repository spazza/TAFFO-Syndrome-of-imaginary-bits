#ifndef GROUP_TEST
#define BOOST_TEST_MODULE Conversion
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
 * Test to verify the correct conversion among the various types of extended_fixed_point_t. 
 * Both integer and floating point values are tested.
 * In particular:
 * - From INT_BITS >= 0 , FRAC_BITS >= 0 to INT_BITS >= 0 , FRAC_BITS >= 0
 * - From INT_BITS >= 0 , FRAC_BITS <  0 to INT_BITS >= 0 , FRAC_BITS <  0
 * - From INT_BITS <  0 , FRAC_BITS >= 0 to INT_BITS <  0 , FRAC_BITS >= 0
 * 
 * - From INT_BITS >= 0 , FRAC_BITS >= 0 to INT_BITS >= 0 , FRAC_BITS <  0
 * - From INT_BITS >= 0 , FRAC_BITS >= 0 to INT_BITS <  0 , FRAC_BITS >= 0
 * - From INT_PART >= 0 , FRAC_PART <  0 to INT_PART >= 0 , FRAC_PART >= 0
 * - From INT_PART <  0 , FRAC_PART >= 0 to INT_PART >= 0 , FRAC_PART >= 0
 * 
 * Integer values are selected such that their binary representation contains the max possible amount of 1 values adjacent.
 */

BOOST_AUTO_TEST_SUITE(Conversion_test)

// Test data structure convention:
// INT_BITS, FRAC_BITS, INT_BITS_NEW, FRAC_BITS_NEW, EFP_VALUE

// From INT_PART >= 0, FRAC_PART >= 0 to INT_PART >= 0, FRAC_PART >= 0 - Integer values

typedef list<
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

// From INT_PART >= 0, FRAC_PART >= 0 to INT_PART >= 0, FRAC_PART >= 0 - Floating point values
// Test:
// 1) Reduced the number of interger bits
// 2) Increased the number of integer bits
// 3) Increased the number of fractional bits

const float test_float_PPPP_parameters[] = {/* Corner case   */  
                                            0.0,
                                            /* Random values */  
                                            3.734375, 11.71875, 2.894531, 0.804688, 1.679688, 7.207031, 15.9375, 13.769531, 9.800781, 0.539062,
                                            /* Random negative values */
                                            -3.27734, -6.41406, -13.2109, -4.70312, -10.3281, -6.58203, -6.25, -9.69922, -9.69531, -15.8438};

BOOST_DATA_TEST_CASE(Conversion_test_float_PPPP, bdata::make(test_float_PPPP_parameters), test_value) {
    const double TOLERANCE = 1e-9;
    extended_fixed_point_t<8, 32> curr_efp(test_value);
    extended_fixed_point_t<4, 32> new_efp_first = curr_efp.template convert<4, 32>();

    BOOST_TEST(std::abs(test_value - new_efp_first.getValueFD()) < TOLERANCE);

    extended_fixed_point_t<12, 32> new_efp_second = curr_efp.template convert<12, 32>();

    BOOST_TEST(std::abs(test_value - new_efp_second.getValueFD()) < TOLERANCE);

    extended_fixed_point_t<8, 48> new_efp_third = curr_efp.template convert<8, 48>();

    BOOST_TEST(std::abs(test_value - new_efp_third.getValueFD()) < TOLERANCE);
}

// From INT_PART >= 0, FRAC_PART < 0 to INT_PART >= 0, FRAC_PART < 0 - Integer values

typedef list<
    // Test increasing the number of negative fractional bits
    list<integral_c<int16_t, 8>, integral_c<int16_t, -2>, integral_c<int16_t, 6>, integral_c<int16_t, -4>, integral_c<int32_t, 112>>,
    list<integral_c<int16_t, 10>, integral_c<int16_t, -2>, integral_c<int16_t, 12>, integral_c<int16_t, -4>, integral_c<int32_t, 4080>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, -4>, integral_c<int16_t, 9>, integral_c<int16_t, -6>, integral_c<int32_t, 8128>>,
    // Test reducing the number of negative fractional bits
    list<integral_c<int16_t, 8>, integral_c<int16_t, -4>, integral_c<int16_t, 6>, integral_c<int16_t, -2>, integral_c<int32_t, 112>>,
    list<integral_c<int16_t, 10>, integral_c<int16_t, -4>, integral_c<int16_t, 12>, integral_c<int16_t, -2>, integral_c<int32_t, 4080>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, -6>, integral_c<int16_t, 9>, integral_c<int16_t, -4>, integral_c<int32_t, 8128>>,
    // Test increasing the number of negative fractional bits with negative values
    list<integral_c<int16_t, 8>, integral_c<int16_t, -2>, integral_c<int16_t, 6>, integral_c<int16_t, -4>, integral_c<int32_t, -112>>,
    list<integral_c<int16_t, 10>, integral_c<int16_t, -2>, integral_c<int16_t, 12>, integral_c<int16_t, -4>, integral_c<int32_t, -4080>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, -4>, integral_c<int16_t, 9>, integral_c<int16_t, -6>, integral_c<int32_t, -8128>>,
    // Test reducing the number of negative fractional bits with negative values
    list<integral_c<int16_t, 8>, integral_c<int16_t, -4>, integral_c<int16_t, 6>, integral_c<int16_t, -2>, integral_c<int32_t, -112>>,
    list<integral_c<int16_t, 10>, integral_c<int16_t, -4>, integral_c<int16_t, 12>, integral_c<int16_t, -2>, integral_c<int32_t, -4080>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, -6>, integral_c<int16_t, 9>, integral_c<int16_t, -4>, integral_c<int32_t, -8128>>
    > test_template_parameters_PNPN_conversion; 

BOOST_AUTO_TEST_CASE_TEMPLATE(Conversion_test_int_PNPN, T, test_template_parameters_PNPN_conversion) {
    typedef typename at<T, int_<0>>::type INT_BITS;
    typedef typename at<T, int_<1>>::type FRAC_BITS;
    typedef typename at<T, int_<2>>::type INT_BITS_NEW;
    typedef typename at<T, int_<3>>::type FRAC_BITS_NEW;
    typedef typename at<T, int_<4>>::type EFP_VALUE;

    extended_fixed_point_t<INT_BITS::value, FRAC_BITS::value> curr_efp(EFP_VALUE::value);
    extended_fixed_point_t<INT_BITS_NEW::value, FRAC_BITS_NEW::value> curr_efp_2(EFP_VALUE::value);
    extended_fixed_point_t<INT_BITS_NEW::value, FRAC_BITS_NEW::value> new_efp = curr_efp.template convert<INT_BITS_NEW::value, FRAC_BITS_NEW::value>();

    BOOST_TEST(EFP_VALUE::value == new_efp.getValue()); 
}

// From INT_PART >= 0, FRAC_PART < 0 to INT_PART >= 0, FRAC_PART < 0 - Floating point values
// Not tested, floating point values are erased

// From INT_PART < 0, FRAC_PART >= 0 to INT_PART < 0, FRAC_PART >= 0 - Integer values
// Not tested, integer values are erased

// From INT_PART < 0, FRAC_PART >= 0 to INT_PART < 0, FRAC_PART >= 0 - Floating point values

const float test_float_NPNP_parameters[] = {// Corner case  
                                            0.0,
                                            // Random values  
                                            0.0078125, 0.0117188, 0.0273438, 0.00195312, 0.00195312, 0.0214844, 0.0195312, 0.0253906, 0.00390625, 0.0195312,
                                            // Random negative values 
                                            -0.0078125, -0.0117188, -0.0273438, -0.00195312, -0.00195312, -0.0214844, -0.0195312, -0.0253906, -0.00390625, -0.0195312
                                            };

BOOST_DATA_TEST_CASE(Conversion_test_float_NPNP, bdata::make(test_float_NPNP_parameters), test_value) {
    const double TOLERANCE = 1e-9;
    extended_fixed_point_t<-2, 30> curr_efp(test_value);
    extended_fixed_point_t<-4, 30> new_efp_first = curr_efp.template convert<-4, 30>();

    BOOST_TEST(std::abs(test_value - new_efp_first.getValueFD()) < TOLERANCE);

    extended_fixed_point_t<-1, 30> new_efp_second = curr_efp.template convert<-1, 30>();

    BOOST_TEST(std::abs(test_value - new_efp_second.getValueFD()) < TOLERANCE);
}

// From INT_PART >= 0, FRAC_PART >= 0 to INT_PART >= 0, FRAC_PART < 0 - Integer values

typedef list<
    // All test values terminates with a certain number of zeros
    // Test maintaining the overall number of bits 
    list<integral_c<int16_t, 8>, integral_c<int16_t, 0>, integral_c<int16_t, 6>, integral_c<int16_t, -2>, integral_c<int32_t, 124>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, 0>, integral_c<int16_t, 10>, integral_c<int16_t, -6>, integral_c<int32_t, 32704>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, 0>, integral_c<int16_t, 18>, integral_c<int16_t, -14>, integral_c<int32_t, 2147467264>>,
    // Test reducing the overall number of bits
    list<integral_c<int16_t, 8>, integral_c<int16_t, 0>, integral_c<int16_t, 4>, integral_c<int16_t, -2>, integral_c<int32_t, 56>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, 0>, integral_c<int16_t, 10>, integral_c<int16_t, -4>, integral_c<int32_t, 16368>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, 0>, integral_c<int16_t, 16>, integral_c<int16_t, -8>, integral_c<int32_t, 32512>>,
    // Test increasing the overall number of bits 
    list<integral_c<int16_t, 8>, integral_c<int16_t, 0>, integral_c<int16_t, 14>, integral_c<int16_t, -2>, integral_c<int32_t, 124>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, 0>, integral_c<int16_t, 24>, integral_c<int16_t, -6>, integral_c<int32_t, 32704>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, 0>, integral_c<int16_t, 46>, integral_c<int16_t, -14>, integral_c<int32_t, 2147467264>>,
    // Test maintaining the overall number of bits with negative numbers
    list<integral_c<int16_t, 8>, integral_c<int16_t, 0>, integral_c<int16_t, 6>, integral_c<int16_t, -2>, integral_c<int32_t, -124>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, 0>, integral_c<int16_t, 10>, integral_c<int16_t, -6>, integral_c<int32_t, -32704>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, 0>, integral_c<int16_t, 18>, integral_c<int16_t, -14>, integral_c<int32_t, -2147467264>>,
    // Test reducing the overall number of bits with negative numbers
    list<integral_c<int16_t, 8>, integral_c<int16_t, 0>, integral_c<int16_t, 4>, integral_c<int16_t, -2>, integral_c<int32_t, -56>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, 0>, integral_c<int16_t, 10>, integral_c<int16_t, -4>, integral_c<int32_t, -16368>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, 0>, integral_c<int16_t, 16>, integral_c<int16_t, -8>, integral_c<int32_t, -32512>>,
    // Test increasing the overall number of bits with negative numbers
    list<integral_c<int16_t, 8>, integral_c<int16_t, 0>, integral_c<int16_t, 14>, integral_c<int16_t, -2>, integral_c<int32_t, -124>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, 0>, integral_c<int16_t, 24>, integral_c<int16_t, -6>, integral_c<int32_t, -32704>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, 0>, integral_c<int16_t, 46>, integral_c<int16_t, -14>, integral_c<int32_t, -2147467264>>
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

// From INT_PART >= 0, FRAC_PART >= 0 to INT_PART >= 0, FRAC_PART < 0 - Floating point values
// Not tested because floating point values are erased

// From INT_PART >= 0, FRAC_PART >= 0 to INT_PART < 0, FRAC_PART >= 0 - Integer values
// Not tested because integer values are erased

// From INT_PART >= 0, FRAC_PART >= 0 to INT_PART < 0, FRAC_PART >= 0 - Floating point values
// Test:
// 1) Maintained the overall amount of fractional bits 
// 2) Increased the number of fractional bits
// 3) Reduced the number of fractional bits

const float test_float_PPNP_parameters[] = {// Corner case  
                                            0.0,
                                            // Random values  
                                            0.0078125, 0.0117188, 0.0273438, 0.00195312, 0.00195312, 0.0214844, 0.0195312, 0.0253906, 0.00390625, 0.0195312,
                                            // Random negative values 
                                            -0.0078125, -0.0117188, -0.0273438, -0.00195312, -0.00195312,- 0.0214844, -0.0195312, -0.0253906, -0.00390625, -0.0195312
                                            };

BOOST_DATA_TEST_CASE(Conversion_test_float_PPNP, bdata::make(test_float_PPNP_parameters), test_value) {
    const double TOLERANCE = 1e-9;
    extended_fixed_point_t<4, 30> curr_efp(test_value);
    extended_fixed_point_t<-2, 30> new_efp_first = curr_efp.template convert<-2, 30>();

    BOOST_TEST(std::abs(test_value - new_efp_first.getValueFD()) < TOLERANCE);

    curr_efp.getValueFD();
    new_efp_first.getValueFD();
}

// From INT_PART >= 0, FRAC_PART < 0 to INT_PART >= 0, FRAC_PART >= 0 - Integer values

typedef list<
    // Test maintaining the overall number of bits 
    list<integral_c<int16_t, 8>, integral_c<int16_t, -2>, integral_c<int16_t, 10>, integral_c<int16_t, 0>, integral_c<int32_t, 508>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, -4>, integral_c<int16_t, 20>, integral_c<int16_t, 0>, integral_c<int32_t, 524272>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, -12>, integral_c<int16_t, 44>, integral_c<int16_t, 0>, integral_c<int64_t, 4398046507008>>,
    // Test reducing the overall number of bits
    list<integral_c<int16_t, 8>, integral_c<int16_t, -2>, integral_c<int16_t, 6>, integral_c<int16_t, 0>, integral_c<int32_t, 60>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, -4>, integral_c<int16_t, 14>, integral_c<int16_t, 0>, integral_c<int32_t, 8176>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, -12>, integral_c<int16_t, 36>, integral_c<int16_t, 0>, integral_c<int32_t, 1073737728>>,
    // Test increasing the overall number of bits 
    list<integral_c<int16_t, 8>, integral_c<int16_t, -2>, integral_c<int16_t, 14>, integral_c<int16_t, 0>, integral_c<int32_t, 508>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, -4>, integral_c<int16_t, 24>, integral_c<int16_t, 0>, integral_c<int32_t, 524272>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, -6>, integral_c<int16_t, 46>, integral_c<int16_t, 0>, integral_c<int64_t, 4398046507008>>,
    // Test maintaining the overall number of bits with negative numbers
    list<integral_c<int16_t, 8>, integral_c<int16_t, -2>, integral_c<int16_t, 10>, integral_c<int16_t, 0>, integral_c<int32_t, -508>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, -4>, integral_c<int16_t, 20>, integral_c<int16_t, 0>, integral_c<int32_t, -524272>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, -12>, integral_c<int16_t, 44>, integral_c<int16_t, 0>, integral_c<int64_t, -4398046507008>>,
    // Test reducing the overall number of bits with negative numbers
    list<integral_c<int16_t, 8>, integral_c<int16_t, -2>, integral_c<int16_t, 6>, integral_c<int16_t, 0>, integral_c<int32_t, -60>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, -4>, integral_c<int16_t, 14>, integral_c<int16_t, 0>, integral_c<int32_t, -8176>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, -12>, integral_c<int16_t, 36>, integral_c<int16_t, 0>, integral_c<int32_t, -1073737728>>,
    // Test increasing the overall number of bits with negative numbers
    list<integral_c<int16_t, 8>, integral_c<int16_t, -2>, integral_c<int16_t, 14>, integral_c<int16_t, 0>, integral_c<int32_t, -508>>,
    list<integral_c<int16_t, 16>, integral_c<int16_t, -4>, integral_c<int16_t, 24>, integral_c<int16_t, 0>, integral_c<int32_t, -524272>>,
    list<integral_c<int16_t, 32>, integral_c<int16_t, -6>, integral_c<int16_t, 46>, integral_c<int16_t, 0>, integral_c<int64_t, -4398046507008>>
    > test_template_parameters_PNPP_conversion;

    BOOST_AUTO_TEST_CASE_TEMPLATE(Conversion_test_int_PNPP, T, test_template_parameters_PNPP_conversion) {
    typedef typename at<T, int_<0>>::type INT_BITS;
    typedef typename at<T, int_<1>>::type FRAC_BITS;
    typedef typename at<T, int_<2>>::type INT_BITS_NEW;
    typedef typename at<T, int_<3>>::type FRAC_BITS_NEW;
    typedef typename at<T, int_<4>>::type EFP_VALUE;

    extended_fixed_point_t<INT_BITS::value, FRAC_BITS::value> curr_efp(EFP_VALUE::value);
    extended_fixed_point_t<INT_BITS_NEW::value, FRAC_BITS_NEW::value> new_efp = curr_efp.template convert<INT_BITS_NEW::value, FRAC_BITS_NEW::value>();

    BOOST_TEST(curr_efp.getValue() == new_efp.getValue()); 
}

// From INT_PART >= 0, FRAC_PART < 0 to INT_PART >= 0, FRAC_PART >= 0 - Floating point values
// Not tested because floating point values are erased

// From INT_PART < 0, FRAC_PART >= 0 to INT_PART >= 0, FRAC_PART >= 0 - Integer values
// Not tested because integer values are erased

// From INT_PART < 0, FRAC_PART >= 0 to INT_PART >= 0, FRAC_PART >= 0 - Floating point values

const float test_float_NPPP_parameters[] = {// Corner case  
                                            0.0,
                                            // Random values  
                                            0.0078125, 0.0117188, 0.0273438, 0.00195312, 0.00195312, 0.0214844, 0.0195312, 0.0253906, 0.00390625, 0.0195312,
                                            // Random negative values 
                                            -0.0078125, -0.0117188, -0.0273438, -0.00195312, -0.00195312,- 0.0214844, -0.0195312, -0.0253906, -0.00390625, -0.0195312
                                            };

BOOST_DATA_TEST_CASE(Conversion_test_float_NPPP, bdata::make(test_float_NPPP_parameters), test_value) {
    const double TOLERANCE = 1e-9;
    extended_fixed_point_t<2, 30> curr_efp(test_value);
    extended_fixed_point_t<-2, 30> new_efp_first = curr_efp.template convert<-2, 30>();

    BOOST_TEST(std::abs(test_value - new_efp_first.getValueFD()) < TOLERANCE);
}
BOOST_AUTO_TEST_SUITE_END()