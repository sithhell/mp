//==============================================================================
//         Copyright 2012 & onward Thomas Heller
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MP_EXPR_HPP
#define NT2_SDK_MP_EXPR_HPP

#include <nt2/sdk/mp/domain.hpp>
#include <nt2/sdk/mp/expr_fwd.hpp>
#include <nt2/sdk/mp/meta/semantic_of.hpp>

#include <boost/proto/extends.hpp>

namespace nt2 { namespace mp
{
    template <typename Expr, typename Backend>
    struct expr
    {
        typedef Backend backend_type;
        BOOST_PROTO_BASIC_EXTENDS(
            Expr
          , expr
          , typename domain<backend_type>
        )
    };
}}

#endif
