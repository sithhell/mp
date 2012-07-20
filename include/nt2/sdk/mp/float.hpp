//==============================================================================
//         Copyright 2012 & onward Thomas Heller
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MP_FLOAT_HPP
#define NT2_SDK_MP_FLOAT_HPP

#include <nt2/sdk/mp/float_fwd.hpp>
#include <nt2/sdk/mp/expr.hpp>
#include <nt2/sdk/mp/domain.hpp>
#include <nt2/sdk/mp/grammar.hpp>

#include <nt2/include/functions/evaluate.hpp>

#include <boost/dispatch/meta/terminal_of.hpp>
#include <boost/proto/proto.hpp>

namespace nt2 { namespace mp
{
    ////////////////////////////////////////////////////////////////////////////
    // float_:
    //
    // The basic proto terminal type to be used in the nt2 expression template
    // system.
    //
    ////////////////////////////////////////////////////////////////////////////
    template <typename Backend, typename>
    struct float_
    {
        BOOST_PROTO_BASIC_EXTENDS(
            typename boost::proto::terminal<
                Backend
            >::type
          , float_<Backend>
          , domain
        )

        typedef Backend backend_type;
        
        /*
        float_(float_ const & expr)
        {
        }

        template <typename Expr>
        float_(Expr const & expr)
        {
        }

        float_(Backend const & expr)
        {
        }
        */

        ////////////////////////////////////////////////////////////////////////
        // Assignment
        ////////////////////////////////////////////////////////////////////////

        // Copy Assign another float_
        float_ &operator=(float_ const & src)
        {
            boost::proto::value(*this) = boost::proto::value(src);
            return *this;
        }
        
        // Copy Assign another Backend value
        float_ &operator=(Backend const & src)
        {
            boost::proto::value(*this) = src;
            return *this;
        }
        
        // Assign a mpfloat expression
        template <typename Expr>
        float_ &operator=(Expr const & expr)
        {
            /*
            nt2::evaluate(
                nt2::assign(
                    *this
                  , expr
                )
            );
            */
            return *this;
        }

        #define NT2_TOOLBOX_MPFLOAT_MAKE_ASSIGN_OP(OP)                         \
        template<typename Expr>                                                \
        float_ &operator BOOST_PP_CAT(OP,=)(Expr const& expr )                 \
        {                                                                      \
            return *this = *this OP expr;                                      \
        }                                                                      \
        /**/
        
        NT2_TOOLBOX_MPFLOAT_MAKE_ASSIGN_OP(+)
        NT2_TOOLBOX_MPFLOAT_MAKE_ASSIGN_OP(-)
        NT2_TOOLBOX_MPFLOAT_MAKE_ASSIGN_OP(*)
        NT2_TOOLBOX_MPFLOAT_MAKE_ASSIGN_OP(/)
        NT2_TOOLBOX_MPFLOAT_MAKE_ASSIGN_OP(%)
        NT2_TOOLBOX_MPFLOAT_MAKE_ASSIGN_OP(^)
        NT2_TOOLBOX_MPFLOAT_MAKE_ASSIGN_OP(&)
        NT2_TOOLBOX_MPFLOAT_MAKE_ASSIGN_OP(|)
        NT2_TOOLBOX_MPFLOAT_MAKE_ASSIGN_OP(>>)
        NT2_TOOLBOX_MPFLOAT_MAKE_ASSIGN_OP(<<)

        #undef NT2_TOOLBOX_MPFLOAT_MAKE_ASSIGN_OP
        
        ////////////////////////////////////////////////////////////////////////
        
    };

}}

#endif
