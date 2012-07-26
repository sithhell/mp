//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <iostream>

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
                , h(8.0);

        mpfr x;

        mpfr::copy_count = 0;

        a = b + c;
        //BOOST_TEST_EQ(a, 5.0);
        a = b + c + d;
        //BOOST_TEST_EQ(a, 9.0);
        a = b + c + d + e;
        //BOOST_TEST_EQ(a, 14.0);
        a = b + c + d + e + f;
        //BOOST_TEST_EQ(a, 20.0);
        a = b + c + d + e + f + g;
        //BOOST_TEST_EQ(a, 27.0);
        a = b + c + d + e + f + g + h;
        //BOOST_TEST_EQ(a, 35.0);
        a = 10 + b + c + d + e + f + g + h;
        //BOOST_TEST_EQ(a, 45.0);
        a = b + 10 + c + d + e + f + g + h;
        //BOOST_TEST_EQ(a, 45.0);
        a = b + c + 10 + d + e + f + g + h;
        //BOOST_TEST_EQ(a, 45.0);
        a = b + c + d + 10 + e + f + g + h;
        //BOOST_TEST_EQ(a, 45.0);
        a = b + c + d + e + 10 + f + g + h;
        //BOOST_TEST_EQ(a, 45.0);
        a = b + c + d + e + f + 10 + g + h;
        //BOOST_TEST_EQ(a, 45.0);
        a = b + c + d + e + f + g + 10 + h;
        //BOOST_TEST_EQ(a, 45.0);
        a = b + c + d + e + f + g + h + 10;
        //BOOST_TEST_EQ(a, 45.0);

        BOOST_TEST_EQ(mpfr::copy_count, 0);
        
        x = b + c;
        BOOST_TEST_EQ(x, 5.0);
        x = b + c + d;
        BOOST_TEST_EQ(x, 9.0);
        x = b + c + d + e;
        BOOST_TEST_EQ(x, 14.0);
        x = b + c + d + e + f;
        BOOST_TEST_EQ(x, 20.0);
        x = b + c + d + e + f + g;
        BOOST_TEST_EQ(x, 27.0);
        x = b + c + d + e + f + g + h;
        BOOST_TEST_EQ(x, 35.0);
        x = 10 + b + c + d + e + f + g + h;
        BOOST_TEST_EQ(x, 45.0);
        x = b + 10 + c + d + e + f + g + h;
        BOOST_TEST_EQ(x, 45.0);
        x = b + c + 10 + d + e + f + g + h;
        BOOST_TEST_EQ(x, 45.0);
        x = b + c + d + 10 + e + f + g + h;
        BOOST_TEST_EQ(x, 45.0);
        x = b + c + d + e + 10 + f + g + h;
        BOOST_TEST_EQ(x, 45.0);
        x = b + c + d + e + f + 10 + g + h;
        BOOST_TEST_EQ(x, 45.0);
        x = b + c + d + e + f + g + 10 + h;
        BOOST_TEST_EQ(x, 45.0);
        x = b + c + d + e + f + g + h + 10;
        BOOST_TEST_EQ(x, 45.0);

        BOOST_TEST_EQ(mpfr::copy_count, 28);

        mpfr::copy_count = 0;
        a = b * c;
        BOOST_TEST_EQ(mpfr::copy_count, 0);
        BOOST_TEST_EQ(a, 6.0);

        mpfr::copy_count = 0;
        a = (b * c) + d;
        BOOST_TEST_EQ(a, 10.0);
        BOOST_TEST_EQ(mpfr::copy_count, 0);

        mpfr::copy_count = 0;
        a = ((b * c) + d) + e;
        BOOST_TEST_EQ(a, 15.0);
        BOOST_TEST_EQ(mpfr::copy_count, 0);
        
        mpfr::copy_count = 0;
        a = (e * b) * c + d;
        BOOST_TEST_EQ(a, 34.0);
        BOOST_TEST_EQ(mpfr::copy_count, 0);


        //BOOST_TEST_EQ(mpfr::copy_count, 27);

        mpfr::copy_count = 0;
        a = (b * c) + d;
        BOOST_TEST_EQ(a, 10.0);
        BOOST_TEST_EQ(mpfr::copy_count, 0);

        bool bb = a <= b;

        mpfr::copy_count = 0;
        a = exp(b);
        BOOST_TEST_EQ(mpfr::copy_count, 0);
        {
            mpfr tmp(boost::proto::value(b));
            mpfr_exp(tmp.data, boost::proto::value(b).data, MPFR_RNDN);
            BOOST_TEST_EQ(boost::proto::value(a), tmp);
        }
    }

    return boost::report_errors();
}
