
#define NT2_UNIT_MODULE "nt2 mpfr toolbox - sandbox test"

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/toolbox/mpfloat/mpfloat.hpp>
#include <nt2/toolbox/operator/functions/mpfr/plus.hpp>

NT2_TEST_CASE (test_)
{
    std::cout << "hello world!\n";

    using nt2::mpfloat::float_;
    using nt2::mpfloat::backend::mpfr;

    float_<mpfr> a, b, c;

    a = b + c;
}
