//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef MP_MPFR_PLUS_HPP
#define MP_MPFR_PLUS_HPP

#include <mp/grammar.hpp>
#include <mp/mpfr/mpfr.hpp>

namespace mp
{
    template <>
    struct mpfr::evaluate<boost::proto::tag::plus>
    {
        mpfr & operator()(mpfr &res, mpfr const & rhs, mpfr const & lhs) const
        {
            mpfr_add(res.data, rhs.data, lhs.data, MPFR_RNDN);

            return res;
        }
    };
}

#endif
