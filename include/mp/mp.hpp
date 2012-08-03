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
#include <mp/exp.hpp>

#include <boost/proto/proto.hpp>

#include <boost/assert.hpp>

#include <iostream>

namespace mp
{
    namespace detail
    {
        template <typename T>
        struct strip { typedef T type; };
        template <typename T>
        struct strip<T const> { typedef T type; };
        template <typename T>
        struct strip<T const &> { typedef T type; };
        template <typename T>
        struct strip<T &> { typedef T type; };
#ifndef BOOST_HAS_NO_RVALUE_REFERENCES
        template <typename T>
        struct strip<T const &&> { typedef T type; };
        template <typename T>
        struct strip<T &&> { typedef T type; };
#endif
    }

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

        mp_(BOOST_RV_REF(mp_) expr)
            : base_type(boost::move(expr))
        {}

        mp_(Backend const & backend)
            : base_type(terminal_type(backend))
        {}

        mp_(BOOST_RV_REF(Backend) backend)
            : base_type(terminal_type(boost::move(backend)))
        {}

        template <typename T>
        mp_(BOOST_FWD_REF(T) t
          , typename boost::disable_if<
                typename boost::is_same<
                    typename detail::strip<T>::type
                  , mp_<Backend>
                >::type
            >::type * = 0
        )
            : base_type(
                boost::proto::make_expr<boost::proto::tag::terminal>(
                    Backend(boost::forward<T>(t))
                )
            )
        {}

        template <typename Expr>
        mp_(expr<Expr, Backend> const & xpr)
            : base_type(
                terminal_type()
            )
        {
            grammar<Backend>()(xpr, 0, boost::proto::value(*this));
        }

        ////////////////////////////////////////////////////////////////////////
        // Assignment
        ////////////////////////////////////////////////////////////////////////

        // Copy Assign another mp_
        mp_ &operator=(mp_ const & src)
        {
            boost::proto::value(*this) = boost::proto::value(src);
            return *this;
        }

        mp_ &operator=(BOOST_RV_REF(mp_) src)
        {
            boost::proto::value(*this) = boost::move(boost::proto::value(src));
            return *this;
        }
        
        // Copy Assign another Backend value
        mp_ &operator=(Backend const & src)
        {
            boost::proto::value(*this) = src;
            return *this;
        }
        
        mp_ &operator=(BOOST_RV_REF(Backend) src)
        {
            boost::proto::value(*this) = boost::move(src);
            return *this;
        }
        
        // Assign a expression and evaluate it.
        template <typename E>
        typename boost::enable_if<boost::proto::is_expr<E>, mp_ &>::type
        operator=(E const & expr)
        {
            grammar<Backend>()(expr, 0, boost::proto::value(*this));
            return *this;
        }
        
        template <typename E>
        typename boost::disable_if<boost::proto::is_expr<E>, mp_ &>::type
        operator=(BOOST_FWD_REF(E) src)
        {
            boost::proto::value(*this) = Backend(boost::forward<E>(src));
            return *this;
        }

        #define MP_MAKE_ASSIGN_OP(OP)                                           \
        template<typename Expr>                                                 \
        mp_ &operator BOOST_PP_CAT(OP,=)(Expr const& expr )                     \
        {                                                                       \
            grammar<Backend>()(*this OP expr, 0, boost::proto::value(*this));   \
            return *this;                                                       \
        }                                                                       \
        template<typename Expr>                                                 \
        mp_ &operator BOOST_PP_CAT(OP,=)(Expr & expr )                          \
        {                                                                       \
            grammar<Backend>()(*this OP expr, 0, boost::proto::value(*this));   \
            return *this;                                                       \
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
    
        std::string to_string(size_t n = 0, int b = 10/*default_base*/) const
        {
            return boost::proto::value(*this).to_string();
        }

        operator double() const
        {
            return double(boost::proto::value(*this));
        }

        template <typename Archive>
        void serialize(Archive & ar, unsigned)
        {
            BOOST_ASSERT(false);
        }

        private:
            BOOST_COPYABLE_AND_MOVABLE(mp_);
    };
    
#define MP_MP_BOOL_OPERATOR(OP)                                                 \
    template <typename Backend>                                                 \
    bool operator OP(mp_<Backend> const & lhs, mp_<Backend> const & rhs)        \
    {                                                                           \
        return boost::proto::value(lhs) OP boost::proto::value(rhs);            \
    }                                                                           \
                                                                                \
    template <typename Backend>                                                 \
    bool operator OP(mp_<Backend> const & lhs, Backend const & rhs)             \
    {                                                                           \
        return boost::proto::value(lhs) OP rhs;                                 \
    }                                                                           \
                                                                                \
    template <typename Backend>                                                 \
    bool operator OP(Backend const & lhs, mp_<Backend> const & rhs)             \
    {                                                                           \
        return lhs OP boost::proto::value(rhs);                                 \
    }                                                                           \
                                                                                \
    template <typename Backend, typename T>                                     \
    bool operator OP(mp_<Backend> const & lhs, T const & rhs)                   \
    {                                                                           \
        return boost::proto::value(lhs) OP Backend(rhs);                        \
    }                                                                           \
                                                                                \
    template <typename Backend, typename T>                                     \
    bool operator OP(T const & lhs, mp_<Backend> const & rhs)                   \
    {                                                                           \
        return Backend(lhs) OP boost::proto::value(rhs);                        \
    }                                                                           \
    /**/

    MP_MP_BOOL_OPERATOR(==)
    MP_MP_BOOL_OPERATOR(>=)
    MP_MP_BOOL_OPERATOR(<=)
    MP_MP_BOOL_OPERATOR(<)
#undef MP_MP_BOOL_OPERATOR


    template <typename Backend>
    std::ostream & operator<<(std::ostream & os, mp_<Backend> const & m)
    {
        os << boost::proto::value(m);

        return os;
    }
}

#endif
