
#ifndef NT2_TOOLBOX_MPFLOAT_HPP
#define NT2_TOOLBOX_MPFLOAT_HPP

#include <boost/proto/proto.hpp>
#include <boost/dispatch/dsl/category.hpp>

namespace nt2 {
    
namespace mpfloat
{
    namespace backend
    {
        struct mpfr {};

        template <typename Backend>
        struct data
        {
            typedef mpfr type;
        };
    }

    template <typename Backend>
    struct domain
        : boost::proto::domain<boost::proto::_>
    {
        typedef Backend backend_type;
    };

    namespace tag { struct evaluate_ {}; }

    BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_SELF(tag::evaluate_, evaluate, 2)

    namespace ext
    {
        template <typename Sig, typename Site, typename Dummy = void>
        struct implement;

        //BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION((nt2)(mpfloat)(ext), Tag, Site, Types, Seq)
        BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION_TPL(
            (nt2)(mpfloat)(ext)
          , nt2::mpfloat::tag::evaluate_
          , boost::dispatch::tag::cpu_
          , (typename A0)(typename A1)
          , (boost::dispatch::meta::unspecified_<A0>)
            (boost::dispatch::meta::unspecified_<A1>)
        )
        {
            typedef void result_type;

            template <typename Src, typename Dst>
            inline
            result_type
            operator()(Src & src, Dst const & dst) const
            {
                std::cout << "evaluating!\n";

                boost::dispatch::meta::as_<A0> target;
                boost::dispatch::meta::compile<boost::dispatch::meta::compute<boost::mpl::_1, boost::dispatch::tag::cpu_> > callee;

                callee(dst, target);
                std::cout
                    << typeid(A0).name() << "\n"
                    << typeid(A1).name() << "\n"
                    << typeid(Src).name() << "\n"
                    << typeid(Dst).name() << "\n"
                ;
            }
        };
    }

    ////////////////////////////////////////////////////////////////////////////
    // float_:
    //
    // The basic proto terminal type to be used in the nt2 expression template
    // system.
    //
    // This type can't be a POD, because we need to use RAII to handle dynamic
    // memory
    ////////////////////////////////////////////////////////////////////////////
    template <typename Backend, typename Dummy = boost::proto::is_proto_expr>
    struct float_
    {
        BOOST_PROTO_BASIC_EXTENDS_TPL(
            typename boost::proto::terminal<
                typename backend::data<Backend>::type
            >::type
          , float_<Backend>
          , domain<Backend>
        )

        typedef Backend backend_type;

        typedef
            typename backend::data<Backend>::type
            data_type;

        ////////////////////////////////////////////////////////////////////////
        // Expression Hierarchy typedefs
        ////////////////////////////////////////////////////////////////////////
        typedef
            typename boost::dispatch::details::hierarchy_of_expr<float_>::type
            dispatch_hierarchy_tag;

        typedef
            backend_type
            dispatch_semantic_tag;
        ////////////////////////////////////////////////////////////////////////
        

        ////////////////////////////////////////////////////////////////////////
        // Assignment
        ////////////////////////////////////////////////////////////////////////

        // Copy Assign another float_
        float_ &operator=(float_ const & src)
        {
            boost::proto::value(*this) = boost::proto::value(src);
            return *this;
        }
        
        template <typename Expr>
        void evaluate(Expr const & expr)
        {
            nt2::mpfloat::evaluate(boost::proto::value(*this), expr);
        }

        // Assign a mpfloat expression
        template <typename Expr>
        float_ &operator=(Expr const & expr)
        {
            std::cout << "ok ...\n";
            evaluate(expr);
            return *this;
        }

        #define NT2_TOOLBOX_MPFLOAT_MAKE_ASSIGN_OP(OP)                         \
        template<typename Expr>                                                \
        float_ &operator BOOST_PP_CAT(OP,=)(Expr const& expr )                 \
        {                                                                      \
            evaluate(*this OP expr);                                           \
            return *this;                                                      \
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
