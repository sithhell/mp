//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef MP_FMOD_HPP
#define MP_FMOD_HPP

#include <mp/domain.hpp>

#include <boost/proto/make_expr.hpp>

namespace mp
{
    namespace tag
    {
        struct fmod {};
    }

    template <typename A0, typename A1>
    typename boost::proto::result_of::make_expr<tag::fmod, boost::proto::deduce_domain, A0 &, A1 &>::type const
    fmod(A0 & a0, A1 & a1)
    {
        return boost::proto::detail::make_expr_<tag::fmod, boost::proto::deduce_domain, A0 &, A1 &>()(a0, a1);
    }
    
    template <typename A0, typename A1>
    typename boost::proto::result_of::make_expr<tag::fmod, boost::proto::deduce_domain, A0 &, A1 const &>::type const
    fmod(A0 & a0, A1 const & a1)
    {
        return boost::proto::detail::make_expr_<tag::fmod, boost::proto::deduce_domain, A0 &, A1 const &>()(a0, a1);
    }
}

#endif
