//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef MP_GRAMMAR_HPP
#define MP_GRAMMAR_HPP

#include <mp/grammar_fwd.hpp>
#include <mp/evaluate.hpp>

#include <boost/proto/proto.hpp>

#include <iostream>

namespace mp
{
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
