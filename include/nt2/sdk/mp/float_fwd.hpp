
//==============================================================================
//         Copyright 2012 & onward Thomas Heller
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MP_FLOAT_FWD_HPP
#define NT2_SDK_MP_FLOAT_FWD_HPP

#include <boost/proto/proto_fwd.hpp>

namespace nt2 { namespace mp
{
    ////////////////////////////////////////////////////////////////////////////
    // float_:
    //
    // The basic proto terminal type to be used in the nt2 expression template
    // system.
    //
    ////////////////////////////////////////////////////////////////////////////
    template <typename Backend, typename Dummy = boost::proto::is_proto_expr>
    struct float_;
}}

#endif
