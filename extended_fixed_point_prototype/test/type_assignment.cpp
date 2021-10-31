#ifndef GROUP_TEST
#define BOOST_TEST_MODULE Compile_time_type_assignment
#include <boost/test/included/unit_test.hpp>
#endif

#include <typeinfo>

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

#include "extended_fixed_point.hpp"

#define INT8_T   "a"
#define INT16_T  "s"
#define INT32_T  "i"
#define INT64_T  "l"
#define INT128_T "n"

using namespace std;
using namespace boost;

BOOST_AUTO_TEST_SUITE(Type_assignment)

/**
 * Test designed to check the correct raw type assignment at compile-time.
 * 8,16,32,64 bits have been checked.
 */ 

// Extended_fixed_point (INT_BITS >= 0, FRAC_BITS >= 0)

typedef mpl::list<
    // 8 bit tests
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 8>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 8>>,
    // 16 bit tests
    mpl::list<mpl::integral_c<int16_t, 9>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 9>>,
    mpl::list<mpl::integral_c<int16_t, 8>, mpl::integral_c<int16_t, 8>>,
    mpl::list<mpl::integral_c<int16_t, 16>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 16>>,
    // 32 bit tests
    mpl::list<mpl::integral_c<int16_t, 17>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 17>>,
    mpl::list<mpl::integral_c<int16_t, 16>, mpl::integral_c<int16_t, 16>>,
    mpl::list<mpl::integral_c<int16_t, 32>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 32>>,
    // 64 bit tests
    mpl::list<mpl::integral_c<int16_t, 33>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 33>>,
    mpl::list<mpl::integral_c<int16_t, 32>, mpl::integral_c<int16_t, 32>>,
    mpl::list<mpl::integral_c<int16_t, 64>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 64>>
> fixed_point_test_template_values;


BOOST_AUTO_TEST_CASE_TEMPLATE(Type_assignment_fixed_point, T, fixed_point_test_template_values) {
    typedef typename mpl::at<T, mpl::int_<0>>::type first;
    typedef typename mpl::at<T, mpl::int_<1>>::type second;

    string raw_string;
    extended_fixed_point_t<first::value, second::value> efp;

    if(first::value + second::value <= 8)
        raw_string = INT8_T;
    else if(first::value + second::value <= 16)
        raw_string = INT16_T;
    else if(first::value + second::value <= 32)
        raw_string = INT32_T;
    else 
        raw_string = INT64_T;

    BOOST_TEST(typeid(efp.getRaw()).name() == raw_string);
}

// Extended_fixed_point (INT_BITS < 0, FRAC_BITS >= 0)

typedef mpl::list<
    // 8 bit tests
    mpl::list<mpl::integral_c<int16_t, -128>, mpl::integral_c<int16_t, 8>>,
    // 16 bit tests
    mpl::list<mpl::integral_c<int16_t, -128>, mpl::integral_c<int16_t, 16>>,
    // 32 bit tests
    mpl::list<mpl::integral_c<int16_t, -128>, mpl::integral_c<int16_t, 32>>,
    // 64 bit tests
    mpl::list<mpl::integral_c<int16_t, -128>, mpl::integral_c<int16_t, 64>>
    > fixed_point_left_test_template_values;

BOOST_AUTO_TEST_CASE_TEMPLATE(Type_assignment_fixed_point_left, T, fixed_point_left_test_template_values) {
    typedef typename mpl::at<T, mpl::int_<0>>::type first;
    typedef typename mpl::at<T, mpl::int_<1>>::type second;

    string raw_string;
    extended_fixed_point_t<first::value, second::value> efp;

    if(second::value <= 8)
        raw_string = INT8_T;
    else if(second::value <= 16)
        raw_string = INT16_T;
    else if(second::value <= 32)
        raw_string = INT32_T;
    else 
        raw_string = INT64_T;

    BOOST_TEST(typeid(efp.getRaw()).name() == raw_string);
}

// Extended_fixed_point (INT_BITS >= 0, FRAC_BITS < 0)

typedef mpl::list<
    // 8 bit tests
    mpl::list<mpl::integral_c<int16_t, 8>, mpl::integral_c<int16_t, -128>>,
    // 16 bit tests
    mpl::list<mpl::integral_c<int16_t, 16>, mpl::integral_c<int16_t, -128>>,
    // 32 bit tests
    mpl::list<mpl::integral_c<int16_t, 32>, mpl::integral_c<int16_t, -128>>,
    // 64 bit tests
    mpl::list<mpl::integral_c<int16_t, 64>, mpl::integral_c<int16_t, -128>>
    > fixed_point_right_test_template_values;

BOOST_AUTO_TEST_CASE_TEMPLATE(Type_assignment_fixed_point_right, T, fixed_point_right_test_template_values) {
    typedef typename mpl::at<T, mpl::int_<0>>::type first;
    typedef typename mpl::at<T, mpl::int_<1>>::type second;

    string raw_string;
    extended_fixed_point_t<first::value, second::value> efp;

    if(first::value <= 8)
        raw_string = INT8_T;
    else if(first::value <= 16)
        raw_string = INT16_T;
    else if(first::value <= 32)
        raw_string = INT32_T;
    else 
        raw_string = INT64_T;

    BOOST_TEST(typeid(efp.getRaw()).name() == raw_string);
}
 
BOOST_AUTO_TEST_SUITE_END()