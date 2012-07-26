//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef MP_EXP_HPP
#define MP_EXP_HPP

#include <mp/domain.hpp>

#include <boost/proto/make_expr.hpp>

namespace mp
{
    namespace tag
    {
        struct exp {};
    }

    template <typename T>
    typename boost::proto::result_of::make_expr<tag::exp, boost::proto::deduce_domain, T &>::type const
    exp(T & t)
    {
        return boost::proto::detail::make_expr_<tag::exp, boost::proto::deduce_domain, T &>()(t);
    }
}

#endif
