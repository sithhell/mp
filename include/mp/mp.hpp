//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef MP_MP_HPP
#define MP_MP_HPP

#include <mp/domain.hpp>
#include <mp/expr.hpp>
#include <mp/mp_fwd.hpp>
#include <mp/grammar.hpp>
#include <mp/optimize.hpp>

#include <boost/proto/proto.hpp>

#include <iostream>

namespace mp
{
    ////////////////////////////////////////////////////////////////////////////
    // mp_:
    //
    // The basic proto terminal type to be used in the nt2 expression template
    // system.
    //
    ////////////////////////////////////////////////////////////////////////////
    template <typename Backend, typename>
    struct mp_
        : expr<typename boost::proto::terminal<Backend>::type, Backend>
    {
        typedef typename boost::proto::terminal<Backend>::type terminal_type;

        typedef 
            expr<terminal_type, Backend>
            base_type;

        typedef Backend backend_type;
        
        mp_()
            : base_type(terminal_type())
        {}

        mp_(mp_ const & expr)
            : base_type(expr)
        {}

        explicit mp_(Backend const & backend)
            : base_type(terminal_type(backend))
        {}

        template <typename T>
        explicit mp_(T const & t)
            : base_type(
                boost::proto::make_expr<boost::proto::tag::terminal>(
                    Backend(t)
                )
            )
        {}

        ////////////////////////////////////////////////////////////////////////
        // Assignment
        ////////////////////////////////////////////////////////////////////////

        // Copy Assign another mp_
        mp_ &operator=(mp_ const & src)
        {
            boost::proto::value(*this) = boost::proto::value(src);
            return *this;
        }
        
        // Copy Assign another Backend value
        mp_ &operator=(Backend const & src)
        {
            boost::proto::value(*this) = src;
            return *this;
        }
        
        // Assign a expression and evaluate it.
        template <typename E>
        mp_ &operator=(E const & expr)
        {
            grammar<Backend>()(expr, 0, boost::proto::value(*this));
            return *this;
        }

        #define MP_MAKE_ASSIGN_OP(OP)                                           \
        template<typename Expr>                                                 \
        mp_ &operator BOOST_PP_CAT(OP,=)(Expr const& expr )                     \
        {                                                                       \
            return *this = *this OP expr;                                       \
        }                                                                       \
        /**/
        
        MP_MAKE_ASSIGN_OP(+)
        MP_MAKE_ASSIGN_OP(-)
        MP_MAKE_ASSIGN_OP(*)
        MP_MAKE_ASSIGN_OP(/)
        MP_MAKE_ASSIGN_OP(%)
        MP_MAKE_ASSIGN_OP(^)
        MP_MAKE_ASSIGN_OP(&)
        MP_MAKE_ASSIGN_OP(|)
        MP_MAKE_ASSIGN_OP(>>)
        MP_MAKE_ASSIGN_OP(<<)

        #undef MP_MAKE_ASSIGN_OP
        
        ////////////////////////////////////////////////////////////////////////
    };
    
    template <typename Backend>
    bool operator==(mp_<Backend> const & lhs, mp_<Backend> const & rhs)
    {
        return boost::proto::value(lhs) == boost::proto::value(rhs);
    }
    
    template <typename Backend>
    bool operator==(mp_<Backend> const & lhs, Backend const & rhs)
    {
        return boost::proto::value(lhs) == rhs;
    }
    
    template <typename Backend>
    bool operator==(Backend const & lhs, mp_<Backend> const & rhs)
    {
        return lhs == boost::proto::value(rhs);
    }
    
    template <typename Backend, typename T>
    bool operator==(mp_<Backend> const & lhs, T const & rhs)
    {
        return boost::proto::value(lhs) == Backend(rhs);
    }
    
    template <typename Backend, typename T>
    bool operator==(T const & lhs, mp_<Backend> const & rhs)
    {
        return Backend(lhs) == boost::proto::value(rhs);
    }

    template <typename Backend>
    std::ostream & operator<<(std::ostream & os, mp_<Backend> const & m)
    {
        os << boost::proto::value(m);

        return os;
    }
}

#endif
