
#ifndef NT2_TOOLBOX_MP_DISPATCH_HPP
#define NT2_TOOLBOX_MP_DISPATCH_HPP

#include <boost/dispatch/dsl/call.hpp>
#include <nt2/toolbox/mp/calc.hpp>
#include <nt2/toolbox/mp/hierarchy.hpp>

namespace nt2 { namespace mp {

    template <typename Sig, typename Site, typename Enable = void>
    struct implement;
    
    BOOST_DISPATCH_IMPLEMENT(
        (nt2)(mp)
      , Tag
      , boost::dispatch::tag::cpu_
      , (Tag)(A0)(A1)(Backend)
      , ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A0>, Backend> >))
        ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A1>, Backend> >))
    )
    {
        typedef A0 result_type;

        result_type operator()(A0 const & a0, A1 const & a1) const
        {
            A0 state;
            //boost::dispatch::functor<Tag>()(a0, a1, state);
            calc<Tag, Backend>(a0, a1, state);
            return state;
        }
    };
    
    BOOST_DISPATCH_IMPLEMENT(
        (nt2)(mp)
      , Tag
      , boost::dispatch::tag::cpu_
      , (Tag)(A0)(A1)(Backend)
      , ((boost::dispatch::meta::scalar_<
            boost::dispatch::meta::arithmetic_<A1>
        >))
        ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A0>, Backend> >))
    )
    {
        typedef A0 result_type;

        result_type operator()(A0 const & a0, A1 const & a1) const
        {
            A0 state;
            calc<Tag, Backend>(a0, a1, state);
            return state;
        }
    };
    
    BOOST_DISPATCH_IMPLEMENT(
        (nt2)(mp)
      , Tag
      , boost::dispatch::tag::cpu_
      , (Tag)(A0)(A1)(Backend)
      , ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A0>, Backend> >))
        ((boost::dispatch::meta::scalar_<
            boost::dispatch::meta::arithmetic_<A1>
        >))
    )
    {
        typedef A0 result_type;

        result_type operator()(A0 const & a0, A1 const & a1) const
        {
            A0 state;
            calc<Tag, Backend>(a0, a1, state);
            return state;
        }
    };

    BOOST_DISPATCH_IMPLEMENT(
        (nt2)(mp)
      , Tag
      , boost::dispatch::tag::cpu_
      , (Tag)(A0)(A1)(State)(Backend)
      , ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A0>, Backend> >))
        ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A1>, Backend> >))
        ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<State>, Backend> >))
    )
    {
        typedef State & result_type;

        result_type operator()(A0 const & a0, A1 const & a1, State & state) const
        {
            std::cout << "got you?\n";
            return calc<Tag, Backend>(a0, a1, state);
        }
    };

    BOOST_DISPATCH_IMPLEMENT(
        (nt2)(mp)
      , Tag
      , boost::dispatch::tag::cpu_
      , (Tag)(A0)(A1)(State)(Backend)
      , ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A0>, Backend> >))
        ((boost::dispatch::meta::scalar_<
            boost::dispatch::meta::arithmetic_<A1>
        >))
        ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<State>, Backend> >))
    )
    {
        typedef State & result_type;

        result_type operator()(A0 const & a0, A1 const & a1, State & state) const
        {
            return calc<Tag, Backend>(a0, a1, state);
        }
    };

    BOOST_DISPATCH_IMPLEMENT(
        (nt2)(mp)
      , Tag
      , boost::dispatch::tag::cpu_
      , (Tag)(A0)(A1)(State)(Backend)
      , ((boost::dispatch::meta::scalar_<
            boost::dispatch::meta::arithmetic_<A1>
        >))
        ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<A0>, Backend> >))
        ((boost::dispatch::meta::scalar_<nt2::mp::meta::mp_<boost::dispatch::meta::floating_<State>, Backend> >))
    )
    {
        typedef State & result_type;

        result_type operator()(A0 const & a0, A1 const & a1, State & state) const
        {
            return calc<Tag, Backend>(a0, a1, state);
        }
    };
    
    /*
    */

}}

#endif
