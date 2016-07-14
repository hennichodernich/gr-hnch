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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <fcntl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <sys/ioctl.h>
#include <gnuradio/io_signature.h>
#include <volk/volk.h>
#include "pispisink_impl.h"


namespace gr {
  namespace hnch {

    pispisink::sptr
    pispisink::make(int spi_clock, int chunk_size, int bus_num, int device_num)
    {
      return pispisink::sptr
        (new pispisink_impl(spi_clock, chunk_size,bus_num,device_num));
    }

    /*
     * The private constructor
     */
    pispisink_impl::pispisink_impl(int spi_clock, int chunk_size, int bus_num, int device_num)
      : gr::sync_block("pispisink",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(0, 0, 0)),
	d_spi_clock(spi_clock), d_chunk_size(chunk_size), d_bus_num(bus_num), d_device_num(device_num),
	d_fd(-1), d_buffer(0)
    {
	char spifilename[20];
	int ret;
	uint8_t spimode = 0;
	uint8_t spibits = 8;
	uint32_t speed;
	
	snprintf(spifilename,20,"/dev/spidev%d.%d",d_bus_num,d_device_num);
	if((d_fd = open(spifilename, O_WRONLY)) < 0) 
	{
        	fprintf(stderr, "pispisink: ");
	        perror(spifilename);
	        throw std::runtime_error("pispisink");
      	}
	
	set_output_multiple(d_chunk_size);

	d_buffer = new uint32_t[d_chunk_size * 2];
	dummybuffer = new uint32_t[d_chunk_size * 2];

	spimode |= (SPI_CPHA);
	/*
         * spi mode
         */
        ret = ioctl(d_fd, SPI_IOC_WR_MODE, &spimode);
        if (ret == -1)
	{
        	fprintf(stderr, "pispisink: ");
	        perror("can't set SPI mode");
	        throw std::runtime_error("pispisink");
      	}

        ret = ioctl(d_fd, SPI_IOC_RD_MODE, &spimode);
        if (ret == -1)
	{
        	fprintf(stderr, "pispisink: ");
	        perror("can't set SPI mode");
	        throw std::runtime_error("pispisink");
      	}

        /*
         * bits per word
         */
        ret = ioctl(d_fd, SPI_IOC_WR_BITS_PER_WORD, &spibits);
        if (ret == -1)
	{
        	fprintf(stderr, "pispisink: ");
	        perror("can't set SPI bits per word");
	        throw std::runtime_error("pispisink");
      	}

        ret = ioctl(d_fd, SPI_IOC_RD_BITS_PER_WORD, &spibits);
        if (ret == -1)
	{
        	fprintf(stderr, "pispisink: ");
	        perror("can't set SPI bits per word");
	        throw std::runtime_error("pispisink");
      	}

	speed = d_spi_clock;

	/*
         * max speed hz
         */
        ret = ioctl(d_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
        if (ret == -1)
	{
        	fprintf(stderr, "pispisink: can't set SPI speed to %d",speed);
	        perror(" ");
	        throw std::runtime_error("pispisink");
      	}

        ret = ioctl(d_fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
        if (ret == -1)
	{
        	fprintf(stderr, "pispisink: can't set SPI speed to %d",speed);
	        perror(" ");
	        throw std::runtime_error("pispisink");
      	}

	transfer_struct.len = 2 * d_chunk_size * sizeof(uint32_t);
	transfer_struct.tx_buf = (__u64) d_buffer;
	transfer_struct.rx_buf = (__u64) dummybuffer;
	transfer_struct.delay_usecs = 0;
	transfer_struct.speed_hz = speed;
	transfer_struct.bits_per_word = spibits;

	alignment = volk_get_alignment();

	out_real = (float*)volk_malloc(sizeof(float)*d_chunk_size, alignment);
	out_imag = (float*)volk_malloc(sizeof(float)*d_chunk_size, alignment);
	

    }

    /*
     * Our virtual destructor.
     */
    pispisink_impl::~pispisink_impl()
    {
	close(d_fd);
	volk_free(out_real);
	volk_free(out_imag);
	delete [] d_buffer;
	delete [] dummybuffer;
    }

    int
    pispisink_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      	const gr_complex *in = (const gr_complex *) input_items[0];
	int ret;
	uint8_t *byte_array_ptr;
	uint16_t integered_value;


	for(int i = 0; i < noutput_items; i += d_chunk_size) 
	{
		volk_32fc_deinterleave_32f_x2(out_real, out_imag, in, d_chunk_size);

        	for(int j = 0; j < d_chunk_size; j++) 
		{
			integered_value = (uint16_t) ((out_real[j]+1)*2047.0);
			byte_array_ptr = (uint8_t *) &d_buffer[2*j+0];
			byte_array_ptr[0] = ((integered_value >> 8) & 0xff) | 0x10;
			byte_array_ptr[1] = integered_value & 0xff;
			byte_array_ptr[2] = 0;
			byte_array_ptr[3] = 0;
			integered_value = (uint16_t) ((out_imag[j]+1)*2047.0);
			byte_array_ptr = (uint8_t *) &d_buffer[2*j+1];
			byte_array_ptr[0] = ((integered_value >> 8) & 0xff) | 0x40;
			byte_array_ptr[1] = integered_value & 0xff;
			byte_array_ptr[2] = 0;
			byte_array_ptr[3] = 0;

			//d_buffer[2*j+0] = (((uint32_t) ((out_real[j]+1)*2047.0)) | 0x1000) << 16;
			//d_buffer[2*j+1] = (((uint32_t) ((out_imag[j]+1)*2047.0)) | 0x4000) << 16;
	        }
	 	in += d_chunk_size;

		ret = ioctl(d_fd, SPI_IOC_MESSAGE(1), &transfer_struct);
		if(ret<1)
		{
            		perror("pispisink: SPI transfer failed");
			throw std::runtime_error("internal error");
		}
        }

      // Do <+signal processing+>

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace hnch */
} /* namespace gr */

