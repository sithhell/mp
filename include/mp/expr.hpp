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
#include <mp/optimize.hpp>

#include <boost/typeof/typeof.hpp>
#include <boost/proto/extends.hpp>

#include <boost/move/move.hpp>

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
        
        expr(BOOST_RV_REF(Expr) expr) : base_type(boost::move(expr)) {}

        operator Backend() const
        {
            Backend b;
            grammar<Backend>()(*this, 0, b);
            return b;
        }
            
        BOOST_COPYABLE_AND_MOVABLE(expr);
    };
}

#endif
