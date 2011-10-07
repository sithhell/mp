
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
}}

namespace boost { namespace dispatch { namespace meta
{
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
}}}


#endif
