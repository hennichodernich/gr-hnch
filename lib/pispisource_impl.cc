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
#include "pispisource_impl.h"

namespace gr {
  namespace hnch {

    pispisource::sptr
    pispisource::make(int spi_clock, int chunk_size, int bus_num, int device_num)
    {
      return pispisource::sptr
        (new pispisource_impl(spi_clock, chunk_size,bus_num,device_num));
    }

    /*
     * The private constructor
     */
    pispisource_impl::pispisource_impl(int spi_clock, int chunk_size, int bus_num, int device_num)
      : gr::sync_block("pispisource",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(gr_complex))),
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
        	fprintf(stderr, "pispisource: ");
	        perror(spifilename);
	        throw std::runtime_error("pispisource");
      	}
	
	set_output_multiple(d_chunk_size);

	d_buffer = new uint16_t[d_chunk_size * 2];
	dummybuffer = new uint16_t[d_chunk_size * 2];

	spimode |= (SPI_CPHA);
	/*
         * spi mode
         */
        ret = ioctl(d_fd, SPI_IOC_WR_MODE, &spimode);
        if (ret == -1)
	{
        	fprintf(stderr, "pispisource: ");
	        perror("can't set SPI mode");
	        throw std::runtime_error("pispisource");
      	}

        ret = ioctl(d_fd, SPI_IOC_RD_MODE, &spimode);
        if (ret == -1)
	{
        	fprintf(stderr, "pispisource: ");
	        perror("can't set SPI mode");
	        throw std::runtime_error("pispisource");
      	}

        /*
         * bits per word
         */
        ret = ioctl(d_fd, SPI_IOC_WR_BITS_PER_WORD, &spibits);
        if (ret == -1)
	{
        	fprintf(stderr, "pispisource: ");
	        perror("can't set SPI bits per word");
	        throw std::runtime_error("pispisource");
      	}

        ret = ioctl(d_fd, SPI_IOC_RD_BITS_PER_WORD, &spibits);
        if (ret == -1)
	{
        	fprintf(stderr, "pispisource: ");
	        perror("can't set SPI bits per word");
	        throw std::runtime_error("pispisource");
      	}

	speed = d_spi_clock;

	/*
         * max speed hz
         */
        ret = ioctl(d_fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
        if (ret == -1)
	{
        	fprintf(stderr, "pispisource: can't set SPI speed to %d",speed);
	        perror(" ");
	        throw std::runtime_error("pispisource");
      	}

        ret = ioctl(d_fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
        if (ret == -1)
	{
        	fprintf(stderr, "pispisource: can't set SPI speed to %d",speed);
	        perror(" ");
	        throw std::runtime_error("pispisource");
      	}

	transfer_struct.tx_buf = (__u64) dummybuffer;
	transfer_struct.rx_buf = (__u64) d_buffer;
	transfer_struct.delay_usecs = 0;
	transfer_struct.speed_hz = speed;
	transfer_struct.bits_per_word = spibits;
    }

    /*
     * Our virtual destructor.
     */
    pispisource_impl::~pispisource_impl()
    {
	close(d_fd);
	delete [] d_buffer;
	delete [] dummybuffer;
    }

    int
    pispisource_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      	gr_complex *out = (gr_complex *) output_items[0];
	int ret;
	uint8_t *byte_array_ptr;

      // Do <+signal processing+>
      
	noutput_items = std::min(noutput_items, d_chunk_size);

	int ntogo = noutput_items;

	while(ntogo > 0) {
		int samples_to_get = std::min(ntogo, d_chunk_size);
	       	int bytes_to_get = samples_to_get * 2 * sizeof(uint16_t);

		transfer_struct.len = bytes_to_get;

		ret = ioctl(d_fd, SPI_IOC_MESSAGE(1), &transfer_struct);
		if(ret<1)
		{
            		perror("pispisink: SPI transfer failed");
			break;
		}

        	for(int j = 0; j < samples_to_get; j++) 
		{
			byte_array_ptr = (uint8_t *) &d_buffer[2*j+0];
			float realpart = (((byte_array_ptr[0] * 256.0f) + (byte_array_ptr[1] * 1.0f))/2048.0f) - 1.0f;
			byte_array_ptr = (uint8_t *) &d_buffer[2*j+1];
			float imagpart = (((byte_array_ptr[0] * 256.0f) + (byte_array_ptr[1] * 1.0f))/2048.0f) - 1.0f;
			out[j] = (realpart + 1i*imagpart);
	        }

		ntogo -= samples_to_get;
	}

	return noutput_items - ntogo;

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace hnch */
} /* namespace gr */

