#pragma once

#include <Python.h>
#include <pybind11/embed.h> // everything needed for embedding

namespace disp {

    namespace py = pybind11;

    int add(int a, int b) {
        return a + b;
    }

    PYBIND11_EMBEDDED_MODULE(disp, m) {
        m.doc() = "pybind11 example plugin"; // optional module docstring

        m.attr("a") = 1;

        m.def("add", &add, "A function that adds two numbers");
    }

}