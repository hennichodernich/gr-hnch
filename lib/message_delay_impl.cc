/* -*- c++ -*- */
/*
 * Copyright 2012-2013 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "message_delay_impl.h"
#include <gnuradio/io_signature.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <boost/thread/thread.hpp>


namespace gr {
namespace hnch {

message_delay::sptr
message_delay::make(pmt::pmt_t msg,
                            float delay_ms)
{
        return gnuradio::get_initial_sptr(
        new message_delay_impl(msg, delay_ms));
}


message_delay_impl::message_delay_impl(
    pmt::pmt_t msg,
    float delay_ms)
    : block("message_delay",
            io_signature::make(0, 0, 0),
            io_signature::make(0, 0, 0)),
      d_finished(true),
      d_delay_ms(delay_ms),
      d_msg(msg),
      d_port(pmt::mp("strobe"))
{
    // set up ports
    message_port_register_out(d_port);

    message_port_register_in(pmt::mp("set_msg"));
    set_msg_handler(pmt::mp("set_msg"), [this](pmt::pmt_t msg) { this->set_msg(msg); });
}

message_delay_impl::~message_delay_impl()
{
    gr::thread::scoped_lock d_mutex;
    
    d_finished = true;
    d_thread->interrupt();
    d_thread->join();
}

void message_delay_impl::set_msg(pmt::pmt_t msg)
{
    gr::thread::scoped_lock d_mutex;
    
    d_msg = msg;
    d_finished = false;
    
    d_thread = new boost::thread(boost::bind(&message_delay_impl::run, this));
}

void message_delay_impl::set_delay(float delay_ms)
{
    gr::thread::scoped_lock d_mutex;
    
    d_delay_ms = delay_ms;
}

void message_delay_impl::run()
{    
    gr::thread::scoped_lock d_mutex;

    if (d_finished==false) {
        boost::this_thread::sleep(boost::posix_time::milliseconds(std::max(0L, long(delay()))));
        message_port_pub(d_port, d_msg);
        d_finished = true;
    }
    return;
}

} /* namespace hnch */
} /* namespace gr */
