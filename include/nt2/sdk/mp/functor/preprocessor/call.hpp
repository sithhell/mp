//==============================================================================
//         Copyright 2012 & onward Thomas Heller
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MP_FUNCTOR_PREPROCESSOR_CALL_HPP
#define NT2_SDK_MP_FUNCTOR_PREPROCESSOR_CALL_HPP

#define NT2_MP_DISPATCH_FILLER_0(X, Y)                                          \
    ((X, Y)) NT2_MP_DISPATCH_FILLER_1
#define NT2_MP_DISPATCH_FILLER_1(X, Y)                                          \
    ((X, Y)) NT2_MP_DISPATCH_FILLER_0
#define NT2_MP_DISPATCH_FILLER_0_END
#define NT2_MP_DISPATCH_FILLER_1_END

#define NT2_MP_DISPATCH_IMPLEMENT_C_TPL_ARGS(R, D, E)                           \
    (BOOST_PP_TUPLE_ELEM(2, 0, E))

#define NT2_MP_DISPATCH_IMPLEMENT_C_HIERARCHY(R, D, E)                          \
    ((                                                                          \
        nt2::ext::scalar_<                                                      \
            nt2::mp::meta::mp_<                                                 \
                nt2::ext::floating_<                                            \
                    BOOST_PP_TUPLE_ELEM(2, 0, E)                                \
                >                                                               \
              , Backend                                                         \
            >                                                                   \
        >                                                                       \
    ))                                                                          \
/**/

#define NT2_MP_DISPATCH_IMPLEMENT_C(Tag, Backend, Args)                         \
    BOOST_DISPATCH_IMPLEMENT(                                                   \
        (nt2)(mp)                                                               \
      , Tag                                                                     \
      , boost::dispatch::tag::cpu_                                              \
      , BOOST_PP_SEQ_FOR_EACH(NT2_MP_DISPATCH_IMPLEMENT_C_TPL_ARGS, _ Args)     \
      , BOOST_PP_SEQ_FOR_EACH(NT2_MP_DISPATCH_IMPLEMENT_C_HIERARCHY, _ Args)    \
    )
/**/

#define NT2_MP_DISPATCH_IMPLEMENT(Tag, Backend, Args)                           \
    NT2_MP_DISPATCH_IMPLEMENT_C(                                                \
        Tag                                                                     \
      , Backend                                                                 \
      , BOOST_PP_CAT(NT2_MP_DISPATCH_FILLER_0 Args,_END)                        \
    )                                                                           \
/**/

#endif
