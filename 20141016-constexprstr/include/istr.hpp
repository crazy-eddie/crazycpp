#ifndef ISTR_HPP
#define ISTR_HPP

#include "string.hpp"

namespace detail_
{

constexpr string<0> istr(boost::mpl::int_<0>)
{
    return string<0>();
}

template < int I >
constexpr auto istr(boost::mpl::int_<I> i)
{
    constexpr int tens = I / 10;
    constexpr int ones = I % 10;

    return istr(boost::mpl::int_<tens>()).push_back('0' + ones);
}

}

template < int I >
constexpr auto istr(boost::mpl::int_<I> i)
{
    return detail_::istr(i);
}

constexpr string<1> istr(boost::mpl::int_<0>) { return make_string("0"); }


#endif
