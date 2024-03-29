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
/* BINDTOOL_HEADER_FILE(message_delay.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(336a74af03e532e681f94b1740ec92ba)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <hnch/message_delay.h>
// pydoc.h is automatically generated in the build directory
#include <message_delay_pydoc.h>

void bind_message_delay(py::module& m)
{

    using message_delay    = ::gr::hnch::message_delay;


    py::class_<message_delay, gr::block, gr::basic_block,
        std::shared_ptr<message_delay>>(m, "message_delay", D(message_delay))

        .def(py::init(&message_delay::make),
           py::arg("msg"),
           py::arg("delay_ms"),
           D(message_delay,make)
        )
        




        
        .def("set_msg",&message_delay::set_msg,       
            py::arg("msg"),
            D(message_delay,set_msg)
        )


        
        .def("msg",&message_delay::msg,       
            D(message_delay,msg)
        )


        
        .def("set_delay",&message_delay::set_delay,       
            py::arg("delay"),
            D(message_delay,set_delay)
        )


        
        .def("delay",&message_delay::delay,       
            D(message_delay,delay)
        )

        ;




}








