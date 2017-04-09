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

#ifndef SliceT_H
#define SliceT_H

template <class T>
class SliceT {
public:
  SliceT(const int cx_, const int cy_) : data(0), cx(0), cy(0), slicesize(0), allocsize(0) { create(cx_,cy_); }
  SliceT() : data(0), cx(0), cy(0), slicesize(0), allocsize(0) {}
  ~SliceT() { delete[] data; data = 0; }
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
  T &operator[](const int pos)       { return data[pos]; }
  T  operator[](const int pos) const { return data[pos]; }
  T  operator()(const int x, const int y) const { return data[y*cx+x]; }
  T &operator()(const int x, const int y)       { return data[y*cx+x]; }
  int cx;
  int cy;
  int allocsize;
  int slicesize;
  T *data;
};

#endif
