#!/usr/bin/env python
# -*- coding: utf-8 -*-
# 
# Copyright 2014 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
from gnuradio import blocks
import hnch_swig as hnch

class qa_vec_mat_mult_cc (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_test1_t (self):
	A = (1, 2, 4, 8, 16, 32, 64, 128)
	expected_D = (10,100)
	matrix = ((0,1,0,1,0,0,0,0),(0,0,1,0,0,1,1,0))
	srcA = blocks.vector_source_c(A, False, 8)
	vmap = hnch.vec_mat_mult_cc(matrix)
	sinkD = blocks.vector_sink_c(2)
	self.tb.connect(srcA,vmap);
	self.tb.connect(vmap,sinkD);
        # set up fg
        self.tb.run ()
        # check data
	self.assertEqual(expected_D, sinkD.data())


if __name__ == '__main__':
    gr_unittest.run(qa_vec_mat_mult_cc, "qa_vec_mat_mult_cc.xml")
