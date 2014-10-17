#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE istr
#include <boost/test/unit_test.hpp>

#include "../include/istr.hpp"
#include <boost/mpl/int.hpp>
#include <boost/mpl/char.hpp>

BOOST_AUTO_TEST_CASE(integer_to_string)
{
    constexpr auto s0 = istr(boost::mpl::int_<42>());
    BOOST_CHECK_EQUAL(s0.c_str(), "42");

    using c = boost::mpl::char_<s0.c_str()[1]>;
    using s = boost::mpl::int_<s0.size()>;

    BOOST_CHECK_EQUAL(c::value, '2');
    BOOST_CHECK_EQUAL(s::value, 2);

    BOOST_CHECK_EQUAL(istr(boost::mpl::int_<0>()).c_str(), "0");
    BOOST_CHECK_EQUAL(istr(boost::mpl::int_<10>()).c_str(), "10");
    BOOST_CHECK_EQUAL(istr(boost::mpl::int_<100>()).c_str(), "100");
}
