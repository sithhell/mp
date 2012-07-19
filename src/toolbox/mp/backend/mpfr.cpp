
#include <mpfr.h>
#include <nt2/toolbox/mp/backend/mpfr/mpfr.hpp>

namespace nt2 { namespace mp { namespace backend
{
    mpfr::mpfr()
    {
        mpfr_init(data);
    }

    mpfr::mpfr(mpfr const & value, mpfr_rnd_t rnd)
    {
        mpfr_init_set(data, value.data, rnd);
    }

    mpfr::mpfr(mpfr_t const & value, mpfr_rnd_t rnd)
    {
        mpfr_init_set(data, value, rnd);
    }
    
    mpfr::mpfr(unsigned long int value, mpfr_rnd_t rnd)
    {
        mpfr_init_set_ui(data, value, rnd);
    }
    
    mpfr::mpfr(long int value, mpfr_rnd_t rnd)
    {
        mpfr_init_set_si(data, value, rnd);
    }
    
    mpfr::mpfr(float value, mpfr_rnd_t rnd)
    {
        mpfr_init(data);
        mpfr_set_flt(data, value, rnd);
    }
    
    mpfr::mpfr(double value, mpfr_rnd_t rnd)
    {
        mpfr_init_set_d(data, value, rnd);
    }
    
    mpfr::mpfr(long double value, mpfr_rnd_t rnd)
    {
        mpfr_init_set_ld(data, value, rnd);
    }

    mpfr::mpfr(std::string const & value, int base, mpfr_rnd_t rnd)
    {
        mpfr_init(data);
        const char *start = value.c_str();
        char * end        = 0;
        mpfr_strtofr(data, start, &end, base, rnd);
    }

    mpfr::~mpfr()
    {
        mpfr_clear(data);
    }
        
    mpfr & mpfr::operator=(mpfr const & value)
    {
        mpfr tmp(value);
        swap(*this, tmp);
        return *this;
    }
        
    mpfr & mpfr::operator=(mpfr_t const & value)
    {
        mpfr tmp(value);
        swap(*this, tmp);
        return *this;
    }

    mpfr & mpfr::operator=(unsigned long int value)
    {
        mpfr tmp(value);
        swap(*this, tmp);
        return *this;
    }

    mpfr & mpfr::operator=(long int value)
    {
        mpfr tmp(value);
        swap(*this, tmp);
        return *this;
    }

    mpfr & mpfr::operator=(float value)
    {
        mpfr tmp(value);
        swap(*this, tmp);
        return *this;
    }

    mpfr & mpfr::operator=(double value)
    {
        mpfr tmp(value);
        swap(*this, tmp);
        return *this;
    }

    mpfr & mpfr::operator=(long double value)
    {
        mpfr tmp(value);
        swap(*this, tmp);
        return *this;
    }

    mpfr & mpfr::operator=(std::string const & value)
    {
        mpfr tmp(value);
        swap(*this, tmp);
        return *this;
    }

    void swap(mpfr & f0, mpfr & f1)
    {
        mpfr_swap(f0.data, f1.data);
    }
}}}
