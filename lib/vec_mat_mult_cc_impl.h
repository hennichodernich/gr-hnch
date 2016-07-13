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

#ifndef INCLUDED_HNCH_VEC_MAT_MULT_CC_IMPL_H
#define INCLUDED_HNCH_VEC_MAT_MULT_CC_IMPL_H

#include <hnch/vec_mat_mult_cc.h>

namespace gr {
  namespace hnch {

    class vec_mat_mult_cc_impl : public vec_mat_mult_cc
    {
     private:
      std::vector<std::vector<gr_complex> > d_A;
     public:
      vec_mat_mult_cc_impl(std::vector<std::vector<gr_complex> > A);
      ~vec_mat_mult_cc_impl();


      int work(int noutput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace hnch
} // namespace gr

#endif /* INCLUDED_HNCH_VEC_MAT_MULT_CC_IMPL_H */

