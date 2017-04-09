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

#ifndef SmoothingKernel_H
#define SmoothingKernel_H

#include <cmath>
#include <vector>
#include <numeric>

class SmoothingKernel {
public:
  SmoothingKernel(const int halfWidth=3) : halfWidth(halfWidth), kernel(halfWidth*2+1)
  {
    const size_t kernelSize(kernel.size());
    const float step = (kernelSize-1)/(2.0f*halfWidth);
    const float v = 1.0f;
    float t  =-(float)halfWidth;
    for (size_t i=0; i<kernelSize; i++, t+= step)
      kernel[i] = std::exp(-t*t/(2*v));
    const float sum = std::accumulate(kernel.begin(),kernel.end(),0.0f);
    for (size_t i=0; i<kernelSize; i++)
      kernel[i] /= sum;
  }
  size_t size() const { return kernel.size(); }
  const float &operator[](const size_t i) const { return kernel[i]; }
  const size_t halfWidth;
  std::vector<float> kernel;
};

#endif
