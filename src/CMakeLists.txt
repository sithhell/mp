
include (NT2Module)
nt2_module_source_setup(mp)
nt2_module_configure_toolbox(mp 0)

set(SOURCES
    sdk/mp/mpfr/mpfr.cpp
    )

nt2_module_add_library(nt2_sdk_mp ${SOURCES})
