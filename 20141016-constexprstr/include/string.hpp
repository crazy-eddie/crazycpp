#ifndef STRING_HPP
#define STRING_HPP

#include <boost/mpl/int.hpp>

namespace detail_ {

template < int ... Nums >
struct indices
{
    template < int I >
    static constexpr auto append(boost::mpl::int_<I>)
    {
        return indices<Nums...,I>();
    }
};

constexpr indices<> make_indices(boost::mpl::int_<0>)
{
    return indices<>();
}

template < int I >
constexpr auto make_indices(boost::mpl::int_<I>)
{
    using prev = boost::mpl::int_<I-1>;
    return make_indices(prev()).append(prev());
}


}

template < int Size >
constexpr auto make_string(char const (&) [Size]);

template < int Size >
struct string
{
    using data_type = char const (&) [Size+1];

    constexpr int size() const
    {
        return Size;
    }

    constexpr data_type c_str() const
    {
        return arr;
    }

    constexpr string<Size+1> push_back(char c) const
    {
        return push_back(c, detail_::make_indices(boost::mpl::int_<Size>()));
    }

    constexpr string<Size+1> push_front(char c) const
    {
        return push_front(c, detail_::make_indices(boost::mpl::int_<Size>()));
    }

    constexpr string(char const (&str) [Size+1])
        : string(str, detail_::make_indices(boost::mpl::int_<Size>()))
    {}

    template < int I >
    constexpr string<Size+I-1> append(char const (&cstr)[I]) const
    {
        return append( detail_::make_indices(boost::mpl::int_<Size>())
                     , detail_::make_indices(boost::mpl::int_<I-1>())
                     , cstr );
    }

    template < int I >
    constexpr string<Size+I> append(string<I> const& s) const
    {
        return append( detail_::make_indices(boost::mpl::int_<Size>())
                     , detail_::make_indices(boost::mpl::int_<I>())
                     , s.c_str() );
    }

    template < typename ... T >
    constexpr string(T ... t)
        : arr{t..., '\0'}
    {}

private:
    char arr[Size+1];

    template < int I, int ... Indices >
    constexpr string(char const (&str) [I], detail_::indices<Indices...>)
        : arr{str[Indices]..., '\0'}
    {}

    template < int ... Indices >
    constexpr string<Size+1> push_back(char c, detail_::indices<Indices...>) const
    {
        return string<Size+1>(arr[Indices]..., c);
    }

    template < int ... Indices >
    constexpr string<Size+1> push_front(char c, detail_::indices<Indices...>) const
    {
        return string<Size+1>(c, arr[Indices]...);
    }

    template < int ... ThisIndices
             , int ... ThatIndices
             , int I >
    constexpr string<Size+I-1> append( detail_::indices<ThisIndices...>
                                   , detail_::indices<ThatIndices...>
                                   , char const (&cstr) [I] ) const
    {
        return string<Size+I-1>(arr[ThisIndices]..., cstr[ThatIndices]...);
    }
};

template < int Size >
constexpr auto make_string(char const (&cstr) [Size])
{
    return string<Size-1>(cstr);
}

template < int I >
constexpr string<I + 1> operator + (string<I> const& s, char c)
{
    return s.push_back(c);
}

template < int I >
constexpr string<I + 1> operator + (char c, string<I> const& s)
{
    return s.push_front(c);
}

template < int I0, int I1>
constexpr string<I0+I1> operator + (string<I0> const& s0, string<I1> const& s1)
{
    return s0.append(s1);
}

#endif
