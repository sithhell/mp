//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef MP_MPFR_POW_HPP
#define MP_MPFR_POW_HPP

#include <mp/mpfr/mpfr.hpp>
#include <mp/pow.hpp>

namespace mp
{
    template <>
    struct mpfr::evaluate<tag::pow>
    {
        mpfr & operator()(mpfr &res, mpfr const & lhs, mpfr const & rhs) const
        {
            mpfr_pow(res.data, lhs.data, rhs.data, MPFR_RNDN);

            return res;
        }
    };
}

#endif
