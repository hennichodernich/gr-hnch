#!/usr/bin/env python
#
# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#
#

from gnuradio import gr
import pmt


class var_to_msg_dict(gr.sync_block):
    """
    This block has a callback that will emit a message dict with the updated variable
    value when called. This is useful for monitoring a GRC variable and emitting a message
    when it is changed.
    """

    def __init__(self, pairname, init_value=None):
        gr.sync_block.__init__(
            self, name="var_to_msg_dict", in_sig=None, out_sig=None)

        self.pairname = pairname
        self.init_value = init_value

        self.message_port_register_out(pmt.intern("msgout"))

    def variable_changed(self, value):
        try:
            if type(value) == float:
                p = pmt.from_double(value)
            elif type(value) == int:
                p = pmt.from_long(value)
            elif type(value) == bool:
                p = pmt.from_bool(value)
            elif type(value) == str:
                p = pmt.intern(value)
            else:
                p = pmt.to_pmt(value)

            d = pmt.make_dict()

            d = pmt.dict_add(d, pmt.intern(self.pairname), p)

            self.message_port_pub(pmt.intern("msgout"), d)

        except Exception as e:
            gr.log.error("Unable to convert " + repr(value) +
                         " to PDU, no message will be emitted (reason: %s)" % repr(e))

    def start(self):
        if self.init_value is None:
            return
        else:
            self.variable_changed(self.init_value)

    def stop(self):
        return True
