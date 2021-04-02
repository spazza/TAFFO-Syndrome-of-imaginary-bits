#define BOOST_TEST_MODULE Compile_time_bit_width_assignment

#include "extended_fixed_point.hpp"

#include <boost/test/included/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

using namespace boost;

/*
 * Test designed to verify the correct assignment of the paramenters that will characterize
 * the extended_fixed_point, in particular the integer part, the fractional part and the 
 * overall bit width.
*/

// Test of templates with positive integer and fractional part

typedef mpl::list<
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 63>>,
    mpl::list<mpl::integral_c<int16_t, 63>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 63>, mpl::integral_c<int16_t, 63>>
    > test_template_parameters_pos_int_pos_frac;   

BOOST_AUTO_TEST_CASE_TEMPLATE(Template_test_pos_int_pos_frac, T, test_template_parameters_pos_int_pos_frac){
    typedef typename mpl::at<T, mpl::int_<0>>::type first;
    typedef typename mpl::at<T, mpl::int_<1>>::type second;

    const int DONT_CARE_VALUE = 0;

    extended_fixed_point_t<first::value, second::value> efp(DONT_CARE_VALUE);

    int16_t integer_length = efp.integer_length;
    int16_t fractional_length = efp.fractional_length;
    uint16_t bit_width = efp.bit_width;

    BOOST_TEST(integer_length == first::value);
    BOOST_TEST(fractional_length == second::value);
    BOOST_TEST(bit_width == first::value + second::value);
}

// Test of templates with positive integer part and negative fractional part

typedef mpl::list<
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, -63>>,
    mpl::list<mpl::integral_c<int16_t, 63>, mpl::integral_c<int16_t, -63>>,
    mpl::list<mpl::integral_c<int16_t, 127>, mpl::integral_c<int16_t, -127>>
    > test_template_parameters_pos_int_neg_frac;   

BOOST_AUTO_TEST_CASE_TEMPLATE(Template_test_pos_int_neg_frac, T, test_template_parameters_pos_int_neg_frac){
    typedef typename mpl::at<T, mpl::int_<0>>::type first;
    typedef typename mpl::at<T, mpl::int_<1>>::type second;

    const int DONT_CARE_VALUE = 0;

    extended_fixed_point_t<first::value, second::value> efp(DONT_CARE_VALUE);

    int16_t integer_length = efp.integer_length;
    int16_t fractional_length = efp.fractional_length;
    uint16_t bit_width = efp.bit_width;

    BOOST_TEST(integer_length == first::value);
    BOOST_TEST(fractional_length == second::value);
    BOOST_TEST(bit_width == first::value);
}

//   Test of templates with negative integer part and positive fractional part

typedef mpl::list<
    mpl::list<mpl::integral_c<int16_t, -63>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, -63>, mpl::integral_c<int16_t, 63>>,
    mpl::list<mpl::integral_c<int16_t, -127>, mpl::integral_c<int16_t, 127>>
    > test_template_parameters_neg_int_pos_frac;   

BOOST_AUTO_TEST_CASE_TEMPLATE(Template_test_neg_int_pos_frac, T, test_template_parameters_neg_int_pos_frac){
    typedef typename mpl::at<T, mpl::int_<0>>::type first;
    typedef typename mpl::at<T, mpl::int_<1>>::type second;

    const int DONT_CARE_VALUE = 0;

    extended_fixed_point_t<first::value, second::value> efp(DONT_CARE_VALUE);

    int16_t integer_length = efp.integer_length;
    int16_t fractional_length = efp.fractional_length;
    uint16_t bit_width = efp.bit_width;

    BOOST_TEST(integer_length == first::value);
    BOOST_TEST(fractional_length == second::value);
    BOOST_TEST(bit_width == second::value);
}

////   Test of templates with negative integer part and negative fractional part

// Already checked at compile time with a static_assert