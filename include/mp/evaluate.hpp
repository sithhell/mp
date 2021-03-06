//==============================================================================
// Copyright 2012 & onward Thomas Heller
//
// Distributed under the Boost Software License, Version 1.0. See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef MP_EVALUATE_HPP
#define MP_EVALUATE_HPP

#include <mp/grammar_fwd.hpp>
#include <mp/optimize.hpp>

#include <boost/proto/proto_fwd.hpp>
#include <boost/proto/tags.hpp>

namespace mp {
    namespace detail
    {
        template <typename Backend, typename Tag, typename Arity>
        struct has_evaluate;
        
        template <typename Backend, typename Tag>
        struct has_evaluate<Backend, Tag, boost::mpl::long_<1> >
        {
            typedef char (&yes)[1];
            typedef char (&no)[2];

            template <
                typename C, Backend & (C::*)(Backend &, Backend const &) const
            >
            struct tester {};

            template <typename B>
            static yes
            test(
                tester<
                    typename B::template evaluate<Tag>
                  , &B::template evaluate<Tag>::operator()
                > *
            );

            template <typename B>
            static no test(...);

            static const int value = (sizeof(test<Backend>(0)) == sizeof(yes));
            typedef boost::mpl::bool_<value> type;
        };
        
        template <typename Backend, typename Tag>
        struct has_evaluate<Backend, Tag, boost::mpl::long_<2> >
        {
            typedef char (&yes)[1];
            typedef char (&no)[2];

            template <
                typename C
              , Backend & (C::*)(Backend &, Backend const &, Backend const &) const
            >
            struct tester {};

            template <typename B>
            static yes
            test(
                tester<
                    typename B::template evaluate<Tag>
                  , &B::template evaluate<Tag>::operator()
                > *
            );

            template <typename B>
            static no test(...);

            static const int value = (sizeof(test<Backend>(0)) == sizeof(yes));
            typedef boost::mpl::bool_<value> type;
        };
        
        template <typename Backend, typename Tag>
        struct has_evaluate<Backend, Tag, boost::mpl::long_<3> >
        {
            typedef char (&yes)[1];
            typedef char (&no)[2];

            template <
                typename C
              , Backend & (C::*)(Backend &, Backend const &, Backend const &, Backend const &) const
            >
            struct tester {};

            template <typename B>
            static yes
            test(
                tester<
                    typename B::template evaluate<Tag>
                  , &B::template evaluate<Tag>::operator()
                > *
            );

            template <typename B>
            static no test(...);

            static const int value = (sizeof(test<Backend>(0)) == sizeof(yes));
            typedef boost::mpl::bool_<value> type;
        };
    }

    template <typename Backend>
    struct evaluate
    {
        template <typename Sig>
        struct result
        {
            typedef Backend & type;
        };

        template <typename Tag, typename T>
        BOOST_FORCEINLINE
        Backend & operator()(Tag, T const & t, Backend & b) const
        {
            return optimize(Tag(), t, b, typename detail::has_optimize<Backend, T>::type());
        }

        template <typename Tag, typename T>
        BOOST_FORCEINLINE
        Backend & optimize(Tag, T const & t, Backend & b, boost::mpl::false_) const
        {
            typedef typename boost::proto::arity_of<T>::type arity;
            return
                eval(
                    Tag()
                  , t
                  , b
                  , arity()
                  , typename detail::has_evaluate<Backend, Tag, arity>::type()
                );
        }
        
        template <typename Tag, typename T>
        BOOST_FORCEINLINE
        Backend & optimize(Tag, T const & t, Backend & b, boost::mpl::true_) const
        {
            typename Backend::template optimize<T> opti;

            opti(t, grammar<Backend>(), b);

            return b;
        }
        
        template <typename Tag, typename T, typename Arity>
        BOOST_FORCEINLINE
        Backend & eval(
            Tag, T const & t, Backend & b, Arity, boost::mpl::false_
        ) const
        {
            BOOST_STATIC_ASSERT(sizeof(Tag) && false);
            return b;
        }

        template <typename Tag, typename T>
        BOOST_FORCEINLINE
        Backend &
        eval(
            Tag, T const & t, Backend & b, boost::mpl::long_<1>, boost::mpl::true_
        ) const
        {
            typename Backend::template evaluate<Tag> f;
            return f(b, grammar<Backend>()(boost::proto::child_c<0>(t), 0, b));
        }

        template <typename Tag, typename T>
        BOOST_FORCEINLINE
        Backend &
        eval(
            Tag, T const & t, Backend & b, boost::mpl::long_<2>, boost::mpl::true_
        ) const
        {
            // FIXME: this is innefficient.
            // Theoretically, we only need to construct a new temporary when
            // both children are not terminals
            Backend t2;
            typename Backend::template evaluate<Tag> f;
            return
                f(
                    b
                  , grammar<Backend>()(
                        boost::proto::child_c<0>(t)
                      , 0
                      , b
                    )
                  , grammar<Backend>()(
                        boost::proto::child_c<1>(t)
                      , 0
                      , t2
                    )
                );
        }

        template <typename Tag, typename T>
        BOOST_FORCEINLINE
        Backend &
        eval(
            Tag, T const & t, Backend & b, boost::mpl::long_<3>, boost::mpl::true_
        ) const
        {
            // FIXME: this is innefficient.
            // Theoretically, we only need to construct a new temporary when
            // both children are not terminals
            Backend t1;
            Backend t2;
            typename Backend::template evaluate<Tag> f;
            return
                f(
                    b
                  , grammar<Backend>()(
                        boost::proto::child_c<0>(t)
                      , 0
                      , b
                    )
                  , grammar<Backend>()(
                        boost::proto::child_c<1>(t)
                      , 0
                      , t1
                    )
                  , grammar<Backend>()(
                        boost::proto::child_c<2>(t)
                      , 0
                      , t2
                    )
                );
        }
    };
}

#endif
