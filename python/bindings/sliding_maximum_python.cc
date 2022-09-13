/*
 * Copyright 2022 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(sliding_maximum.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(e7fdd2ffad901e83aacdd6637df0e809)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <hnch/sliding_maximum.h>
// pydoc.h is automatically generated in the build directory
#include <sliding_maximum_pydoc.h>

void bind_sliding_maximum(py::module& m)
{

    using sliding_maximum    = ::gr::hnch::sliding_maximum;


    py::class_<sliding_maximum, gr::sync_block, gr::block, gr::basic_block,
        std::shared_ptr<sliding_maximum>>(m, "sliding_maximum", D(sliding_maximum))

        .def(py::init(&sliding_maximum::make),
           py::arg("length"),
           D(sliding_maximum,make)
        )
        




        
        .def("set_length",&sliding_maximum::set_length,       
            py::arg("length"),
            D(sliding_maximum,set_length)
        )

        ;




}







