
#define NT2_UNIT_MODULE "nt2 mpfr toolbox - sandbox test"

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/toolbox/mp/backend/mpfr/mpfr.hpp>
#include <nt2/toolbox/mp/float.hpp>

//#include <boost/simd/toolbox/operator/functions/plus.hpp>
#include <boost/dispatch/dsl/compute.hpp>
#include <boost/dispatch/dsl/call.hpp>
#include <boost/simd/sdk/simd/pack/call.hpp>>

//#include <nt2/toolbox/mpfloat/mpfloat.hpp>
//#include <nt2/toolbox/operator/functions/mp/plus.hpp>
#include <nt2/toolbox/operator/functions/plus.hpp>

#include <iostream>

namespace boost { namespace dispatch { namespace meta
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
}}}

namespace nt2 { namespace mp
{
    template <typename Sig, typename Site, typename Enable = void>
    struct implement;

    BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(
        (nt2)(mp)
      , boost::simd::tag::plus_
      , boost::dispatch::tag::formal_
      , (A0)(A1)(A2)(Backend)
      , ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A0>, Backend> >))
        ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A1>, Backend> >))
        ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A2>, Backend> >))
    )
    {
        typedef nt2::mp::backend::mpfr result_type;

        result_type operator()(A0 const & a0, A1 const & a1, A2 & a2) const
        {
            mpfr_add(a2.data, a0.data, a1.data, MPFR_RNDN);

            return a2;
        }
    };

    BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(
        (nt2)(mp)
      , boost::simd::tag::plus_
      , boost::dispatch::tag::formal_
      , (A0)(A1)(A2)(Backend)
      , ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A0>, Backend> >))
        ((boost::dispatch::meta::scalar_<boost::dispatch::meta::arithmetic_<A1> >))
        ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A2>, Backend> >))
    )
    {
        typedef nt2::mp::backend::mpfr result_type;

        result_type operator()(A0 const & a0, A1 const & a1, A2 & a2) const
        {
            nt2::mp::backend::mpfr tmp(a1);
            mpfr_add(a2.data, a0.data, tmp.data, MPFR_RNDN);

            return a2;
        }
    };

    BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(
        (nt2)(mp)
      , boost::simd::tag::terminal_
      , boost::dispatch::tag::formal_
      , (A0)(A1)(Backend)
      , ((boost::dispatch::meta::expr_<boost::dispatch::meta::unspecified_<A0>, nt2::mp::domain, boost::simd::tag::terminal_>))
        ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A1>, Backend> >))
    )
    {
        typedef typename boost::proto::result_of::value<A0>::type result_type;

        result_type operator()(A0 const & a0, A1 & a1) const
        {
            return boost::proto::value(a0);
        }
    };

    BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(
        (nt2)(mp)
      , boost::simd::tag::evaluate_
      , boost::dispatch::tag::formal_
      , (A0)(Tag)(A1)(Backend)
      , ((boost::dispatch::meta::expr_<boost::dispatch::meta::unspecified_<A0>, nt2::mp::domain, Tag>))
        ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A1>, Backend> >))
    )
    {
        typedef typename boost::dispatch::meta::semantic_of<A0>::type result_type;

        result_type operator()(A0 const & a0, A1 & a1) const
        {
            return
                boost::dispatch::meta::compile<
                    boost::dispatch::meta::compute<boost::mpl::_1, boost::dispatch::tag::formal_, boost::proto::_state>
                >()(a0, a1);
        }
    };
}}


NT2_TEST_CASE (test_)
{
    std::cout << "hello world!\n";

    using nt2::mp::backend::mpfr;

    {
        mpfr f;
    }

    {
        unsigned long int value = 42ul;
        mpfr f(value);
        std::cout << mpfr_get_ui(f.data, MPFR_RNDN) << "\n";
    }

    {
        long int value = 42;
        mpfr f(value);
        std::cout << mpfr_get_si(f.data, MPFR_RNDN) << "\n";
    }

    {
        float value = 42.0f;
        try {
        mpfr f(value);
        std::cout << mpfr_get_flt(f.data, MPFR_RNDN) << "\n";
        }
        catch(...) {}
    }

    {
        double value = 42.0;
        mpfr f(value);

        std::cout << mpfr_get_d(f.data, MPFR_RNDN) << "\n";
    }

    {
        long double value = 42.0l;
        mpfr f(value);
        std::cout << mpfr_get_ld(f.data, MPFR_RNDN) << "\n";
    }

    {
        std::string value = "42.0";
        mpfr f(value);
        std::cout << mpfr_get_flt(f.data, MPFR_RNDN) << "\n";
    }

    {
        std::cout << typeid(boost::dispatch::meta::hierarchy_of<mpfr>::type).name() << "\n";
        std::cout << typeid(boost::dispatch::meta::hierarchy_of<int>::type).name() << "\n";

        mpfr f1(90.0);
        mpfr f2(90.0);

        mpfr f3;
        //boost::dispatch::functor<boost::simd::tag::plus_>()(f1, f2, f3);
    }

    using nt2::mp::float_;

    {
        float_<mpfr> f1 = {mpfr(9.0)};
        float_<mpfr> f2 = {mpfr(9.0)};
        float_<mpfr> f3;
        f3 = f1 + f2 + f2 + f2 + f1;
        std::cout << mpfr_get_d(boost::proto::value(f3).data, MPFR_RNDN) << "\n";
        f3 = f1 + 5.0f;
        std::cout << mpfr_get_d(boost::proto::value(f3).data, MPFR_RNDN) << "\n";
        f3 = f1 + 5.0;
        std::cout << mpfr_get_d(boost::proto::value(f3).data, MPFR_RNDN) << "\n";
        f3 = f1 + 5ul;
        std::cout << mpfr_get_d(boost::proto::value(f3).data, MPFR_RNDN) << "\n";
    }

    {
        float_<mpfr> f1, f2;

        nt2::plus(f1, f2);
    }
}
