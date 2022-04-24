/* -*- c++ -*- */
/*
 * Copyright 2012-2013 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef INCLUDED_HNCH_MESSAGE_DELAY_IMPL_H
#define INCLUDED_HNCH_MESSAGE_DELAY_IMPL_H

#include <hnch/message_delay.h>

namespace gr {
namespace hnch {

class HNCH_API message_delay_impl : public message_delay
{
private:
    boost::thread* d_thread;

    bool d_finished;
    float d_delay_ms;
    pmt::pmt_t d_msg;
    void run();
    
    const pmt::pmt_t d_port;

public:
    message_delay_impl(pmt::pmt_t msg,
                               float delay_ms);
    ~message_delay_impl();

    void set_msg(pmt::pmt_t msg);
    pmt::pmt_t msg() const { return d_msg; }

    void set_delay(float delay_ms);
    float delay() const { return d_delay_ms; }
};

} /* namespace hnch */
} /* namespace gr */

#endif /* INCLUDED_HNCH_MESSAGE_DELAY_IMPL_H */
