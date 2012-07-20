
//==============================================================================
//         Copyright 2012 & onward Thomas Heller
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MP_META_SEMANTIC_OF_HPP
#define NT2_SDK_MP_META_SEMANTIC_OF_HPP

#include <nt2/sdk/mp/expr_fwd.hpp>
#include <nt2/sdk/mp/float_fwd.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>

namespace boost { namespace dispatch {
    namespace meta
    {
        template <typename Expression, typename Backend>
        struct semantic_of<nt2::mp::expr<Expression, Backend> >
        {
            typedef typename nt2::mp::expr<Expression, Backend>::backend_type type;
        };

        template <typename Backend>
        struct semantic_of<nt2::mp::float_<Backend> >
        {
            typedef Backend type;
        };
    }
}}

#endif
