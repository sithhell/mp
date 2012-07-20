//==============================================================================
//         Copyright 2012 & onward Thomas Heller
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MP_DOMAIN_HPP
#define NT2_SDK_MP_DOMAIN_HPP

#include <nt2/sdk/mp/domain_fwd.hpp>
#include <nt2/sdk/mp/expr_fwd.hpp>
#include <nt2/sdk/mp/grammar_fwd.hpp>

#include <boost/proto/domain.hpp>

namespace nt2 { namespace mp
{
    struct domain
        : boost::proto::domain<boost::proto::pod_generator<expr>, grammar>
    {};
}}

#endif
