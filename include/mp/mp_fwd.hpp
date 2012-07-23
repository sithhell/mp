//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef MP_MP_FWD_HPP
#define MP_MP_FWD_HPP

#include <boost/proto/proto_fwd.hpp>

namespace mp
{
    ////////////////////////////////////////////////////////////////////////////
    // float_:
    //
    // The basic proto terminal type to be used in the nt2 expression template
    // system.
    //
    ////////////////////////////////////////////////////////////////////////////
    template <typename Backend, typename Dummy = boost::proto::is_proto_expr>
    struct mp_;
}

#endif
