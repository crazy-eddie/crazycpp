#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <array>

struct matrix
{
    matrix(std::array<int,9> init) : vals(std::move(init)) {}

    int value(int i,int j) const
    {
        return vals[i * 3 + j];
    }

private:
    std::array<int, 9> vals;
};

template < typename Right
         , typename Left >
struct add_matrix
{
    add_matrix( Right const& r
              , Left const& l )
        : right(r)
        , left(l)
    {}

    add_matrix(add_matrix const& other)
        : right(other.right)
        , left(other.left)
    {}
    add_matrix & operator = (add_matrix const&) = delete;

    int value(int i, int j) const
    {
        return right.value(i,j) + left.value(i,j);
    }
private:
    Right const& right;
    Left const& left;
};

template < typename Right, typename Left >
auto operator + (Right const& r, Left const& l)
{
    return add_matrix<Right,Left>{r,l};
}

#endif
