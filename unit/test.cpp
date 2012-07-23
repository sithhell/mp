//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <mp/mp.hpp>
#include <mp/mpfr.hpp>

#include <boost/detail/lightweight_test.hpp>

int main()
{
    using mp::mpfr;
    using mp::mp_;

    {
        mp_<mpfr> a(1.0)
                , b(2.0)
                , c(3.0)
                , d(4.0)
                , e(5.0)
                , f(6.0)
                , g(7.0)
                , h(8.0)
                , i(9.0)
                , j(10.0)
                , k(11.0)
                , l(12.0)
                , m(13.0)
                , n(14.0)
                , o(15.0)
                , p(16.0);

        mpfr::copy_count = 0;

        a = b + c;
        BOOST_TEST_EQ(boost::proto::value(a), mpfr(5.0));
        a = b + c + d;
        BOOST_TEST_EQ(boost::proto::value(a), mpfr(9.0));
        a = b + c + d + e;
        BOOST_TEST_EQ(boost::proto::value(a), mpfr(14.0));

        BOOST_TEST_EQ(mpfr::copy_count, 0);
    }

    return boost::report_errors();
}
