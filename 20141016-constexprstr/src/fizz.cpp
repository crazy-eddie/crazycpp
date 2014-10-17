#include "../include/string.hpp"
#include "../include/istr.hpp"

#include <iostream>

namespace detail_ {

template < bool five, bool three >
struct fizzy {};

template < int I >
constexpr auto make_fizzy(boost::mpl::int_<I>)
{
    return fizzy<I%5==0,I%3==0>();
}

template < typename Int >
constexpr auto fizzy_string(Int, fizzy<true,true>)
{
    return make_string("fizzbuzz");
}

template < typename Int >
constexpr auto fizzy_string(Int, fizzy<true,false>)
{
    return make_string("buzz");
}

template < typename Int >
constexpr auto fizzy_string(Int, fizzy<false,true>)
{
    return make_string("fizz");
}

template < typename Int >
constexpr auto fizzy_string(Int i, fizzy<false,false>)
{
    return istr(i);
}

template < int I >
constexpr auto fizzy_string(boost::mpl::int_<I> i)
{
    return fizzy_string(i, make_fizzy(i));
}

template < int End >
constexpr auto fizzbuzz( boost::mpl::int_<End> i
                       , boost::mpl::int_<End> )
{
    return fizzy_string(i);
}

template < int Beg, int End >
constexpr auto fizzbuzz( boost::mpl::int_<Beg> beg
                       , boost::mpl::int_<End> end )
{
    // Note: If I put a space after the , then 100 count exceeds maximum constexpr recursion level.
    //       99 will be OK though.  Recursion is exceeded in the make_indices function.  Turning it
    //       into a template metafunction might solve that.
    return fizzy_string(beg) + ',' + fizzbuzz(boost::mpl::int_<Beg+1>(), end);
}

}

template < typename Size >
constexpr auto fizzbuzz(Size s)
{
    return detail_::fizzbuzz(boost::mpl::int_<1>(), s);
}

int main()
{
    /*
     * Ubuntu clang version 3.4-1ubuntu3 (tags/RELEASE_34/final) (based on LLVM 3.4)
     * Target: x86_64-pc-linux-gnu
     * Thread model: posix
     */
    using upper = boost::mpl::int_<100>; // 100 exceeds constexpr recursion limit, 99 OK.
    constexpr auto fizz_str = fizzbuzz(upper());

    std::cout << fizz_str.c_str() << std::endl;
}
