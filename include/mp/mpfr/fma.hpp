//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef MP_MPFR_FMA_HPP
#define MP_MPFR_FMA_HPP

#include <mp/optimize.hpp>
#include <mp/mpfr/mpfr.hpp>

#include <boost/utility/enable_if.hpp>

#include <boost/proto/matches.hpp>
#include <boost/proto/traits.hpp>

namespace mp
{
    namespace detail
    {
        struct fma_grammar_1
            : boost::proto::plus<
                boost::proto::multiplies<
                    boost::proto::_
                  , boost::proto::_
                >
              , boost::proto::_
            >
        {};
        
        struct fma_grammar_2
            : boost::proto::plus<
                boost::proto::_
              , boost::proto::multiplies<
                    boost::proto::_
                  , boost::proto::_
                >
            >
        {};
    }

    namespace tag
    {
        struct fma {};
    };
    
    template <>
    struct mpfr::evaluate<tag::fma>
    {
        typedef mpfr & result_type;
        mpfr & operator()(mpfr &res, mpfr const & op1, mpfr const & op2, mpfr const & op3) const
        {
            mpfr_fma(res.data, op1.data, op2.data, op3.data, MPFR_RNDN);

            return res;
        }
    };

    template <typename Expr>
    struct mpfr::optimize
    <
        Expr
      , typename boost::enable_if<
            boost::proto::matches<Expr, detail::fma_grammar_1>
        >::type
    >
        : optimizer<
            detail::fma_grammar_1
          , mpfr::evaluate<tag::fma>
          , boost::proto::_child_c<0>(boost::proto::_child_c<0>)
          , boost::proto::_child_c<1>(boost::proto::_child_c<0>)
          , boost::proto::_child_c<1>
        >
    {
    };

    template <typename Expr>
    struct mpfr::optimize
    <
        Expr
      , typename boost::enable_if<
            boost::mpl::and_<
                boost::proto::matches<Expr, detail::fma_grammar_2>
              , boost::mpl::not_<
                    boost::proto::matches<Expr, detail::fma_grammar_1>
                >
            >
        >::type
    >
        : optimizer<
            detail::fma_grammar_2
          , mpfr::evaluate<tag::fma>
          , boost::proto::_child_c<0>(boost::proto::_child_c<1>)
          , boost::proto::_child_c<1>(boost::proto::_child_c<1>)
          , boost::proto::_child_c<0>
        >
    {
    };
}

#endif
