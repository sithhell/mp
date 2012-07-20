//==============================================================================
//         Copyright 2012 & onward Thomas Heller
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MP_GRAMMAR_HPP
#define NT2_SDK_MP_GRAMMAR_HPP

#include <nt2/sdk/mp/grammar_fwd.hpp>

#include <boost/proto/matches.hpp>

namespace nt2 { namespace mp
{
    template <typename Backend>
    struct grammar
        : boost::proto::or_<
          /*
            boost::proto::plus<grammar, grammar>
          , boost::proto::multiplies<grammar, grammar>
          , boost::proto::assign<boost::proto::terminal<, grammar>
          , boost::proto::terminal<boost::proto::_>
          */
          boost::proto::_
        >
    {};
}}
#endif
