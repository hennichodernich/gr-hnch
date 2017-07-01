/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
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
#include <gnuradio/random.h>
#include "chancoding_bsc_bb_impl.h"

namespace gr {
  namespace hnch {

    chancoding_bsc_bb::sptr
    chancoding_bsc_bb::make(float ber, unsigned bits_per_byte, long seed)
    {
      return gnuradio::get_initial_sptr
        (new chancoding_bsc_bb_impl(ber, bits_per_byte, seed));
    }

    /*
     * The private constructor
     */
    chancoding_bsc_bb_impl::chancoding_bsc_bb_impl(float ber, unsigned bits_per_byte, long seed)
      : gr::block("chancoding_bsc_bb",
              gr::io_signature::make(1,1,1),
              gr::io_signature::make(1,1,1)),
	d_bits_per_byte(bits_per_byte),
	d_random(seed)
    {
	if (ber < 0 || ber > 1) {
		throw std::invalid_argument("ber must be in range [0; 1]");
	}
	if (d_bits_per_byte > 8) {
		throw std::invalid_argument("a byte only has 8 bits");
	}
	set_ber(ber);

    }

    /*
     * Our virtual destructor.
     */
    chancoding_bsc_bb_impl::~chancoding_bsc_bb_impl()
    {
    }

    void
    chancoding_bsc_bb_impl::set_ber(float ber)
	{
		gr::thread::scoped_lock guard(d_mutex);
		d_ber = ber;
	}

    int
    chancoding_bsc_bb_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
	const unsigned char *in = (const unsigned char *) input_items[0];
	unsigned char *out = (unsigned char *) output_items[0];

      // Do <+signal processing+>
	gr::thread::scoped_lock guard(d_mutex);
	for (int i = 0; i < noutput_items; i++) {
		out[i] = in[i];
		for (int b = 0; b < d_bits_per_byte; b++) {
			if (d_random.ran1() < d_ber) {
				out[i] ^= (0x01 << b);
			}
		}
	}

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput_items);

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

    void
    chancoding_bsc_bb_impl::setup_rpc()
    {
#ifdef GR_CTRLPORT
	add_rpc_variable(rpcbasic_sptr(new rpcbasic_register_get<chancoding_bsc_bb, float>( alias(), "BER", &add_const_ff::ber, pmt::from_double(0), pmt::from_double(1), pmt::from_double(0), "", "Bit Error Rate", RPC_PRIVLVL_MIN, DISPTIME | DISPOPTCPLX | DISPOPTSTRIP)));

       	add_rpc_variable(rpcbasic_sptr(new rpcbasic_register_set<chancoding_bsc_bb, float>( alias(), "BER", &add_const_ff::set_ber, pmt::from_double(0), pmt::from_double(1), pmt::from_double(0), "", "Bit Error Rate", RPC_PRIVLVL_MIN, DISPNULL)));
#endif /* GR_CTRLPORT */
    }

  } /* namespace hnch */
} /* namespace gr */
