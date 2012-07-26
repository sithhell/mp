//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <mp/mpfr/mpfr.hpp>
#include <sstream>
#include <cstdlib>
#include <cstring>

namespace mp
{
    std::size_t mpfr::copy_count = 0;

    mpfr::mpfr()
    {
        mpfr_init(data);
    }

    mpfr::mpfr(mpfr const & value, mpfr_rnd_t rnd)
    {
        mpfr_init_set(data, value.data, rnd);
        ++copy_count;
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
    
    mpfr::mpfr(int value, mpfr_rnd_t rnd)
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
        if(MPFR_MANT(data))
            mpfr_clear(data);
    }
        
    mpfr & mpfr::operator=(mpfr const & value)
    {
        mpfr tmp(value);
        swap(*this, tmp);
        ++copy_count;
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

    mpfr & mpfr::operator=(int value)
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

    template <class T>
    std::string to_string(T t, std::ios_base & (*f)(std::ios_base&))
    {
      std::ostringstream oss;
      oss << f << t;
      return oss.str();
    }

    std::string mpfr::to_string(size_t n, int b, mp_rnd_t mode) const
    {
        using std::string;
        char *s, *ns = NULL;
        size_t slen, nslen;
        mp_exp_t exp;
        string out;
        
        if(mpfr_inf_p(data))
        {
            if(mpfr_sgn(data)>0) return "+@Inf@";
            else                 return "-@Inf@";
        }
        
        if(mpfr_zero_p(data)) return "0";
        if(mpfr_nan_p(data))  return "@NaN@";
        
        s  = mpfr_get_str(NULL,&exp,b,0,data,mode);
        ns = mpfr_get_str(NULL,&exp,b,n,data,mode);
       
        if(s!=NULL && ns!=NULL)
        {
            slen  = strlen(s);
            nslen = strlen(ns);
            if(nslen<=slen)
            {
                mpfr_free_str(s);
                s = ns;
                slen = nslen;
            }
            else {
                mpfr_free_str(ns);
            }
            
            // Make human eye-friendly formatting if possible
            if (exp>0 && static_cast<size_t>(exp)<slen)
            {
                if(s[0]=='-')
                {
                    // Remove zeros starting from right end
                    char* ptr = s+slen-1;
                    while (*ptr=='0' && ptr>s+exp) ptr--;
                    
                    if(ptr==s+exp) out = string(s,exp+1);
                    else           out = string(s,exp+1)+'.'+string(s+exp+1,ptr-(s+exp+1)+1);
                    
                    //out = string(s,exp+1)+'.'+string(s+exp+1);
                }
                else
                {
                    // Remove zeros starting from right end
                    char* ptr = s+slen-1;
                    while (*ptr=='0' && ptr>s+exp-1) ptr--;
                    
                    if(ptr==s+exp-1) out = string(s,exp);
                    else             out = string(s,exp)+'.'+string(s+exp,ptr-(s+exp)+1);
                    
                    //out = string(s,exp)+'.'+string(s+exp);
                }
                
            }else{ // exp<0 || exp>slen
                if(s[0]=='-')
                {
                    // Remove zeros starting from right end
                    char* ptr = s+slen-1;
                    while (*ptr=='0' && ptr>s+1) ptr--;
                    
                    if(ptr==s+1) out = string(s,2);
                    else         out = string(s,2)+'.'+string(s+2,ptr-(s+2)+1);
                    
                    //out = string(s,2)+'.'+string(s+2);
                }
                else
                {
                    // Remove zeros starting from right end
                    char* ptr = s+slen-1;
                    while (*ptr=='0' && ptr>s) ptr--;
                    
                    if(ptr==s) out = string(s,1);
                    else       out = string(s,1)+'.'+string(s+1,ptr-(s+1)+1);
                    
                    //out = string(s,1)+'.'+string(s+1);
                }
                
                // Make final string
                if(--exp)
                {
                    if(exp>0) out += "e+"+mp::to_string<mp_exp_t>(exp,std::dec);
                    else      out += "e"+mp::to_string<mp_exp_t>(exp,std::dec);
                }
            }
            
            mpfr_free_str(s);
            return out;
        }else{
            return "conversion error!";
        }
    }

    bool operator==(mpfr const & lhs, mpfr const & rhs)
    {
        return mpfr_equal_p(lhs.data, rhs.data) != 0;
    }

    bool operator>=(mpfr const & lhs, mpfr const & rhs)
    {
        return mpfr_greaterequal_p(lhs.data, rhs.data) != 0;
    }

    bool operator<=(mpfr const & lhs, mpfr const & rhs)
    {
        return mpfr_lessequal_p(lhs.data, rhs.data) != 0;
    }

    bool operator<(mpfr const & lhs, mpfr const & rhs)
    {
        return mpfr_less_p(lhs.data, rhs.data) != 0;
    }

    void swap(mpfr & f0, mpfr & f1)
    {
        mpfr_swap(f0.data, f1.data);
    }
}
