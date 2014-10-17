#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE string
#include <boost/test/unit_test.hpp>

#include "../include/string.hpp"

#include <boost/mpl/char.hpp>
#include <boost/mpl/int.hpp>

BOOST_AUTO_TEST_CASE(from_cstr)
{
    constexpr auto s0 = make_string("hello");
    BOOST_CHECK_EQUAL(s0.c_str(), "hello");

    using c = boost::mpl::char_<s0.c_str()[2]>;
    using s = boost::mpl::int_<s0.size()>;

    BOOST_CHECK_EQUAL(c::value, 'l');
    BOOST_CHECK_EQUAL(s::value, 5);
}

BOOST_AUTO_TEST_CASE(pushes)
{
    constexpr auto s0 = make_string("ell");
    constexpr auto s1 = s0.push_back('o');

    BOOST_CHECK_EQUAL(s1.c_str(), "ello");

    constexpr auto s2 = s1.push_front('h');

    BOOST_CHECK_EQUAL(s2.c_str(), "hello");

    using c = boost::mpl::char_<s2.c_str()[1]>;
    using s = boost::mpl::int_<s2.size()>;
}

BOOST_AUTO_TEST_CASE(appending)
{
    constexpr auto s0 = make_string("hello ");
    constexpr auto s1 = s0.append("world");
    constexpr auto s2 = make_string("hello world");
    constexpr auto s3 = s0.append(make_string("world"));

    BOOST_CHECK_EQUAL(s1.size(), s2.size());
    BOOST_CHECK_EQUAL(s1.c_str(), s2.c_str());

    using c = boost::mpl::char_<s1.c_str()[6]>;
    using s = boost::mpl::int_<s1.size()>;

    BOOST_CHECK_EQUAL(c::value, 'w');
    BOOST_CHECK_EQUAL(s::value, s1.size());

    BOOST_CHECK_EQUAL(s1.c_str(), s3.c_str());
}

BOOST_AUTO_TEST_CASE(operators)
{
    constexpr auto s0 = '[' + make_string("hello") + ' ' + make_string("world") + ']';

    BOOST_CHECK_EQUAL(s0.c_str(), "[hello world]");
}
