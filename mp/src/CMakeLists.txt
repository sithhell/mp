
include (NT2Module)
nt2_module_source_setup(mp)
nt2_module_configure_toolbox(mp 1)

set(SOURCES
    toolbox/mp/backend/mpfr.cpp
    )

nt2_module_add_library(nt2_toolbox_mp ${SOURCES})
