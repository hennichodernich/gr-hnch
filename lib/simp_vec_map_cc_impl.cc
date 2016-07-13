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
#include <string.h>
#include "simp_vec_map_cc_impl.h"

namespace gr {
  namespace hnch {

    simp_vec_map_cc::sptr
    simp_vec_map_cc::make(size_t vlen_in, std::vector< size_t > mapping)
    {
      return gnuradio::get_initial_sptr
        (new simp_vec_map_cc_impl(vlen_in, mapping));
    }

    /*
     * The private constructor
     */
    simp_vec_map_cc_impl::simp_vec_map_cc_impl(size_t vlen_in, std::vector< size_t > mapping)
      : gr::sync_block("simp_vec_map_cc",
              gr::io_signature::make(1, 1, sizeof(gr_complex)*vlen_in),
              gr::io_signature::make(1, 1, sizeof(gr_complex)*mapping.size())),
        d_vlen_in(vlen_in)
    {
	set_mapping(mapping);
    }

    /*
     * Our virtual destructor.
     */
    simp_vec_map_cc_impl::~simp_vec_map_cc_impl()
    {
    }

    void simp_vec_map_cc_impl::set_mapping(std::vector< size_t > mapping)
    {
	for(unsigned int j=0; j<mapping.size(); j++) {
		if((mapping[j] >= d_vlen_in) || (mapping[j] < 0)){
			throw std::runtime_error("Mapping index out of bounds.");
		}
	}
	gr::thread::scoped_lock guard(d_mutex);
	d_mapping = mapping;
    }

    int
    simp_vec_map_cc_impl::work (int noutput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];

	for(unsigned int n = 0; n < (unsigned int)(noutput_items); n++) {
		unsigned int vlen_out = d_mapping.size();
		for(unsigned int j=0;j<vlen_out;j++)
		{
			out[j+vlen_out*n]=in[d_mapping[j]+d_vlen_in*n];
		}
	}

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace hnch */
} /* namespace gr */

