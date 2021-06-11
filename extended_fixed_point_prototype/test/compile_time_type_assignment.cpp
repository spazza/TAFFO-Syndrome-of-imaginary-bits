#define BOOST_TEST_MODULE Compile_time_type_assignment

#include "extended_fixed_point.hpp"
#include <typeinfo>

#include <boost/test/included/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/int.hpp>

#define INT8_T   "a"
#define INT16_T  "s"
#define INT32_T  "i"
#define INT64_T  "l"
#define INT128_T "n"

using namespace boost;


/**
 * Test designed to check the correct raw type assignment of the extended floating point at compile-time.
 * 
 * Starting from 32 bit integer some lines are commented, this is due to the undefined behavior of the
 * shift operator, in fact the corner cases with 32/64/128 in the fractional part and 0 or a negative value
 * in the integer part produce a warning by GCC compiler.
 * It's better not to use the extreme values for the fractional part like 32,64,128 otherwise the shift will
 * overcome the width of the type.
*/ 


// Integer 8 bit test

typedef mpl::list<
    // Corner Cases
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 7>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 7>>,
    mpl::list<mpl::integral_c<int16_t, -128>, mpl::integral_c<int16_t, 7>>,
    mpl::list<mpl::integral_c<int16_t, 7>, mpl::integral_c<int16_t, -128>>,
    // Random values
    mpl::list<mpl::integral_c<int16_t, 3>, mpl::integral_c<int16_t, 2>>,
    mpl::list<mpl::integral_c<int16_t, -2>, mpl::integral_c<int16_t, 5>>,
    mpl::list<mpl::integral_c<int16_t, 3>, mpl::integral_c<int16_t, 4>>
    > test_template_parameters_8bit;

BOOST_AUTO_TEST_CASE_TEMPLATE(Compile_time_type_assignment_8bit, T, test_template_parameters_8bit) {
    typedef typename mpl::at<T, mpl::int_<0>>::type first;
    typedef typename mpl::at<T, mpl::int_<1>>::type second;

    const int DONT_CARE_VALUE = 0;
    
    extended_fixed_point_t<first::value, second::value> efp(DONT_CARE_VALUE);

    BOOST_TEST(typeid(efp.getRaw()).name() == INT8_T);
}

// Integer 16 bit test

typedef mpl::list<
    // Corner Cases
    mpl::list<mpl::integral_c<int16_t, 8>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 8>>,
    mpl::list<mpl::integral_c<int16_t, 8>, mpl::integral_c<int16_t, 7>>,
    mpl::list<mpl::integral_c<int16_t, 15>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 15>>,
    mpl::list<mpl::integral_c<int16_t, 15>, mpl::integral_c<int16_t, -128>>,
    mpl::list<mpl::integral_c<int16_t, -128>, mpl::integral_c<int16_t, 15>>,
    // Random values
    mpl::list<mpl::integral_c<int16_t, 3>, mpl::integral_c<int16_t, 11>>,
    mpl::list<mpl::integral_c<int16_t, 8>, mpl::integral_c<int16_t, 5>>
    > test_template_parameters_16bit;

BOOST_AUTO_TEST_CASE_TEMPLATE(Compile_time_type_assignment_16bit, T, test_template_parameters_16bit){
    typedef typename mpl::at<T, mpl::int_<0>>::type first;
    typedef typename mpl::at<T, mpl::int_<1>>::type second;

    const int DONT_CARE_VALUE = 0;
    
    extended_fixed_point_t<first::value, second::value> efp(DONT_CARE_VALUE);

    BOOST_TEST(typeid(efp.getRaw()).name() == INT16_T);
}

// Integer 32 bit test

typedef mpl::list<
    // Corner Cases
    mpl::list<mpl::integral_c<int16_t, 16>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 16>>,
    mpl::list<mpl::integral_c<int16_t, 16>, mpl::integral_c<int16_t, 15>>,
    mpl::list<mpl::integral_c<int16_t, 31>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 31>>,
    mpl::list<mpl::integral_c<int16_t, 31>, mpl::integral_c<int16_t, -128>>,
    mpl::list<mpl::integral_c<int16_t, -128>, mpl::integral_c<int16_t, 31>>,
    // Random values
    mpl::list<mpl::integral_c<int16_t, 8>, mpl::integral_c<int16_t, 18>>,
    mpl::list<mpl::integral_c<int16_t, 21>, mpl::integral_c<int16_t, 5>>
    > test_template_parameters_32bit;

BOOST_AUTO_TEST_CASE_TEMPLATE(Compile_time_type_assignment_32bit, T, test_template_parameters_32bit) {
    typedef typename mpl::at<T, mpl::int_<0>>::type first;
    typedef typename mpl::at<T, mpl::int_<1>>::type second;

    const int DONT_CARE_VALUE = 0;
    
    extended_fixed_point_t<first::value, second::value> efp(DONT_CARE_VALUE);

    BOOST_TEST(typeid(efp.getRaw()).name() == INT32_T);
}


// Integer 64 bit test

typedef mpl::list<
    // Corner Cases
    mpl::list<mpl::integral_c<int16_t, 32>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 32>>,
    mpl::list<mpl::integral_c<int16_t, 32>, mpl::integral_c<int16_t, 31>>,
    mpl::list<mpl::integral_c<int16_t, 63>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 63>>,
    mpl::list<mpl::integral_c<int16_t, 63>, mpl::integral_c<int16_t, -128>>,
    mpl::list<mpl::integral_c<int16_t, -128>, mpl::integral_c<int16_t, 63>>,
    // Random values
    mpl::list<mpl::integral_c<int16_t, 18>, mpl::integral_c<int16_t, 23>>,
    mpl::list<mpl::integral_c<int16_t, 49>, mpl::integral_c<int16_t, 5>>
    > test_template_parameters_64bit;

BOOST_AUTO_TEST_CASE_TEMPLATE(Compile_time_type_assignment_64bit, T, test_template_parameters_64bit){
    typedef typename mpl::at<T, mpl::int_<0>>::type first;
    typedef typename mpl::at<T, mpl::int_<1>>::type second;

    const int DONT_CARE_VALUE = 0;
    
    extended_fixed_point_t<first::value, second::value> efp(DONT_CARE_VALUE);

    BOOST_TEST(typeid(efp.getRaw()).name() == INT64_T);
}

// Integer 128 bit test

#ifdef _IS64bit

typedef mpl::list<
    // Corner Cases
    mpl::list<mpl::integral_c<int16_t, 64>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 64>>,
    mpl::list<mpl::integral_c<int16_t, 64>, mpl::integral_c<int16_t, 63>>,
    mpl::list<mpl::integral_c<int16_t, 127>, mpl::integral_c<int16_t, 0>>,
    mpl::list<mpl::integral_c<int16_t, 0>, mpl::integral_c<int16_t, 127>>,
    mpl::list<mpl::integral_c<int16_t, 127>, mpl::integral_c<int16_t, -128>>,
    mpl::list<mpl::integral_c<int16_t, -128>, mpl::integral_c<int16_t, 127>>,
    // Random values
    mpl::list<mpl::integral_c<int16_t, 90>, mpl::integral_c<int16_t, 23>>,
    mpl::list<mpl::integral_c<int16_t, 49>, mpl::integral_c<int16_t, 57>>
    > test_template_parameters_128bit;

BOOST_AUTO_TEST_CASE_TEMPLATE(Compile_time_type_assignment_128bit, T, test_template_parameters_128bit){
    typedef typename mpl::at<T, mpl::int_<0>>::type first;
    typedef typename mpl::at<T, mpl::int_<1>>::type second;

    const int DONT_CARE_VALUE = 0;
    
    extended_fixed_point_t<first::value, second::value> efp(DONT_CARE_VALUE);

    BOOST_TEST(typeid(efp.getRaw()).name() == INT128_T);
}

#endif