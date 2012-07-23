#==============================================================================
# Copyright 2012 & onward Thomas Heller
#
# Distributed under the Boost Software License, Version 1.0. See accompanying
# file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt
#==============================================================================

cmake_minimum_required(VERSION 2.6)

include_directories(${CMAKE_SOURCE_DIR}/include)

find_path(MPFR_INCLUDE_DIR mpfr.h)
find_library(MPFR_LIBRARY mpfr)
mark_as_advanced(MPFR_INCLUDE_DIR MPFR_LIBRARY)

find_package(Boost)

include_directories(${MPFR_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIRS})

set(MP_LIBRARY_SOURCES
    src/mpfr/mpfr.cpp
)


add_library(mp ${MP_LIBRARY_SOURCES})
target_link_libraries(mp ${Boost_LIBRARIES} ${MPFR_LIBRARY})

set(MP_TEST_SOURCES
    test
)

foreach(test ${MP_TEST_SOURCES})
    add_executable(${test} unit/${test}.cpp)
    target_link_libraries(${test} mp)
endforeach()
