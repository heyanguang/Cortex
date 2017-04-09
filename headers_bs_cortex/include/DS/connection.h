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

#ifndef Connection_H
#define Connection_H

#include <vector>

class Connection {
public:
  enum { NN=16 };
  Connection() : v(NN), n(0) {  }
  int operator[](const int i) const { return v[i]; }
  int &operator[](const int i) { return v[i]; }
  std::vector<int> v;
  size_t n;
  void reset()
  {
    n = 0;
  }
  void remove(int b)
  {
    int dst = 0;
    for (size_t i=0;i<n;i++)
    {
      if (v[i]!=b) v[dst++]=v[i];
    }
    for (size_t i=dst;i<v.size();i++) v[i]=-1;
    n = dst;
  }
  void insert(int b)
  {
    for (size_t i=0;i<n;i++)
    {
      if (v[i]==b) return;
    }
    if ((n+1)>=v.capacity())
    {
      v.resize(v.capacity()*2);
    }
    v[n++]=b;
  }
};

#endif
