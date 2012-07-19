
#define NT2_UNIT_MODULE "nt2 mpfr toolbox - sandbox test"

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/toolbox/mp/backend/mpfr/mpfr.hpp>
#include <nt2/toolbox/mp/backend/mpfr/tag.hpp>
#include <nt2/toolbox/mp/backend/mpfr/hierarchy.hpp>
#include <nt2/toolbox/mp/dispatch.hpp>
#include <nt2/toolbox/mp/float.hpp>
#include <nt2/toolbox/mp/evaluate.hpp>

#include <boost/dispatch/dsl/call.hpp>
#include <boost/simd/sdk/simd/pack/call.hpp>

#include <nt2/toolbox/operator/functions/plus.hpp>
#include <nt2/toolbox/operator/functions/multiplies.hpp>

#include <iostream>


namespace nt2 { namespace mp
{
#define H(A0)\
    boost::dispatch::meta::scalar_< \
        nt2::mp::meta::mp_< \
            boost::dispatch::meta::floating_< \
                A0 \
            > \
          , nt2::mp::backend::tag::mpfr_ \
        > \
    > \
    /**/

    // generic case
    
    // tag::plus_ case
    BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(
        (nt2)(mp)
      , nt2::tag::plus_
      , boost::dispatch::tag::cpu_
      , (A0)(A1)(A2)
      , ((H(A0)))
        ((H(A1)))
        ((H(A2)))
    )
    {
        typedef A2 & result_type;

        result_type operator()(A0 const & a0, A1 const & a1, A2 & a2) const
        {
            std::cout << "plus!\n";
            return a2;
        }
    };


}}

NT2_TEST_CASE (plus_)
{
    using nt2::mp::backend::mpfr;
    using nt2::mp::float_;

    {
        mpfr x,y,z;
        
        boost::dispatch::functor<boost::proto::tag::plus>()(x, y, z);
        nt2::plus(x, y);
    }

    {
        float_<mpfr> x, y, z;

        x = y + z;

        nt2::evaluate(x+y);
    }
}
