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


#ifndef INCLUDED_HNCH_PISPISOURCE_H
#define INCLUDED_HNCH_PISPISOURCE_H

#include <hnch/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace hnch {

    /*!
     * \brief <+description of block+>
     * \ingroup hnch
     *
     */
    class HNCH_API pispisource : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<pispisource> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of hnch::pispisource.
       *
       * To avoid accidental use of raw pointers, hnch::pispisource's
       * constructor is in a private implementation
       * class. hnch::pispisource::make is the public interface for
       * creating new instances.
       */
      static sptr make(int spi_clock, int chunk_size, int bus_num, int device_num);
    };

  } // namespace hnch
} // namespace gr

#endif /* INCLUDED_HNCH_PISPISOURCE_H */

