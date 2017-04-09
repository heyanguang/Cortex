// Copyright (C) 2016 The Regents of the University of California and
// the University of Southern California
//
// Created by David W. Shattuck, Ph.D.
//
// This file is part of BrainSuite16a1.
//
// BrainSuite16a1 is free software; you can redistribute it and/or
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

#ifndef SliceTemplates_H
#define SliceTemplates_H

#include <vol3ddatatypes.h>

template <class T>
class SliceT {
public:
  SliceT() : data(0), cx(0), cy(0), slicesize(0), allocsize(0) {}
  SliceT(const int cx_, const int cy_)  : data(0), cx(0), cy(0), slicesize(0), allocsize(0) { create(cx_,cy_); }
  ~SliceT() { delete[] data; data = 0; }
  T &operator[](const int n) { return data[n]; }
  T  operator[](const int n) const { return data[n]; }
  bool save(const char *ofname)
  {
    std::ofstream ofile(ofname,std::ios::binary);
    if (!ofile) return false;
    ofile.write((char *)data,slicesize*sizeof(T));
    ofile.close();
    return true;
  }
  void set(const T &t)
  {
    T *d = data;
    const int ss = slicesize;
    for (int i=0;i<ss;i++) d[i] = t;
  }
  void clear()
  {
    memset((char *)data,0,slicesize * sizeof(T));
  }
  void create(int cx_, int cy_)
  {
    cx = cx_;
    cy = cy_;
    slicesize = cx*cy;
    allocate(slicesize);
  }
  void allocate(const int n)
  {
    if (n>allocsize)
    {
      delete[] data;
      allocsize = n;
      data = new T[allocsize];
    }
  }
  T *data;
  int cx;
  int cy;
  int slicesize;
  int allocsize;
};

#endif
