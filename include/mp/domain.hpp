//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef MP_DOMAIN_HPP
#define MP_DOMAIN_HPP

#include <mp/expr_fwd.hpp>
#include <mp/domain_fwd.hpp>
#include <mp/grammar_fwd.hpp>

#include <boost/proto/domain.hpp>

namespace mp
{
    namespace detail
    {
        template <template <typename, typename> class Extends, typename Backend>
        struct expr_generator
        {
            BOOST_PROTO_CALLABLE()
            BOOST_PROTO_USE_BASIC_EXPR()
            
            template<typename Sig>
            struct result;
            
            template<typename This, typename Expr>
            struct result<This(Expr)>
            {
                typedef Extends<Expr, Backend> type;
            };
            
            template<typename This, typename Expr>
            struct result<This(Expr &)>
            {
                typedef Extends<Expr, Backend> type;
            };
            
            template<typename This, typename Expr>
            struct result<This(Expr const &)>
            {
                typedef Extends<Expr, Backend> type;
            };
            
            /// \param expr The expression to wrap
            /// \return <tt>Extends\<Expr\> that = {expr}; return that;</tt>
            template<typename Expr>
            BOOST_FORCEINLINE
            Extends<Expr, Backend> operator ()(Expr const &e) const
            {
                return Extends<Expr, Backend>(e);
            }
        };
    }

    template <typename Backend>
    struct domain
        : boost::proto::domain<detail::expr_generator<expr, Backend>, grammar<Backend> >
    {};
}

#endif
