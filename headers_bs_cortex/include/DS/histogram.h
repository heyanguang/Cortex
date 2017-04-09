// Copyright (C) 2016 The Regents of the University of California and
// the University of Southern California
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

#ifndef Histogram_H
#define Histogram_H
#include <vol3d.h>
#include <algorithm>

class HistogramBase {
public:
  HistogramBase() : total(0) {}
  int total;
  enum {nBins = 256};
  int count[nBins];
  int clamp(const float f) { return (f>0) ? ((f<nBins) ? (int)(f) : (nBins-1)) : (0); }
  void clear()
  {
    std::fill(count,count+nBins,0);
  }
};

class Histogram : public HistogramBase {
public:
  Histogram() : HistogramBase() { clear(); }
  void clear()
  {
    for (int i=0;i<nBins;i++) count[i] = 0;
  }
  virtual void compute(const Vol3D<uint8> &v)
  {
    if (v.start()) compute(v.start(),v.size());
  }
  virtual void compute(const Vol3D<uint8> &v, const Vol3D<uint8> &m)
  {
    if ((v.start())&&(m.start())&&(v.isCompatible(m)))
    {
      compute(v.start(),m.start(),v.size());
    }
  }
  virtual void compute(const uint8 *image, int datasize)
  {
    total = datasize;
    for (int h=0;h<256;h++) count[h] = 0;
    for (int i=0;i<datasize;i++) count[image[i]]++;
  }
  virtual void compute(const uint8 *image, uint8 *mask, int datasize)
  {
    total = 0;
    for (int h=0;h<256;h++) count[h] = 0;
    for (int i=0;i<datasize;i++) if (mask[i]) { count[image[i]]++; total++; }
  }
};

#endif
