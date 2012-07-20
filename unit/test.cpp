
#define NT2_UNIT_MODULE "nt2 mpfr toolbox - sandbox test"

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/sdk/mp/float.hpp>
#include <nt2/sdk/mp/mpfr.hpp>
#include <nt2/sdk/mp/meta/hierarchy.hpp>
#include <nt2/sdk/mp/mpfr/meta/hierarchy.hpp>
#include <nt2/sdk/mp/mpfr/meta/terminal_of.hpp>

using namespace boost::dispatch::meta;

#define M0(z,n,t) ::parent
#define UP(T,N) T BOOST_PP_REPEAT(N,M0,~)

NT2_TEST_CASE(hierachy_of_backend_mpfr)
{
    using boost::is_same;
    using namespace boost::dispatch::meta;
    using nt2::mp::meta::mp_;
    using nt2::mp::float_;
    using nt2::mp::mpfr;
    using nt2::mp::tag::mpfr_;
    
    {
        typedef hierarchy_of<mpfr>::type base;
        
        NT2_TEST( (is_same<scalar_<mp_<floating_<mpfr>, mpfr_>    >, base>::value) );
        NT2_TEST( (is_same<scalar_<mp_<signed_<mpfr>, mpfr_>      >, UP(base, 1)>::value) );
        NT2_TEST( (is_same<scalar_<mp_<arithmetic_<mpfr>, mpfr_>  >, UP(base, 2)>::value) );
        NT2_TEST( (is_same<scalar_<mp_<fundamental_<mpfr>, mpfr_> >, UP(base, 3)>::value) );
        NT2_TEST( (is_same<scalar_<mp_<unspecified_<mpfr>, mpfr_> >, UP(base, 4)>::value) );
        
        NT2_TEST( (is_same<scalar_<floating_<mpfr>    >, UP(base, 5)>::value) );
        NT2_TEST( (is_same<scalar_<signed_<mpfr>      >, UP(base, 6)>::value) );
        NT2_TEST( (is_same<scalar_<arithmetic_<mpfr>  >, UP(base, 7)>::value) );
        NT2_TEST( (is_same<scalar_<fundamental_<mpfr> >, UP(base, 8)>::value) );
        NT2_TEST( (is_same<scalar_<unspecified_<mpfr> >, UP(base, 9)>::value) );
        
        NT2_TEST( (is_same<generic_<mp_<floating_<mpfr>, mpfr_>    > , UP(base,10) >::value) );
        NT2_TEST( (is_same<generic_<mp_<signed_<mpfr>, mpfr_>      > , UP(base,11) >::value) );
        NT2_TEST( (is_same<generic_<mp_<arithmetic_<mpfr>, mpfr_>  > , UP(base,12) >::value) );
        NT2_TEST( (is_same<generic_<mp_<fundamental_<mpfr>, mpfr_> > , UP(base,13) >::value) );
        NT2_TEST( (is_same<generic_<mp_<unspecified_<mpfr>, mpfr_> > , UP(base,14) >::value) );
        
        NT2_TEST( (is_same<generic_<floating_<mpfr>    > , UP(base,15) >::value) );
        NT2_TEST( (is_same<generic_<signed_<mpfr>      > , UP(base,16) >::value) );
        NT2_TEST( (is_same<generic_<arithmetic_<mpfr>  > , UP(base,17) >::value) );
        NT2_TEST( (is_same<generic_<fundamental_<mpfr> > , UP(base,18) >::value) );
        NT2_TEST( (is_same<generic_<unspecified_<mpfr> > , UP(base,19) >::value) );
        NT2_TEST( (is_same<unspecified_<mpfr>            , UP(base,20) >::value) );
    }
    {
        typedef hierarchy_of<float_<mpfr> >::type base;
        
        NT2_TEST( (is_same<expr_<scalar_<mp_<floating_<float_<mpfr> >, mpfr_> >, boost::simd::tag::terminal_, boost::mpl::long_<0l>    >, base>::value) );
        NT2_TEST( (is_same<expr_<scalar_<mp_<signed_<float_<mpfr> >, mpfr_> >, boost::simd::tag::terminal_, boost::mpl::long_<0l>    >, UP(base, 1)>::value) );
        NT2_TEST( (is_same<expr_<scalar_<mp_<arithmetic_<float_<mpfr> >, mpfr_> >, boost::simd::tag::terminal_, boost::mpl::long_<0l>    >, UP(base, 2)>::value) );
        NT2_TEST( (is_same<expr_<scalar_<mp_<fundamental_<float_<mpfr> >, mpfr_> >, boost::simd::tag::terminal_, boost::mpl::long_<0l>    >, UP(base, 3)>::value) );
        NT2_TEST( (is_same<expr_<scalar_<mp_<unspecified_<float_<mpfr> >, mpfr_> >, boost::simd::tag::terminal_, boost::mpl::long_<0l>    >, UP(base, 4)>::value) );
        
        NT2_TEST( (is_same<expr_<scalar_<floating_<float_<mpfr> > >, boost::simd::tag::terminal_, boost::mpl::long_<0l>    >, UP(base, 5)>::value) );
        NT2_TEST( (is_same<expr_<scalar_<signed_<float_<mpfr> > >, boost::simd::tag::terminal_, boost::mpl::long_<0l>    >, UP(base, 6)>::value) );
        NT2_TEST( (is_same<expr_<scalar_<arithmetic_<float_<mpfr> > >, boost::simd::tag::terminal_, boost::mpl::long_<0l>    >, UP(base, 7)>::value) );
        NT2_TEST( (is_same<expr_<scalar_<fundamental_<float_<mpfr> > >, boost::simd::tag::terminal_, boost::mpl::long_<0l>    >, UP(base, 8)>::value) );
        NT2_TEST( (is_same<expr_<scalar_<unspecified_<float_<mpfr> > >, boost::simd::tag::terminal_, boost::mpl::long_<0l>    >, UP(base, 9)>::value) );
        
        NT2_TEST( (is_same<expr_<generic_<mp_<floating_<float_<mpfr> >, mpfr_>    >, boost::simd::tag::terminal_, boost::mpl::long_<0l> > , UP(base,10) >::value) );
        NT2_TEST( (is_same<expr_<generic_<mp_<signed_<float_<mpfr> >, mpfr_>      >, boost::simd::tag::terminal_, boost::mpl::long_<0l> > , UP(base,11) >::value) );
        NT2_TEST( (is_same<expr_<generic_<mp_<arithmetic_<float_<mpfr> >, mpfr_>  >, boost::simd::tag::terminal_, boost::mpl::long_<0l> > , UP(base,12) >::value) );
        NT2_TEST( (is_same<expr_<generic_<mp_<fundamental_<float_<mpfr> >, mpfr_> >, boost::simd::tag::terminal_, boost::mpl::long_<0l> > , UP(base,13) >::value) );
        NT2_TEST( (is_same<expr_<generic_<mp_<unspecified_<float_<mpfr> >, mpfr_> >, boost::simd::tag::terminal_, boost::mpl::long_<0l> > , UP(base,14) >::value) );
        
        NT2_TEST( (is_same<expr_<generic_<floating_<float_<mpfr> >    >, boost::simd::tag::terminal_, boost::mpl::long_<0l> > , UP(base,15) >::value) );
        NT2_TEST( (is_same<expr_<generic_<signed_<float_<mpfr> >      >, boost::simd::tag::terminal_, boost::mpl::long_<0l> > , UP(base,16) >::value) );
        NT2_TEST( (is_same<expr_<generic_<arithmetic_<float_<mpfr> >  >, boost::simd::tag::terminal_, boost::mpl::long_<0l> > , UP(base,17) >::value) );
        NT2_TEST( (is_same<expr_<generic_<fundamental_<float_<mpfr> > >, boost::simd::tag::terminal_, boost::mpl::long_<0l> > , UP(base,18) >::value) );
        NT2_TEST( (is_same<expr_<generic_<unspecified_<float_<mpfr> > >, boost::simd::tag::terminal_, boost::mpl::long_<0l> > , UP(base,19) >::value) );
        NT2_TEST( (is_same<expr_<unspecified_<float_<mpfr> >           , boost::simd::tag::terminal_, boost::mpl::long_<0l> > , UP(base,20) >::value) );
        
        NT2_TEST( (is_same<node_<float_<mpfr>, boost::simd::tag::terminal_, boost::mpl::long_<0l> > , UP(base,21) >::value) );
        NT2_TEST( (is_same<node_<float_<mpfr>, elementwise_<boost::simd::tag::terminal_>, boost::mpl::long_<0l> > , UP(base,22) >::value) );
        NT2_TEST( (is_same<node_<float_<mpfr>, unspecified_<boost::simd::tag::terminal_>, boost::mpl::long_<0l> > , UP(base,23) >::value) );
        NT2_TEST( (is_same<ast_<float_<mpfr> > , UP(base,24) >::value) );
        NT2_TEST( (is_same<unspecified_<float_<mpfr> > , UP(base,25) >::value) );
        NT2_TEST( (is_same<unknown_<float_<mpfr> > , UP(base,26) >::value) );
    }
    {
        float_<mpfr> x, y;
        typedef hierarchy_of<BOOST_TYPEOF(x + y)>::type base;
        
        NT2_TEST( (is_same<expr_<scalar_<mp_<floating_<BOOST_TYPEOF(x + y) >, mpfr_> >, boost::simd::tag::plus_, boost::mpl::long_<2l>    >, base>::value) );
        NT2_TEST( (is_same<expr_<scalar_<mp_<signed_<BOOST_TYPEOF(x + y) >, mpfr_> >, boost::simd::tag::plus_, boost::mpl::long_<2l>    >, UP(base, 1)>::value) );
        NT2_TEST( (is_same<expr_<scalar_<mp_<arithmetic_<BOOST_TYPEOF(x + y) >, mpfr_> >, boost::simd::tag::plus_, boost::mpl::long_<2l>    >, UP(base, 2)>::value) );
        NT2_TEST( (is_same<expr_<scalar_<mp_<fundamental_<BOOST_TYPEOF(x + y) >, mpfr_> >, boost::simd::tag::plus_, boost::mpl::long_<2l>    >, UP(base, 3)>::value) );
        NT2_TEST( (is_same<expr_<scalar_<mp_<unspecified_<BOOST_TYPEOF(x + y) >, mpfr_> >, boost::simd::tag::plus_, boost::mpl::long_<2l>    >, UP(base, 4)>::value) );
        
        NT2_TEST( (is_same<expr_<scalar_<floating_<BOOST_TYPEOF(x + y) > >, boost::simd::tag::plus_, boost::mpl::long_<2l>    >, UP(base, 5)>::value) );
        NT2_TEST( (is_same<expr_<scalar_<signed_<BOOST_TYPEOF(x + y) > >, boost::simd::tag::plus_, boost::mpl::long_<2l>    >, UP(base, 6)>::value) );
        NT2_TEST( (is_same<expr_<scalar_<arithmetic_<BOOST_TYPEOF(x + y) > >, boost::simd::tag::plus_, boost::mpl::long_<2l>    >, UP(base, 7)>::value) );
        NT2_TEST( (is_same<expr_<scalar_<fundamental_<BOOST_TYPEOF(x + y) > >, boost::simd::tag::plus_, boost::mpl::long_<2l>    >, UP(base, 8)>::value) );
        NT2_TEST( (is_same<expr_<scalar_<unspecified_<BOOST_TYPEOF(x + y) > >, boost::simd::tag::plus_, boost::mpl::long_<2l>    >, UP(base, 9)>::value) );
        
        NT2_TEST( (is_same<expr_<generic_<mp_<floating_<BOOST_TYPEOF(x + y) >, mpfr_>    >, boost::simd::tag::plus_, boost::mpl::long_<2l> > , UP(base,10) >::value) );
        NT2_TEST( (is_same<expr_<generic_<mp_<signed_<BOOST_TYPEOF(x + y) >, mpfr_>      >, boost::simd::tag::plus_, boost::mpl::long_<2l> > , UP(base,11) >::value) );
        NT2_TEST( (is_same<expr_<generic_<mp_<arithmetic_<BOOST_TYPEOF(x + y) >, mpfr_>  >, boost::simd::tag::plus_, boost::mpl::long_<2l> > , UP(base,12) >::value) );
        NT2_TEST( (is_same<expr_<generic_<mp_<fundamental_<BOOST_TYPEOF(x + y) >, mpfr_> >, boost::simd::tag::plus_, boost::mpl::long_<2l> > , UP(base,13) >::value) );
        NT2_TEST( (is_same<expr_<generic_<mp_<unspecified_<BOOST_TYPEOF(x + y) >, mpfr_> >, boost::simd::tag::plus_, boost::mpl::long_<2l> > , UP(base,14) >::value) );
        
        NT2_TEST( (is_same<expr_<generic_<floating_<BOOST_TYPEOF(x + y) >    >, boost::simd::tag::plus_, boost::mpl::long_<2l> > , UP(base,15) >::value) );
        NT2_TEST( (is_same<expr_<generic_<signed_<BOOST_TYPEOF(x + y) >      >, boost::simd::tag::plus_, boost::mpl::long_<2l> > , UP(base,16) >::value) );
        NT2_TEST( (is_same<expr_<generic_<arithmetic_<BOOST_TYPEOF(x + y) >  >, boost::simd::tag::plus_, boost::mpl::long_<2l> > , UP(base,17) >::value) );
        NT2_TEST( (is_same<expr_<generic_<fundamental_<BOOST_TYPEOF(x + y) > >, boost::simd::tag::plus_, boost::mpl::long_<2l> > , UP(base,18) >::value) );
        NT2_TEST( (is_same<expr_<generic_<unspecified_<BOOST_TYPEOF(x + y) > >, boost::simd::tag::plus_, boost::mpl::long_<2l> > , UP(base,19) >::value) );
        NT2_TEST( (is_same<expr_<unspecified_<BOOST_TYPEOF(x + y) >           , boost::simd::tag::plus_, boost::mpl::long_<2l> > , UP(base,20) >::value) );
        
        NT2_TEST( (is_same<node_<BOOST_TYPEOF(x + y), boost::simd::tag::plus_, boost::mpl::long_<2l> > , UP(base,21) >::value) );
        NT2_TEST( (is_same<node_<BOOST_TYPEOF(x + y), elementwise_<boost::simd::tag::plus_>, boost::mpl::long_<2l> > , UP(base,22) >::value) );
        NT2_TEST( (is_same<node_<BOOST_TYPEOF(x + y), unspecified_<boost::simd::tag::plus_>, boost::mpl::long_<2l> > , UP(base,23) >::value) );
        NT2_TEST( (is_same<ast_<BOOST_TYPEOF(x + y) > , UP(base,24) >::value) );
        NT2_TEST( (is_same<unspecified_<BOOST_TYPEOF(x + y) > , UP(base,25) >::value) );
        NT2_TEST( (is_same<unknown_<BOOST_TYPEOF(x + y) > , UP(base,26) >::value) );

        std::cout << typeid(base).name() << "\n";
        std::cout << typeid(x+y).name() << "\n";
    }
}
