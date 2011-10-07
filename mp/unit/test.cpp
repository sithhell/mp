
#define NT2_UNIT_MODULE "nt2 mpfr toolbox - sandbox test"

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/toolbox/mp/dispatch.hpp>
#include <nt2/toolbox/mp/backend/mpfr/mpfr.hpp>
#include <nt2/toolbox/mp/backend/mpfr/tag.hpp>
#include <nt2/toolbox/mp/backend/mpfr/hierarchy.hpp>
#include <nt2/toolbox/mp/float.hpp>

#include <boost/dispatch/dsl/compute.hpp>
#include <boost/dispatch/dsl/call.hpp>
#include <boost/simd/sdk/simd/pack/call.hpp>

#include <nt2/toolbox/operator/functions/plus.hpp>
#include <nt2/toolbox/operator/functions/multiplies.hpp>

#include <iostream>


namespace nt2 { namespace mp
{
    namespace ext
    {
        template <typename Backend>
        struct compute_impl<boost::simd::tag::plus_, Backend>
        {
            struct call
            {
                nt2::mp::backend::mpfr &
                operator()(nt2::mp::backend::mpfr const & a0, nt2::mp::backend::mpfr const & a1, nt2::mp::backend::mpfr& state)
                {
                    mpfr_add(state.data, a0.data, a1.data, MPFR_RNDN);
                    
                    return state;
                }
                
                template <typename T>
                nt2::mp::backend::mpfr &
                operator()(nt2::mp::backend::mpfr const & a0, T const & a1, nt2::mp::backend::mpfr& state)
                {
                    nt2::mp::backend::mpfr tmp(a1);
                    mpfr_add(state.data, a0.data, tmp.data, MPFR_RNDN);
                    
                    return state;
                }
            };
        };

        /*
        template <typename Backend>
        struct compute_impl<boost::simd::tag::multiplies_, Backend>
        {
            struct call
            {
                nt2::mp::backend::mpfr &
                operator()(nt2::mp::backend::mpfr const & a0, nt2::mp::backend::mpfr const & a1, nt2::mp::backend::mpfr& state)
                {
                    mpfr_add(state.data, a0.data, a1.data, MPFR_RNDN);
                    
                    return state;
                }
                
                template <typename T>
                nt2::mp::backend::mpfr &
                operator()(nt2::mp::backend::mpfr const & a0, T const & a1, nt2::mp::backend::mpfr& state)
                {
                    nt2::mp::backend::mpfr tmp(a1);
                    mpfr_add(state.data, a0.data, tmp.data, MPFR_RNDN);
                    
                    return state;
                }
            };
        };
        */
    }

#define H(A0)\
            nt2::mp::meta::mp_< \
                boost::dispatch::meta::floating_< \
                    A0 \
                > \
              , nt2::mp::backend::tag::mpfr_ \
            >\
    /**/

    BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(
        (nt2)(mp)
      , Tag
      , boost::dispatch::tag::formal_
      , (Tag)(A0)(A1)
      , ((H(A0)))
        ((H(A1)))
      /*, ((boost::dispatch::meta::scalar_<
            nt2::mp::meta::mp_<
                boost::dispatch::meta::floating_<A0>
              , Backend
            >
        >))
        ((boost::dispatch::meta::scalar_<
            nt2::mp::meta::mp_<
                boost::dispatch::meta::floating_<A1>
              , Backend
            >
        >))
        */
    )
    {
        typedef A0 result_type;

        result_type operator()(A0 const & a0, A1 const & a1) const
        {
            std::cout << "hooray!\n";
            return a0;
        }
    };

    BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(
        (nt2)(mp)
      , nt2::tag::plus_
      , boost::dispatch::tag::formal_
      , (A0)(A1)(A2)
      , ((H(A0)))
        ((H(A1)))
        ((H(A2)))
      /*, ((boost::dispatch::meta::scalar_<
            nt2::mp::meta::mp_<
                boost::dispatch::meta::floating_<A0>
              , Backend
            >
        >))
        ((boost::dispatch::meta::scalar_<
            nt2::mp::meta::mp_<
                boost::dispatch::meta::floating_<A1>
              , Backend
            >
        >))
        */
    )
    {
        typedef A2 result_type;

        result_type operator()(A0 const & a0, A1 const & a1, A2 & a2) const
        {
            std::cout << "hooray!\n";
            return a2;
        }
    };

    BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(
        (nt2)(mp)
      , boost::simd::tag::terminal_
      , boost::dispatch::tag::formal_
      , (A0)(A1)
      , ((boost::dispatch::meta::expr_<boost::dispatch::meta::unspecified_<A0>, nt2::mp::domain, boost::simd::tag::terminal_>))
        ((H(A1)))//((nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A1>, Backend>))
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
      , (A0)(Tag)(A1)
      , ((boost::dispatch::meta::expr_<boost::dispatch::meta::unspecified_<A0>, nt2::mp::domain, Tag>))
        ((H(A1)))//((nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A1>, Backend>))
    )
    {
        typedef A1 result_type;

        result_type operator()(A0 const & a0, A1 & a1) const
        {
            return
                boost::dispatch::meta::compile<
                    boost::dispatch::meta::compute<boost::mpl::_1, boost::dispatch::tag::formal_>
                >()(a0, a1);
        }
    };
}}

using namespace boost::dispatch::meta;

template <typename T>
void f(scalar_<single_<T> >, T)
{}

template <typename T>
void f(scalar_<T>, T)
{}

template <typename T>
void f(T t)
{
    f(typename hierarchy_of<T>::type(), t);
}

#define M0(z,n,t) ::parent
#define UP(T,N) T BOOST_PP_REPEAT(N,M0,~)

NT2_TEST_CASE(hierachy_of_backend_mpfr)
{
  using boost::is_same;
  using namespace boost::dispatch::meta;
  using nt2::mp::meta::mp_;
  using nt2::mp::float_;
  using nt2::mp::backend::mpfr;
  using nt2::mp::backend::tag::mpfr_;

  typedef hierarchy_of<mpfr>::type base;
  
  NT2_TEST( (is_same<mp_<floating_<mpfr>, mpfr_>, base>::value) );
  NT2_TEST( (is_same<scalar_<floating_<mpfr> >, UP(base, 1)>::value) );
  NT2_TEST( (is_same<scalar_<signed_<mpfr>      > , UP(base,2) >::value) );
  NT2_TEST( (is_same<scalar_<arithmetic_<mpfr>  > , UP(base,3) >::value) );
  NT2_TEST( (is_same<scalar_<fundamental_<mpfr> > , UP(base,4) >::value) );
  NT2_TEST( (is_same<scalar_<unspecified_<mpfr> > , UP(base,5) >::value) );

  NT2_TEST( (is_same<generic_<floating_<mpfr>        > , UP(base,6) >::value) );
  NT2_TEST( (is_same<generic_<signed_<mpfr>      > , UP(base,7) >::value) );
  NT2_TEST( (is_same<generic_<arithmetic_<mpfr>  > , UP(base,8) >::value) );
  NT2_TEST( (is_same<generic_<fundamental_<mpfr> > , UP(base,9) >::value) );
  NT2_TEST( (is_same<generic_<unspecified_<mpfr> > , UP(base,10) >::value) );
  NT2_TEST( (is_same<unspecified_<mpfr>            , UP(base,11) >::value) );

  std::cout << typeid(typename hierarchy_of<float_<mpfr> >::type).name() << "\n";
  std::cout << typeid(base).name() << "\n";

  NT2_TEST((
    is_same<
        typename hierarchy_of<float_<mpfr> >::type
      , expr_<
            base
          , nt2::mp::domain
          , boost::proto::tag::plus
        >
    >::value
  ));

  float_<mpfr> x, y;
        
  BOOST_DISPATCH_DECLTYPE(x+y, type_t_);
  typedef typename strip<type_t_>::type type_t;
  typedef typename boost::proto::domain_of<type_t>::type domain_t;
  typedef typename semantic_of<type_t>::type semantic_t;
  
  std::cout << typeid(semantic_t).name() << "\n";

  NT2_TEST(( is_same< typename hierarchy_of<type_t>::type
                    , expr_< typename hierarchy_of<semantic_t, type_t>::type
                           , domain_t
                           , boost::proto::tag::plus
                           >
                    >::value
          ));
}

NT2_TEST_CASE (test_)
{
    std::cout << "hello world !!\n";

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
        std::cout << typeid(boost::dispatch::meta::hierarchy_of<float>::type).name() << "\n";

        f(1.0f);
        //f(hierarchy_of<float>::type(), 1.0f);

        mpfr f1(90.0);
        mpfr f2(90.0);

        //f(f2);

        mpfr f3;
        boost::dispatch::functor<boost::proto::tag::plus>()(f1, f2);
        //boost::dispatch::functor<boost::simd::tag::plus_>()(f1, f2);
        //f3 = boost::dispatch::functor<boost::simd::tag::plus_>()(f1, f2);
    }

    using nt2::mp::float_;

    {
        float_<mpfr> f1 = {mpfr(9.0)};
        float_<mpfr> f2 = {mpfr(9.0)};
        float_<mpfr> f3;

        f1 = f2 + f3;

        /*
        f3 = f1 + f2 + f2 + f2 + f1;

        std::cout << mpfr_get_d(boost::proto::value(f3).data, MPFR_RNDN) << "\n";

        f3 = f1 + 5.0f;
        std::cout << mpfr_get_d(boost::proto::value(f3).data, MPFR_RNDN) << "\n";

        f3 = f1 + 5.0;
        std::cout << mpfr_get_d(boost::proto::value(f3).data, MPFR_RNDN) << "\n";

        f3 = f1 + 5ul;
        std::cout << mpfr_get_d(boost::proto::value(f3).data, MPFR_RNDN) << "\n";

        f1 = f2 + f3;

        std::cout << typeid(f2 * f3).name() << "\n";
        */
        //f1 = f2 * f3;
    }

    {
        float_<mpfr> f1, f2;

        nt2::plus(f1, f2);
    }
}
