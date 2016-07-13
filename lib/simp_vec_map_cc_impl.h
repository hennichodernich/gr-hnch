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

#ifndef INCLUDED_HNCH_SIMP_VEC_MAP_CC_IMPL_H
#define INCLUDED_HNCH_SIMP_VEC_MAP_CC_IMPL_H

#include <hnch/simp_vec_map_cc.h>

namespace gr {
  namespace hnch {

    class simp_vec_map_cc_impl : public simp_vec_map_cc
    {
     private:
      size_t d_vlen_in;
      std::vector<size_t> d_mapping;
      gr::thread::mutex d_mutex; // mutex to protect set/work access

     public:
      simp_vec_map_cc_impl(size_t vlen_in, std::vector< size_t > mapping);
      ~simp_vec_map_cc_impl();

      void set_mapping(std::vector< size_t > mapping);

      int work(int noutput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace hnch
} // namespace gr

#endif /* INCLUDED_HNCH_SIMP_VEC_MAP_CC_IMPL_H */

