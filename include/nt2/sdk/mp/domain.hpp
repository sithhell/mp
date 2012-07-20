//==============================================================================
//         Copyright 2012 & onward Thomas Heller
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MP_DOMAIN_HPP
#define NT2_SDK_MP_DOMAIN_HPP

#include <nt2/sdk/mp/expr_fwd.hpp>
#include <nt2/sdk/mp/domain_fwd.hpp>
#include <nt2/sdk/mp/grammar_fwd.hpp>

#include <boost/proto/domain.hpp>

namespace nt2 { namespace mp
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
                Extends<Expr, Backend> that = {e};
                return that;
            }
        };
    }

    template <typename Backend>
    struct domain
        : boost::proto::domain<detail::expr_generator<expr, Backend>, grammar<Backend> >
    {};
}}

#endif
