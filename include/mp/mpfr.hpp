//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef MP_MPFR_HPP
#define MP_MPFR_HPP

#include <mp/mpfr/mpfr.hpp>
#include <mp/mpfr/plus.hpp>
#include <mp/mpfr/minus.hpp>
#include <mp/mpfr/negate.hpp>
#include <mp/mpfr/multiplies.hpp>
#include <mp/mpfr/divides.hpp>
#include <mp/mpfr/fma.hpp>
#include <mp/mpfr/fms.hpp>
#include <mp/mpfr/exp.hpp>
#include <mp/mpfr/pow.hpp>
#include <mp/mpfr/fmod.hpp>

#include <mp/grammar.hpp>

namespace mp
{
    template <>
    template <>
    struct grammar<mpfr>::case_<boost::proto::tag::greater_equal> : boost::proto::not_<boost::proto::_> {};

    template <>
    template <>
    struct grammar<mpfr>::case_<boost::proto::tag::less_equal> : boost::proto::not_<boost::proto::_> {};
    
    template <>
    template <>
    struct grammar<mpfr>::case_<boost::proto::tag::less> : boost::proto::not_<boost::proto::_> {};
    
    template <>
    template <>
    struct grammar<mpfr>::case_<boost::proto::tag::shift_left> : boost::proto::not_<boost::proto::_> {};
    
    template <>
    template <>
    struct grammar<mpfr>::case_<boost::proto::tag::address_of> : boost::proto::not_<boost::proto::_> {};
}

#endif
