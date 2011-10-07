
#ifndef NT2_TOOLBOX_MP_BACKEND_MPFR_HIERARCHY_HPP
#define NT2_TOOLBOX_MP_BACKEND_MPFR_HIERARCHY_HPP

#include <nt2/toolbox/mp/hierarchy.hpp>

namespace nt2 { namespace mp {
    namespace backend { 
        namespace tag {
            struct mpfr_;
        }
        struct mpfr;
    }
    
    namespace meta
    {
        template<class Origin>
        struct mp_of<backend::mpfr, Origin>
        {
            typedef boost::dispatch::meta::floating_<Origin> type;
        };
    }
}}

namespace boost { namespace dispatch { namespace meta {
    
    template<class Origin>
    struct property_of<nt2::mp::backend::mpfr, Origin>
    {
        typedef nt2::mp::meta::mp_<
            typename nt2::mp::meta::mp_of<nt2::mp::backend::mpfr, Origin>::type
          , nt2::mp::backend::tag::mpfr_
        > type;
    };
    
    template<class Origin>
    struct hierarchy_of<nt2::mp::backend::mpfr, Origin>
    {
        typedef
            scalar_< typename property_of<nt2::mp::backend::mpfr, Origin>::type >
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
