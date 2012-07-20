//==============================================================================
//         Copyright 2012 & onward Thomas Heller
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MP_MPFR_META_HIERARCHY_HPP
#define NT2_SDK_MP_MPFR_META_HIERARCHY_HPP

#include <nt2/sdk/mp/meta/hierarchy.hpp>
#include <nt2/sdk/mp/mpfr/tag_fwd.hpp>
#include <nt2/sdk/mp/mpfr/mpfr_fwd.hpp>

namespace nt2 { namespace mp {
    namespace meta
    {
        template<class Origin>
        struct mp_of<mpfr, Origin>
        {
            typedef boost::dispatch::meta::floating_<Origin> type;
        };
    }
}}

namespace boost { namespace dispatch { namespace meta {
    
    template<class Origin>
    struct property_of<nt2::mp::mpfr, Origin>
    {
        typedef nt2::mp::meta::mp_<
            typename nt2::mp::meta::mp_of<nt2::mp::mpfr, Origin>::type
          , nt2::mp::tag::mpfr_
        > type;
    };
    
    template<class Origin>
    struct hierarchy_of<nt2::mp::mpfr, Origin>
    {
        typedef
            scalar_< typename property_of<nt2::mp::mpfr, Origin>::type >
            type;
    };
    /*
    template <typename Origin>
    struct property_of< ::nt2::mp::backend::mpfr, Origin>
    {
        typedef floating_<Origin> type;
    };

    template <typename Origin>
    struct hierarchy_of< ::nt2::mp::backend::mpfr, Origin>
    {
        typedef
            nt2::mp::meta::mp_<
                typename property_of<
                    ::nt2::mp::backend::mpfr
                  , Origin
                >::type
              , nt2::mp::backend::tag::mpfr_
            >
            type;
    };
    */
}}}


#endif
