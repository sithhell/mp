//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef MP_OPTIMIZE_HPP
#define MP_OPTIMIZE_HPP

#include <mp/grammar_fwd.hpp>

#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/tags.hpp>
#include <boost/proto/traits.hpp>

#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>

namespace mp {

    namespace detail
    {
        template <typename Backend, typename Expr>
        struct has_optimize
        {
            typedef char (&yes)[1];
            typedef char (&no)[2];

            template <typename B>
            static yes test(typename B::template optimize<Expr>::is_optimize *);

            template <typename B>
            static no test(...);

            static const int value = (sizeof(test<Backend>(0)) == sizeof(yes));
            typedef boost::mpl::bool_<value> type;
        };
    }

    template <typename Grammar, typename F, typename A0 = void, typename A1 = void, typename A2 = void, typename Dummy = void>
    struct optimizer;

    template <typename Grammar, typename F, typename A0, typename A1, typename A2>
    struct optimizer<Grammar, F, A0, A1, A2>
        : boost::proto::when<
            Grammar
          , boost::proto::call<
                F(
                    boost::proto::_data
                  , boost::proto::lazy<
                        boost::proto::_state(
                            A0
                          , int()
                          , boost::proto::_data
                        )
                    >
                  , boost::proto::lazy<
                        boost::proto::_state(
                            A1
                          , int()
                          , boost::proto::_data
                        )
                    >
                  , boost::proto::lazy<
                        boost::proto::_state(
                            A2
                          , int()
                          , boost::proto::_data
                        )
                    >
                )
            >
        >
    {
        typedef void is_optimize;
    };
}

#endif
