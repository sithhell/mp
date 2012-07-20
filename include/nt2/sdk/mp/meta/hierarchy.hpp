//==============================================================================
//         Copyright 2012 & onward Thomas Heller
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MP_META_HIERARCHY_HPP
#define NT2_SDK_MP_META_HIERARCHY_HPP

namespace nt2 { namespace mp {
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
    }
}}
#endif
