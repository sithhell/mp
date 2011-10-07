
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
        template<class T, class Origin = void>
        struct mp_of
        {
            typedef boost::dispatch::meta::unspecified_<T> type;
        };
        
        template<class T, class B>
        struct mp_ : mp_<typename T::parent, B>
        {
            typedef mp_<typename T::parent, B> parent;
        };
        
        template<class T, class B>
        struct mp_< boost::dispatch::meta::unspecified_<T>, B >
            : mp_of<
                typename boost::dispatch::meta::primitive_of<T>::type
              , T
            >::type
        {
            typedef typename mp_of< typename boost::dispatch::meta::primitive_of<T>::type, T>::type parent;
        };

#if 0
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
#endif
    }
}}

#endif

