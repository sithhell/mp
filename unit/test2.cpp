
#define NT2_UNIT_MODULE "nt2 mpfr toolbox - sandbox test"

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

/*
#include <nt2/toolbox/mp/backend/mpfr/mpfr.hpp>
#include <nt2/toolbox/mp/backend/mpfr/tag.hpp>
#include <nt2/toolbox/mp/backend/mpfr/hierarchy.hpp>
*/
#include <nt2/toolbox/mp/dispatch.hpp>
#include <nt2/toolbox/mp/backend/mpfr/tag.hpp>
#include <nt2/toolbox/mp/backend/mpfr/hierarchy.hpp>
#include <nt2/toolbox/mp/float.hpp>

#include <boost/dispatch/functor/preprocessor/call.hpp>

#include <nt2/include/functions/plus.hpp>

#include <nt2/include/functions/terminal.hpp>
//#include <nt2/toolbox/mp/evaluate.hpp>

//#include <boost/dispatch/dsl/call.hpp>
//#include <boost/simd/sdk/simd/pack/call.hpp>

//#include <nt2/toolbox/operator/functions/plus.hpp>
//#include <nt2/toolbox/operator/functions/multiplies.hpp>

#include <iostream>


namespace nt2 { namespace mp
{
    BOOST_DISPATCH_IMPLEMENT(
        (nt2)(mp)
      , nt2::tag::plus_
      , boost::dispatch::tag::cpu_
      , (A0)(Tag0)(Arity0)(A1)(Tag1)(Arity1)
      , ((boost::dispatch::meta::expr_<boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A0>, nt2::mp::backend::tag::mpfr_ > >, Tag0, Arity0>))
        ((boost::dispatch::meta::expr_<boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A1>, nt2::mp::backend::tag::mpfr_ > >, Tag1, Arity1>))
    )
    {
        typedef A1 & result_type;

        result_type operator()(A0 const & a0, A1 & a1) const
        {
            std::cout << "plus2!\n";
            return a1;
        }
    };
}}


NT2_TEST_CASE (plus_)
{
    using nt2::mp::backend::mpfr;
    using nt2::mp::float_;

    /*
    {
        mpfr x,y,z;
        
        boost::dispatch::functor<boost::proto::tag::plus>()(x, y, z);
        nt2::plus(x, y);
    }
    */

    {
        float_<mpfr> x, y, z;

        std::cout << typeid(boost::dispatch::meta::hierarchy_of<float_<mpfr> >::type).name() << "\n";
        std::cout << typeid(boost::dispatch::meta::hierarchy_of<BOOST_TYPEOF(x+y)>::type).name() << "\n";
        std::cout << typeid(boost::dispatch::meta::hierarchy_of<mpfr>::type).name() << "\n";

        nt2::evaluate(y + z);
    }
}
