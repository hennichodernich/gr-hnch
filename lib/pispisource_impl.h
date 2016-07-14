/* -*- c++ -*- */
/* 
 * Copyright 2016 <+YOU OR YOUR COMPANY+>.
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

#ifndef INCLUDED_HNCH_PISPISOURCE_IMPL_H
#define INCLUDED_HNCH_PISPISOURCE_IMPL_H

#include <hnch/pispisource.h>

namespace gr {
  namespace hnch {

    class pispisource_impl : public pispisource
    {
	int         	d_spi_clock;
	int		d_bus_num, d_device_num;
	int         	d_fd;
      	uint16_t	*d_buffer;
      	int		d_chunk_size;
	
	struct spi_ioc_transfer transfer_struct;
     private:
      // Nothing to declare in this block.

     public:
      pispisource_impl(int spi_clock, int chunk_size, int bus_num, int device_num);
      ~pispisource_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace hnch
} // namespace gr

#endif /* INCLUDED_HNCH_PISPISOURCE_IMPL_H */

