//==============================================================================
//         Copyright 2012 & onward Thomas Heller
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MP_MPFR_MPFR_HPP
#define NT2_SDK_MP_MPFR_MPFR_HPP

#include <nt2/sdk/mp/mpfr/mpfr_fwd.hpp>

//#include <boost/cstdint.hpp>
#include <mpfr.h>
#include <string>

namespace nt2 { namespace mp
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

        mpfr_t data;
    };
    ////////////////////////////////////////////////////////////////////////////

    void swap(mpfr & f0, mpfr & f1);
}}

#endif
