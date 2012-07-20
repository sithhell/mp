
#define NT2_UNIT_MODULE "nt2 mpfr toolbox - sandbox test"

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/sdk/mp/float.hpp>
#include <nt2/sdk/mp/mpfr.hpp>

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
        float_<mpfr> x, y, z, a;

        std::cout << typeid(boost::dispatch::meta::hierarchy_of<float_<mpfr> >::type).name() << "\n";
        std::cout << typeid(boost::dispatch::meta::hierarchy_of<BOOST_TYPEOF(x+y)>::type).name() << "\n";
        std::cout << typeid(boost::dispatch::meta::hierarchy_of<mpfr>::type).name() << "\n";

        /*
        x = y + z;
        
        x = y + z + a;

        nt2::evaluate(y + z);
        */
    }
}
