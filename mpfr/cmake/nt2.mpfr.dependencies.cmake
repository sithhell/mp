################################################################################
#         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
#         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
#
#          Distributed under the Boost Software License, Version 1.0.
#                 See accompanying file LICENSE.txt or copy at
#                     http://www.boost.org/LICENSE_1_0.txt
################################################################################

find_path(MPFR_INCLUDE_DIR mpfr.h)
find_library(MPFR_LIBRARY mpfr)
mark_as_advanced(MPFR_INCLUDE_DIR MPFR_LIBRARY)

if(NOT MPFR_INCLUDE_DIR OR NOT MPFR_LIBRARY)
  set(NT2_MPFR_DEPENDENCIES_FOUND 0)
else()
  set(NT2_MPFR_DEPENDENCIES_FOUND 1)
  set(NT2_MPFR_DEPENDENCIES_INCLUDE_DIR ${MPFR_INCLUDE_DIR})
  set(NT2_MPFR_DEPENDENCIES_LIBRARIES ${MPFR_LIBRARY})
  set(NT2_MPFR_DEPENDENCIES_EXTRA sdk)
endif()
