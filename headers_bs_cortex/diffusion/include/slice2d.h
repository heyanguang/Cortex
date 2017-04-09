// Copyright (C) 2016 The Regents of the University of California
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

#ifndef Slide2D_H
#define Slide2D_H

#include <iostream>

template <class T>
class Slice2D {
public:
  Slice2D() : cx(0), cy(0), d(0), allocsize(0)
  {
  }
  ~Slice2D()
  {
    freeUs();
  }
  void freeUs()
  {
    delete[] d;
    allocsize=0;
    d=0;
    cx = 0;
    cy = 0;
  }
  bool setsize(const int cx_, const int cy_)
  {
    const int nElements = cx_ * cy_;
    if (nElements<=allocsize)
    {
      cx = cx_; cy = cy_;
    }
    else
    {
      delete[] d;
      d = new T[nElements];
      if (d)
      {
        cx = cx_; cy = cy_;
        allocsize = nElements;
      }
      else
      {
        std::cerr<<__FILE__<<" : "<<__LINE__<<" Allocation failed."<<std::endl;
        allocsize = 0;
        return false;
      }
    }
    return true;
  }
  T operator()(const int x, const int y) const { return d[y*cx+x]; }
  T &operator()(const int x, const int y) { return d[y*cx+x]; }
  T *begin() { return d; }
  int cx,cy;
private:
  T *d;
  int allocsize;
};

#endif
