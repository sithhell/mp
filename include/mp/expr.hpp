//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef MP_EXPR_HPP
#define MP_EXPR_HPP

#include <mp/domain.hpp>
#include <mp/expr_fwd.hpp>

#include <boost/proto/extends.hpp>

namespace mp
{
    template <typename Expr, typename Backend>
    struct expr
        : boost::proto::extends<
            Expr, expr<Expr, Backend>, domain<Backend>
        >
    {
        typedef 
            boost::proto::extends<
                Expr, expr<Expr, Backend>, domain<Backend>
            >
            base_type;

        expr(Expr const & expr) : base_type(expr) {}

    };
}

#endif
