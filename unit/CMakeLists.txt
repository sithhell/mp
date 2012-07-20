
nt2_module_use_modules(unit mp)

SET( SOURCES
    test.cpp
    test2.cpp
    )

nt2_module_add_tests(nt2.mp.unit ${SOURCES})
