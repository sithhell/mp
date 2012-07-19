
#ifndef NT2_TOOLBOX_MP_COMPUTE_HPP
#define NT2_TOOLBOX_MP_COMPUTE_HPP

#include <nt2/toolbox/mp/ext/calc_impl.hpp>

namespace nt2 { namespace mp {

    template <typename Calc>
    struct has_call
    {
        typedef char no;
        typedef struct {char c[2];} yes;

        template <typename T>
        static yes test(typename T::call*);
        template <typename T>
        static no test(...);

        typedef
            boost::mpl::bool_<
                sizeof(has_call<Calc>::test<Calc>(0)) == sizeof(yes)
            >
            type;
    };

    namespace detail
    {
        template <typename Tag, typename Backend, typename A0, typename A1, typename State>
        State & calc(A0 const & a0, A1 const & a1, State & state, boost::mpl::true_)
        {
            return typename ext::calc_impl<Tag, Backend>::call()(a0, a1, state);
        }

        template <typename Tag, typename Backend, typename A0, typename A1, typename State>
        State & calc(A0 const & a0, A1 const & a1, State & state, boost::mpl::false_)
        {
            std::cout << "awesome!\n";
            state = boost::dispatch::functor<Tag>()(a0, a1);
            return state;
        }
    }
    
    template <typename Tag, typename Backend, typename A0, typename A1, typename State>
    State & calc(A0 const & a0, A1 const & a1, State & state)
    {
        //return typename ext::calc_impl<Tag, Backend>::call()(a0, a1, state);
        return
            detail::calc<Tag, Backend>(
                a0
              , a1
              , state
              , typename has_call<ext::calc_impl<Tag, Backend> >::type()
            );
    }

}}

#endif
