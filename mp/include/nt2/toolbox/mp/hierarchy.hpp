
#ifndef NT2_TOOLBOX_MP_HIERARCHY_HPP
#define NT2_TOOLBOX_MP_HIERARCHY_HPP

#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/dispatch/meta/property_of.hpp>

namespace nt2 { namespace mp
{
    namespace tag
    {
        struct mp_ {};
    }

    namespace meta
    {
        template <typename Parent>
        struct hierarchy
            : Parent
        {
            typedef Parent parent;
        };

        template <typename Hierarchy, typename Backend>
        struct mp_
            : boost::dispatch::meta::scalar_<Hierarchy>
#if 0
          : hierarchy<
                /*
                mp_<
                    typename Hierarchy::parent
                  , Backend
                >
                */
                boost::dispatch::meta::scalar_<Hierarchy>
            >
#endif
        {
            typedef boost::dispatch::meta::scalar_<Hierarchy> parent;
        };
        
        /*
        template <typename Hierarchy, typename Backend>
        struct mp_<boost::dispatch::meta::unspecified_<Hierarchy>, Backend>
            : hierarchy<
                boost::dispatch::meta::generic_<
                    typename boost::dispatch::meta::property_of<
                        Hierarchy
                    >::type
                >
            >
        {};
        */
    }
}}

#endif

