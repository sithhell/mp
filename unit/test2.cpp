
#define NT2_UNIT_MODULE "nt2 mpfr toolbox - sandbox test"

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/sdk/mp/float.hpp>
#include <nt2/sdk/mp/expr.hpp>
#include <nt2/sdk/mp/mpfr.hpp>
#include <nt2/sdk/mp/meta/hierarchy.hpp>
#include <nt2/sdk/mp/mpfr/meta/hierarchy.hpp>
#include <nt2/sdk/mp/functor/hierarchy.hpp>

#include <nt2/dsl/functions/schedule.hpp>
#include <nt2/include/functions/plus.hpp>

namespace boost { namespace dispatch {
}}

namespace nt2 { namespace mp {

    /*
    BOOST_DISPATCH_IMPLEMENT(
        (nt2)(mp)
      , nt2::tag::run_
      , boost::dispatch::tag::cpu_
      , (A0)
      , ((boost::dispatch::meta::expr_<
            boost::dispatch::meta::scalar_<
                nt2::mp::meta::mp_<
                    A0
                  , nt2::mp::tag::mpfr_
                >
            >
          , boost::simd::tag::assign_
          , boost::mpl::long_<2l>
        >))
    )
    {
        typedef void result_type;

        result_type operator()(A0 & a0)
        {
            std::cout << "run assign!\n";
        }
    };
    
    NT2_MP_DISPATCH_IMPLEMENT(boost::simd::tag::schedule_, nt2::mp::tag::mpfr_, (A0))
    {
        typedef A0 const & result_type;

        result_type operator()(A0 const & a0) const
        {
            std::cout << "run\n";
            std::cout << typeid(A0).name() << "\n";
            std::cout << "\n";
            return a0;
        }
    };
    */

    NT2_MP_DISPATCH_IMPLEMENT(nt2::tag::assign_, nt2::mp::tag::mpfr_, (A0)(A1))
    {
        typedef A0 & result_type;

        result_type operator()(A0 & a0, A1 const & a1) const
        {
            std::cout << "assign\n";
            std::cout << typeid(A0).name() << "\n";
            std::cout << typeid(A1).name() << "\n";
            std::cout << "\n";
            return a0;
        }
    };
    
    NT2_MP_DISPATCH_IMPLEMENT(nt2::tag::plus_, nt2::mp::tag::mpfr_, (A0)(A1))
    {
        typedef A0 & result_type;

        result_type operator()(A0 & a0, A1 const & a1) const
        {
            std::cout << "plus\n";
            std::cout << typeid(A0).name() << "\n";
            std::cout << typeid(A1).name() << "\n";
            std::cout << "\n";
            return a0;
        }
    };
}}

template <typename A>
void foo(
    A
  , boost::dispatch::meta::expr_<
        boost::dispatch::meta::scalar_<
            typename boost::dispatch::meta::property_of<A>::type
        >
      , boost::simd::tag::plus_
      , boost::mpl::long_<2l>
    > const &
)
{}

template <typename A>
void foo(A a)
{
    foo(a, typename boost::dispatch::meta::hierarchy_of<A>::type());
}

NT2_TEST_CASE (plus_)
{
    using nt2::mp::mpfr;
    using nt2::mp::float_;

    /*
    {
        mpfr x,y,z;
        
        boost::dispatch::functor<boost::proto::tag::plus>()(x, y, z);
        nt2::plus(x, y);
    }
    */

    {
        mpfr a;
        float_<mpfr> x, y, z;

        std::cout << typeid(boost::dispatch::meta::hierarchy_of<float_<mpfr> >::type).name() << "\n";
        std::cout << typeid(boost::dispatch::meta::hierarchy_of<BOOST_TYPEOF(x+y)>::type).name() << "\n";
        std::cout << typeid(boost::dispatch::meta::hierarchy_of<mpfr>::type).name() << "\n";

        //foo(x + y);


        x = y + z;
        /*
        x = y + a;
        
        x = y + z + a;

        nt2::evaluate(y + z);
        */
    }
}
