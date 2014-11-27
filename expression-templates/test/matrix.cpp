#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE matrix
#include <boost/test/unit_test.hpp>

#include "../include/matrix.hpp"

BOOST_AUTO_TEST_CASE(matrix_)
{
    auto m = matrix{{{ 1,0,0
                     , 0,1,0
                     , 0,0,1 }}};

    BOOST_CHECK_EQUAL(m.value(0,0), 1);
    BOOST_CHECK_EQUAL(m.value(0,1), 0);
    BOOST_CHECK_EQUAL(m.value(0,2), 0);

    BOOST_CHECK_EQUAL(m.value(1,0), 0);
    BOOST_CHECK_EQUAL(m.value(1,1), 1);
    BOOST_CHECK_EQUAL(m.value(1,2), 0);

    BOOST_CHECK_EQUAL(m.value(2,0), 0);
    BOOST_CHECK_EQUAL(m.value(2,1), 0);
    BOOST_CHECK_EQUAL(m.value(2,2), 1);
}

BOOST_AUTO_TEST_CASE(addition)
{
    auto m0 = matrix{{{ 1,2,3
                      , 4,5,6
                      , 7,8,9 }}};
    auto m1 = matrix{{{ 9,8,7
                      , 6,5,4
                      , 3,2,1 }}};

    auto exp = m0 + m1;
    matrix m = exp;

    for (int i = 0; i != 3; ++i)
    {
        for (int j = 0; j != 3; ++j)
        {
            BOOST_CHECK_EQUAL(exp.value(i,j), 10);
            BOOST_CHECK_EQUAL(m.value(i,j), 10);
        }
    }

    auto exp2 = m0 + m1;
    auto exp3 = exp + exp2;

    for (int i = 0; i != 3; ++i)
    {
        for (int j = 0; j != 3; ++j)
        {
            BOOST_CHECK_EQUAL(exp3.value(i,j), 20);
        }
    }
}
