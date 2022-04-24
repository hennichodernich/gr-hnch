/* -*- c++ -*- */
/*
 * Copyright 2012-2013 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#ifndef INCLUDED_HNCH_MESSAGE_DELAY_H
#define INCLUDED_HNCH_MESSAGE_DELAY_H

#include <gnuradio/block.h>
#include <hnch/api.h>

namespace gr {
namespace hnch {

class HNCH_API message_delay : virtual public block
{
public:
    typedef std::shared_ptr<message_delay> sptr;

    static sptr make(pmt::pmt_t msg,
                     float delay_ms);

    /*!
     * Reset the message being sent.
     * \param msg The message to send as a PMT.
     */
    virtual void set_msg(pmt::pmt_t msg) = 0;

    /*!
     * Get the value of the message being sent.
     */
    virtual pmt::pmt_t msg() const = 0;

    /*!
     * Reset the sending interval.
     * \param delay in milliseconds.
     */
    virtual void set_delay(float delay) = 0;

    /*!
     * Get the time interval of the strobe_random.
     */
    virtual float delay() const = 0;
};

} /* namespace hnch */
} /* namespace gr */

#endif /* INCLUDED_HNCH_MESSAGE_DELAY_H */
