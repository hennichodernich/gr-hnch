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


#ifndef INCLUDED_HNCH_SIMP_VEC_MAP_CC_H
#define INCLUDED_HNCH_SIMP_VEC_MAP_CC_H

#include <hnch/api.h>
#include <vector>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace hnch {

    /*!
     * \brief <+description of block+>
     * \ingroup hnch
     *
     */
    class HNCH_API simp_vec_map_cc : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<simp_vec_map_cc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of hnch::simp_vec_map_cc.
       *
       * To avoid accidental use of raw pointers, hnch::simp_vec_map_cc's
       * constructor is in a private implementation
       * class. hnch::simp_vec_map_cc::make is the public interface for
       * creating new instances.
       */
      static sptr make(size_t vlen_in, std::vector< size_t > mapping);

      virtual void set_mapping(std::vector<size_t> mapping) = 0;
    };

  } // namespace hnch
} // namespace gr

#endif /* INCLUDED_HNCH_SIMP_VEC_MAP_CC_H */

