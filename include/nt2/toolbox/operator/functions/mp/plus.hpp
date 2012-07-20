//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_MPFR_PLUS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTIONS_MPFR_PLUS_HPP_INCLUDED

/*
#include <boost/simd/toolbox/operator/include/functions/plus.hpp>
#include <nt2/toolbox/operator/include/functions/plus.hpp>
#include <nt2/toolbox/mp/float.hpp>
*/

namespace nt2 { namespace mp { namespace ext
{
    /*
        BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION_TPL(
            (nt2)(mp)(ext)
          , boost::simd::tag::plus_
          , boost::dispatch::tag::cpu_
          , (typename A0)(typename A1)
          , (boost::dispatch::meta::unspecified_<A0>)
            (boost::dispatch::meta::unspecified_<A1>)
        )
        {
            typedef void result_type;

            template <typename Src, typename Dst>
            result_type
            operator()(Src & src, Dst const & dst) const
            {
                std::cout << "plus!\n";

                boost::dispatch::meta::as_<A0> target;
                boost::dispatch::meta::compile<boost::dispatch::meta::compute<boost::mpl::_1, boost::dispatch::tag::cpu_> > callee;

                //src = callee(dst, target);
                std::cout
                    << typeid(A0).name() << "\n"
                    << typeid(A1).name() << "\n"
                    << typeid(Src).name() << "\n"
                    << typeid(Dst).name() << "\n"
                ;

            }
        };
        
        BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION_TPL(
            (nt2)(mp)(ext)
          , boost::simd::tag::plus_
          , boost::dispatch::tag::cpu_
          , (typename A0)(typename A1)
          , (boost::dispatch::meta::unknown_<A0>)
            (boost::dispatch::meta::unknown_<A1>)
        )
        {
            typedef void result_type;

            template <typename Src, typename Dst>
            result_type
            operator()(Src & src, Dst const & dst) const
            {
                std::cout << "plus!\n";

                boost::dispatch::meta::as_<A0> target;
                boost::dispatch::meta::compile<boost::dispatch::meta::compute<boost::mpl::_1, boost::dispatch::tag::cpu_> > callee;

                //src = callee(dst, target);
                std::cout
                    << typeid(A0).name() << "\n"
                    << typeid(A1).name() << "\n"
                    << typeid(Src).name() << "\n"
                    << typeid(Dst).name() << "\n"
                ;

            }
        };
        */

} }}

#endif
