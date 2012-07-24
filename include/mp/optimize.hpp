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

    template <typename Backend>
    struct optimizer;

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
}

#endif
