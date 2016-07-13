/* -*- c++ -*- */
/* 
 * Copyright 2014 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "vec_mat_mult_cc_impl.h"

namespace gr {
  namespace hnch {

    vec_mat_mult_cc::sptr
    vec_mat_mult_cc::make(std::vector<std::vector<gr_complex> > A)
    {
      return gnuradio::get_initial_sptr
        (new vec_mat_mult_cc_impl(A));
    }

    /*
     * The private constructor
     */
    vec_mat_mult_cc_impl::vec_mat_mult_cc_impl(std::vector<std::vector<gr_complex> > A)
      : gr::sync_block("vec_mat_mult_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)*A[0].size()),
              gr::io_signature::make(1, 1, sizeof(gr_complex)*A.size())),
	d_A(A)
    {
    }

    /*
     * Our virtual destructor.
     */
    vec_mat_mult_cc_impl::~vec_mat_mult_cc_impl()
    {
    }


    int
    vec_mat_mult_cc_impl::work (int noutput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];

	for(unsigned int n = 0; n < (unsigned int)(noutput_items); n++) {
		unsigned int vlen_in = d_A[0].size();
		unsigned int vlen_out = d_A.size();
		for(unsigned int j=0;j<vlen_out;j++)
		{
			out[j+vlen_out*n]=0;
			for(unsigned int i=0;i<vlen_in;i++)
			{
				out[j+vlen_out*n]+=d_A[j][i]*in[i+vlen_in*n];
			}
		}
	}


        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace hnch */
} /* namespace gr */

