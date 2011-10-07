
#ifndef NT2_TOOLBOX_MP_DISPATCH_HPP
#define NT2_TOOLBOX_MP_DISPATCH_HPP

#include <boost/dispatch/dsl/call.hpp>
#include <nt2/toolbox/mp/compute.hpp>
#include <nt2/toolbox/mp/hierarchy.hpp>

namespace nt2 { namespace mp {

    template <typename Sig, typename Site, typename Enable = void>
    struct implement;
    
    /*
    BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(
        (nt2)(mp)
      , boost::simd::tag::plus_
      , boost::dispatch::tag::formal_
      , (A0)(A1)(State)(Backend)
      , ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A0>, Backend> >))
        ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A1>, Backend> >))
        ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<State>, Backend> >))
    )
    {
        typedef State & result_type;

        result_type operator()(A0 const & a0, A1 const & a1, State & state) const
        {
            return compute<boost::simd::tag::plus_, Backend>(a0, a1, state);
        }
    };

    BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(
        (nt2)(mp)
      , Tag
      , boost::dispatch::tag::formal_
      , (Tag)(A0)(A1)(State)(Backend)
      , ((nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A0>, Backend>))
        ((nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A1>, Backend>))
        ((nt2::mp::meta::mp_<boost::dispatch::meta::floating_<State>, Backend>))
    )
    {
        typedef State & result_type;

        result_type operator()(A0 const & a0, A1 const & a1, State & state) const
        {
            return compute<Tag, Backend>(a0, a1, state);
        }
    };

    BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(
        (nt2)(mp)
      , Tag
      , boost::dispatch::tag::formal_
      , (Tag)(A0)(A1)(State)(Backend)
      , ((nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A0>, Backend>))
        ((boost::dispatch::meta::scalar_<
            boost::dispatch::meta::arithmetic_<A1>
        >))
        ((nt2::mp::meta::mp_<boost::dispatch::meta::floating_<State>, Backend>))
    )
    {
        typedef State & result_type;

        result_type operator()(A0 const & a0, A1 const & a1, State & state) const
        {
            return compute<Tag, Backend>(a0, a1, state);
        }
    };

    BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(
        (nt2)(mp)
      , Tag
      , boost::dispatch::tag::formal_
      , (Tag)(A0)(A1)(State)(Backend)
      , ((boost::dispatch::meta::scalar_<
            boost::dispatch::meta::arithmetic_<A1>
        >))
        ((nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A0>, Backend>))
        ((nt2::mp::meta::mp_<boost::dispatch::meta::floating_<State>, Backend>))
    )
    {
        typedef State & result_type;

        result_type operator()(A0 const & a0, A1 const & a1, State & state) const
        {
            return compute<Tag, Backend>(a0, a1, state);
        }
    };
    
    BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION(
        (nt2)(mp)
      , Tag
      , boost::dispatch::tag::formal_
      , (Tag)(A0)(A1)(Backend)
      , ((boost::dispatch::meta::scalar_<
            boost::dispatch::meta::arithmetic_<A1>
        >))
       ((nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A0>, Backend>))
    )
    {
        typedef A0 result_type;

        result_type operator()(A0 const & a0, A1 const & a1) const
        {
            A0 tmp;
            tmp = compute<Tag, Backend>(a0, a1, tmp);
            return tmp;
        }
    };
    */

}}

#endif
