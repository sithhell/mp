
#ifndef NT2_TOOLBOX_MP_EVALUATE_HPP
#define NT2_TOOLBOX_MP_EVALUATE_HPP

//#include <nt2/include/functions/compile.hpp>
//#include <nt2/include/functions/schedule.hpp>
//#include <nt2/include/functions/optimize.hpp>
#include <nt2/dsl/functions/optimize.hpp>
#include <nt2/dsl/functions/schedule.hpp>
#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/toolbox/mp/hierarchy.hpp>
#include <nt2/dsl/functions/evaluate.hpp>

namespace nt2 { namespace mp {

    BOOST_DISPATCH_IMPLEMENT(
        (nt2)(mp)
      , boost::simd::tag::terminal_
      , boost::dispatch::tag::cpu_
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

    BOOST_DISPATCH_IMPLEMENT(
        (nt2)(mp)
      , boost::simd::tag::evaluate_
      , boost::dispatch::tag::formal_
      , (A0)(Tag)(A1)(Backend)
      , ((boost::dispatch::meta::expr_<boost::dispatch::meta::unspecified_<A0>, nt2::mp::domain, Tag>))
        ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A1>, Backend> >))
    )
    {
        typedef A1 & result_type;

        result_type operator()(A0 const & a0, A1 & a1) const
        {
            std::cout << "help?\n";
            //boost::simd::compile(boost::simd::schedule(boost::simd::optimize(a0)))(a0, a1);
            return a1;
        }
    };

    BOOST_DISPATCH_IMPLEMENT(
        (nt2)(mp)
      , boost::simd::tag::evaluate_
      , boost::dispatch::tag::formal_
      , (A0)(Tag)
      , ((boost::dispatch::meta::expr_<boost::dispatch::meta::unspecified_<A0>, nt2::mp::domain, Tag>))
    )
    {
        typedef typename boost::dispatch::meta::semantic_of<A0>::type result_type;

        result_type operator()(A0 const & a0) const
        {
            result_type a1;
            //boost::simd::compile(boost::simd::schedule(boost::simd::optimize(a0)))(a0, a1);
            return a1;
        }
    };
}}

#endif
