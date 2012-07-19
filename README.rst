.. title:: NT2 - C++ High Performance Computing Made Easy


=================================================
The Numerical Template Toolbox MP module
=================================================

.. image:: http://www.lri.fr/~falcou/nt2.png
   :align: right

.. contents:: Index

--------------------
About **NT**:sup:`2`
--------------------
The **Numerical Template Toolbox** (**NT**:sup:`2`) is an Open Source C++ library
aimed at simplifying the development, debugging and optimization of
high-performance computing application by providing a **Matlab** like syntax that
ease the transition between prototype and actual application.

More Information can be found at: https://github.com/MetaScale/nt2

So What is This Module About ?
:::::::::::::::::::::::
This repository contains a module that tries to provide a generic interface for
**NT**:sup:`2` to support multi-precision floating point libraries.

As a proof of concept this library implements an adapter for
`MPFR <http://www.mpfr.org/>`_.

Installation
:::::::::::::::::::::::

    git clone git://github.com/MetaScale/nt2.git

    cd modules

    git clone git@github.com:sithhell/mp.git

    cd ..

    mkdir build

    cd build

    cmake ..

For more information refer to: http://nt2.metascale.org/doc/html/setting_up_nt__/__nt2___github_clone.html

