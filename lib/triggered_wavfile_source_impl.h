/* -*- c++ -*- */
/*
 * Copyright 2004,2008,2013 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_HNCH_TRIGGERED_WAVFILE_SOURCE_IMPL_H
#define INCLUDED_HNCH_TRIGGERED_WAVFILE_SOURCE_IMPL_H

#include <hnch/triggered_wavfile_source.h>
#include <cstdio> // for FILE

namespace gr {
namespace hnch {

class triggered_wavfile_source_impl : public triggered_wavfile_source
{
private:
    FILE* d_fp;
    bool d_retrigger;

    bool d_finished;
    unsigned d_sample_rate;
    int d_nchans;
    int d_bytes_per_sample;
    int d_first_sample_pos;
    unsigned d_samples_per_chan;
    unsigned d_sample_idx;
    int d_normalize_shift;
    int d_normalize_fac;
    const pmt::pmt_t d_port;

    /*!
     * \brief Convert an integer sample value to a float value within [-1;1]
     */
    float convert_to_float(short int sample);

public:
    triggered_wavfile_source_impl(const char* filename, bool retrigger);
    ~triggered_wavfile_source_impl();
    
    void clr_finished(pmt::pmt_t msg);

    unsigned int sample_rate() const { return d_sample_rate; };

    int bits_per_sample() const { return d_bytes_per_sample * 8; };

    int channels() const { return d_nchans; };

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} /* namespace hnch */
} /* namespace gr */

#endif /* INCLUDED_HNCH_TRIGGERED_WAVFILE_SOURCE_IMPL_H */
