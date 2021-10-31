#ifndef GROUP_TEST
#define BOOST_TEST_MODULE Compile_time_bit_width_assignment
#include <boost/test/included/unit_test.hpp>
#endif

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

#include "extended_fixed_point.hpp"

using namespace boost;

/*
 * Test designed to verify the correct assignment of the paramenters that will characterize
 * the extended_fixed_point, in particular the integer part, the fractional part and the 
 * overall bit width.
*/

BOOST_AUTO_TEST_SUITE(Bit_width_assignment)

// Extended fixed point (INT_BITS >= 0, FRAC_BITS >= 0)

typedef mpl::list<
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 63>>,
    mpl::list<mpl::integral_c<int16_t, 63>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 63>, mpl::integral_c<int16_t, 63>>
    > test_template_parameters_pos_int_pos_frac;   

BOOST_AUTO_TEST_CASE_TEMPLATE(Template_test_pos_int_pos_frac, T, test_template_parameters_pos_int_pos_frac){
    typedef typename mpl::at<T, mpl::int_<0>>::type first;
    typedef typename mpl::at<T, mpl::int_<1>>::type second;

    int16_t integer_length = extended_fixed_point_t<first::value, second::value>::integer_length;
    int16_t fractional_length = extended_fixed_point_t<first::value, second::value>::fractional_length;
    uint16_t bit_width = extended_fixed_point_t<first::value, second::value>::bit_width;

    BOOST_TEST(integer_length == first::value);
    BOOST_TEST(fractional_length == second::value);
    BOOST_TEST(bit_width == first::value + second::value);
}

// Extended fixed point (INT_BITS >= 0, FRAC_BITS < 0)

typedef mpl::list<
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, -63>>,
    mpl::list<mpl::integral_c<int16_t, 63>, mpl::integral_c<int16_t, -63>>,
    mpl::list<mpl::integral_c<int16_t, 127>, mpl::integral_c<int16_t, -127>>
    > test_template_parameters_pos_int_neg_frac;   

BOOST_AUTO_TEST_CASE_TEMPLATE(Template_test_pos_int_neg_frac, T, test_template_parameters_pos_int_neg_frac){
    typedef typename mpl::at<T, mpl::int_<0>>::type first;
    typedef typename mpl::at<T, mpl::int_<1>>::type second;

    int16_t integer_length = extended_fixed_point_t<first::value, second::value>::integer_length;
    int16_t fractional_length = extended_fixed_point_t<first::value, second::value>::fractional_length;
    uint16_t bit_width = extended_fixed_point_t<first::value, second::value>::bit_width;

    BOOST_TEST(integer_length == first::value);
    BOOST_TEST(fractional_length == second::value);
    BOOST_TEST(bit_width == first::value);
}

// Extended fixed point (INT_BITS < 0, FRAC_BITS >= 0)

typedef mpl::list<
    mpl::list<mpl::integral_c<int16_t, -63>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, -63>, mpl::integral_c<int16_t, 63>>,
    mpl::list<mpl::integral_c<int16_t, -127>, mpl::integral_c<int16_t, 127>>
    > test_template_parameters_neg_int_pos_frac;   

BOOST_AUTO_TEST_CASE_TEMPLATE(Template_test_neg_int_pos_frac, T, test_template_parameters_neg_int_pos_frac){
    typedef typename mpl::at<T, mpl::int_<0>>::type first;
    typedef typename mpl::at<T, mpl::int_<1>>::type second;

    int16_t integer_length = extended_fixed_point_t<first::value, second::value>::integer_length;
    int16_t fractional_length = extended_fixed_point_t<first::value, second::value>::fractional_length;
    uint16_t bit_width = extended_fixed_point_t<first::value, second::value>::bit_width;

    BOOST_TEST(integer_length == first::value);
    BOOST_TEST(fractional_length == second::value);
    BOOST_TEST(bit_width == second::value);
}

// Extended fixed point (INT_BITS < 0, FRAC_BITS < 0)

// Already checked at compile time with a static_assert

BOOST_AUTO_TEST_SUITE_END()