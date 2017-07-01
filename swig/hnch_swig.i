/* -*- c++ -*- */

#define HNCH_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "hnch_swig_doc.i"

%{
#include "hnch/simp_vec_map_cc.h"
#include "hnch/vec_mat_mult_cc.h"
#include "hnch/pispisink.h"
#include "hnch/pispisource.h"
#include "hnch/chancoding_bsc_bb.h"
%}


%include "hnch/simp_vec_map_cc.h"
GR_SWIG_BLOCK_MAGIC2(hnch, simp_vec_map_cc);
%include "hnch/vec_mat_mult_cc.h"
GR_SWIG_BLOCK_MAGIC2(hnch, vec_mat_mult_cc);
%include "hnch/pispisink.h"
GR_SWIG_BLOCK_MAGIC2(hnch, pispisink);
%include "hnch/pispisource.h"
GR_SWIG_BLOCK_MAGIC2(hnch, pispisource);
%include "hnch/chancoding_bsc_bb.h"
GR_SWIG_BLOCK_MAGIC2(hnch, chancoding_bsc_bb);
