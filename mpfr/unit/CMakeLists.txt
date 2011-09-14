
nt2_module_use_modules(unit)

SET( SOURCES
    test.cpp
    )

nt2_module_add_tests(nt2.mpfr.unit ${SOURCES})
