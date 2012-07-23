//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef MP_GRAMMAR_HPP
#define MP_GRAMMAR_HPP

#include <mp/grammar_fwd.hpp>

#include <boost/proto/proto.hpp>

#include <iostream>

namespace mp
{
    template <typename Backend>
    struct grammar;

    template <typename Backend>
    struct evaluate
    {
        typedef Backend & result_type;
        
        Backend & operator()(boost::proto::tag::terminal, Backend & t, Backend &) const
        {
            return t;
        }

        template <typename Tag, typename T>
        Backend & operator()(Tag, T const & t, Backend & b) const
        {
            return eval(Tag(), t, b, typename boost::proto::arity_of<T>::type());
        }

        template <typename Tag, typename T>
        Backend & eval(Tag, T const & t, Backend & b, boost::mpl::long_<1>) const
        {
            return evaluate<Backend>::call(Tag(), grammar<Backend>()(t, 0, b));
        }

        template <typename Tag, typename T>
        Backend & eval(Tag, T const & t, Backend & b, boost::mpl::long_<2>) const
        {
            typename Backend::template evaluate<Tag> eval;
            return
                eval(
                    b
                  , grammar<Backend>()(
                        boost::proto::child_c<0>(t)
                      , 0
                      , b
                    )
                  , grammar<Backend>()(
                        boost::proto::child_c<1>(t)
                      , 0
                      , b
                    )
                );
        }

        /*
        template <typename Tag, typename... A>
        static Backend & call(Tag, Backend & b, A...)
        {
            std::cout << typeid(Tag).name() << "\n";
            return b;
        }
        */
    };

    template <typename Backend>
    struct grammar
        : boost::proto::switch_<grammar<Backend> >
    {
        template <typename Tag>
        struct case_
            : boost::proto::or_<
                boost::proto::when<
                    boost::proto::terminal<boost::proto::_>
                  , boost::proto::call<
                        evaluate<Backend>(
                            Tag()
                          , boost::proto::_value(boost::proto::_)
                          , boost::proto::_data
                        )
                    >
                >
              , boost::proto::when<
                    boost::proto::nary_expr<
                        boost::proto::_
                      , boost::proto::vararg<grammar<Backend> >
                    >
                  , boost::proto::call<
                        evaluate<Backend>(
                            Tag()
                          , boost::proto::_
                          , boost::proto::_data
                      )
                    >
                >
            >
        {};
    };
}
#endif
