// Copyright (C) 2016 The Regents of the University of California
//
// Created by David W. Shattuck, Ph.D.
//
// This file is part of Vol3D.
//
// Vol3D is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; version 2.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
// USA.
//

#ifndef HistogramSmoother_H
#define HistogramSmoother_H

#include <numeric>
#include "smoothingkernel.h"

class HistogramSmoother {
public:
  enum { HalfWidth=3 };
  HistogramSmoother() : kernel(HalfWidth)
  {
  }
  ~HistogramSmoother() { }
  void smooth(std::vector<float> &hSmooth, std::vector<float> &h) const;
  void smoothNew(std::vector<float> &hSmooth, std::vector<float> &h) const;
  SmoothingKernel kernel;
};

inline void convolveSame(std::vector<float> &hOut, const std::vector<float> &hIn, const std::vector<float> &kernel)
{
  hOut.resize(hIn.size());
  std::fill(hOut.begin(),hOut.end(),0.0f);
  const size_t halfWidth=kernel.size()/2;
  for (size_t n=0;n<halfWidth;n++)
  {
    hOut[n] = std::inner_product(kernel.begin()+n,kernel.end(),hIn.begin(),0.0f);
  }
  for (size_t n=halfWidth;n<hIn.size()-halfWidth;n++)
  {
    hOut[n] = std::inner_product(kernel.begin(),kernel.end(),hIn.begin()+n-halfWidth,0.0f);
  }
  for (size_t n=hIn.size()-halfWidth;n<hIn.size();n++)
  {
    hOut[n] = std::inner_product(kernel.begin(),kernel.begin()+(hIn.size()-n),hIn.begin()+n-halfWidth,0.0f);
  }
}

inline void HistogramSmoother::smoothNew(std::vector<float> &hSmooth, std::vector<float> &h) const
// convolves h with kernel, returns central region of convolution with same size as h
// note that this is for a symmetric kernel
{
  convolveSame(hSmooth,h,kernel.kernel);
}

inline void HistogramSmoother::smooth(std::vector<float> &hSmooth, std::vector<float> &h) const
// convolves h with kernel, returns central region of convolution with same size as h
// note that this is for a symmetric kernel
{
  hSmooth.resize(h.size());
  std::fill(hSmooth.begin(),hSmooth.end(),0.0f);
  const int halfWidth=(int)kernel.halfWidth;
  for (size_t n=0;n<kernel.halfWidth;n++)
  {
    for (int k=-(int)n;k<=halfWidth;k++)
    {
      hSmooth[n] += h[k+n] * kernel[k+halfWidth];
    }
  }
  for (size_t n=halfWidth;n<h.size()-halfWidth;n++)
  {
    for (int k=-halfWidth;k<=halfWidth;k++)
    {
      hSmooth[n] += h[k+n] * kernel[k+halfWidth];
    }
  }
  for (size_t n=h.size()-halfWidth;n<h.size();n++)
  {
    const int stop=(int)(h.size()-n-1);
    for (int k=-halfWidth;k<=stop;k++)
    {
      hSmooth[n] += h[k+n] * kernel[k+halfWidth];
    }
  }
}

#endif
