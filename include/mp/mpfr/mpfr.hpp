//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef MP_MPFR_MPFR_HPP
#define MP_MPFR_MPFR_HPP

#include <mp/mpfr/mpfr_fwd.hpp>

//#include <boost/cstdint.hpp>
#include <mpfr.h>
#include <string>
#include <iostream>

namespace mp
{
    ////////////////////////////////////////////////////////////////////////////
    // Lightweight wrapper around mpfr_t:
    //  - RAII for ressource management
    //  - No operators except assignment
    //  - To be used with nt2
    //
    // See http://www.mpfr.org/mpfr-current/mpfr.html for more detail
    struct mpfr
    {
        typedef mpfr_t native_type;

        ////////////////////////////////////////////////////////////////////////
        // Constructors
        // Wrapping init and set functions:
        // http://www.mpfr.org/mpfr-current/mpfr.html#Initialization-Functions 

        // Initializes data, sets default precision and teh value to NaN
        // Does not throw
        mpfr();
        // Copy Constructor
        mpfr(
            mpfr const & value
          , mpfr_rnd_t rnd = MPFR_RNDN
        );
        // Value Constructors
        explicit mpfr(
            mpfr_t const & value
          , mpfr_rnd_t rnd = MPFR_RNDN
        );

        explicit mpfr(
            unsigned long int value
          , mpfr_rnd_t rnd = MPFR_RNDN
        );
        explicit mpfr(
            long int value
          , mpfr_rnd_t rnd = MPFR_RNDN
        );
        explicit mpfr(
            float value
          , mpfr_rnd_t rnd = MPFR_RNDN
        );
        explicit mpfr(
            double value
          , mpfr_rnd_t rnd = MPFR_RNDN
        );
        explicit mpfr(
            long double value
          , mpfr_rnd_t rnd = MPFR_RNDN
        );
        explicit mpfr(
            std::string const & value
          , int base = 10
          , mpfr_rnd_t rnd = MPFR_RNDN
        );
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // Destructor
        // Releases resources
        ~mpfr();
        ////////////////////////////////////////////////////////////////////////

        // Assignment
        mpfr & operator=(mpfr const & value);
        mpfr & operator=(mpfr_t const & value);
        mpfr & operator=(unsigned long int value);
        mpfr & operator=(long int value);
        mpfr & operator=(float value);
        mpfr & operator=(double value);
        mpfr & operator=(long double value);
        mpfr & operator=(std::string const & value);

        bool operator==(mpfr const &) const;

        mpfr_t data;

        template <typename Tag>
        struct evaluate;

        static std::size_t copy_count;
    };
    ////////////////////////////////////////////////////////////////////////////

    void swap(mpfr & f0, mpfr & f1);

    inline std::ostream & operator<<(std::ostream & os, mpfr const & m)
    {
        float tmp = mpfr_get_flt(m.data, MPFR_RNDN);
        os << tmp;
        return os;
    }
}

#endif
