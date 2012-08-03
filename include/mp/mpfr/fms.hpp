//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef MP_MPFR_FMS_HPP
#define MP_MPFR_FMS_HPP

#include <mp/optimize.hpp>
#include <mp/mpfr/mpfr.hpp>

#include <boost/utility/enable_if.hpp>

#include <boost/proto/matches.hpp>
#include <boost/proto/traits.hpp>

namespace mp
{
    namespace detail
    {
        struct fms_grammar
            : boost::proto::minus<
                boost::proto::multiplies<
                    boost::proto::_
                  , boost::proto::_
                >
              , boost::proto::_
            >
        {};
    }

    namespace tag
    {
        struct fms {};
    };
    
    template <>
    struct mpfr::evaluate<tag::fms>
    {
        typedef mpfr & result_type;
        mpfr & operator()(mpfr &res, mpfr const & op1, mpfr const & op2, mpfr const & op3) const
        {
            mpfr_fms(res.data, op1.data, op2.data, op3.data, MPFR_RNDN);

            return res;
        }
    };

    template <typename Expr>
    struct mpfr::optimize
    <
        Expr
      , typename boost::enable_if<
            boost::proto::matches<Expr, detail::fms_grammar>
        >::type
    >
        : optimizer<
            detail::fms_grammar
          , mpfr::evaluate<tag::fms>
          , boost::proto::_child_c<0>(boost::proto::_child_c<0>)
          , boost::proto::_child_c<1>(boost::proto::_child_c<0>)
          , boost::proto::_child_c<1>
        >
    {
    };
}

#endif
