
#ifndef NT2_TOOLBOX_MP_FLOAT_HPP
#define NT2_TOOLBOX_MP_FLOAT_HPP

#include <boost/proto/proto.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>
#include <nt2/include/functions/evaluate.hpp>
#include <nt2/include/functions/schedule.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/toolbox/mp/backend/mpfr/mpfr.hpp>

namespace nt2 { namespace mp
{
    struct grammar
        : boost::proto::or_<
          /*
            boost::proto::plus<grammar, grammar>
          , boost::proto::multiplies<grammar, grammar>
          , boost::proto::assign<boost::proto::terminal<, grammar>
          , boost::proto::terminal<boost::proto::_>
          */
          boost::proto::_
        >
    {};

    template <typename Expr>
    struct expr;
 
    struct domain
        : boost::proto::domain<boost::proto::pod_generator<expr>, grammar>
    {};

    template <typename Expr>
    struct expr
    {
        BOOST_PROTO_BASIC_EXTENDS(
            Expr
          , expr
          , domain
        )
    };

    ////////////////////////////////////////////////////////////////////////////
    // float_:
    //
    // The basic proto terminal type to be used in the nt2 expression template
    // system.
    //
    ////////////////////////////////////////////////////////////////////////////
    template <typename Backend, typename Dummy = boost::proto::is_proto_expr>
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
            nt2::evaluate(
                nt2::assign(
                    *this
                  , expr
                )
            );
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

namespace boost { namespace dispatch {
    namespace meta
    {
        template <typename Expression>
        struct semantic_of<nt2::mp::expr<Expression> >
        {
            typedef nt2::mp::backend::mpfr type;
        };    
        
        template <typename Backend>
        struct semantic_of<nt2::mp::float_<Backend> >
        {
            typedef Backend type;
        };

        template <>
        struct terminal_of<nt2::mp::backend::mpfr>
        {
            typedef nt2::mp::float_<nt2::mp::backend::mpfr> type;
        };
    }
}}

#endif
