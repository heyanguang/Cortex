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

#ifndef Collector_H
#define Collector_H
#include <iostream>

template <class T>
class Collector {
public:
  Collector(int n=0);
  ~Collector();
  void reset() { N=1; count=0; }
  int n() const { return (N-1) * blocksize + count; }
  bool add(const T& t);
  template<class S> void dump(S &s)
  {
    for (int i=0;i<N-1;i++)
    {
      T *b = blocks[i];
      for (int j=0;j<blocksize;j++,b) s<<b[j]<<'\n';
    }
    T *b = blocks[N-1];
    for (int j=0;j<count;j++) s<<b[j]<<'\n';
  }
  template<class S> void dumpbin(S &s)
  {
    for (int i=0;i<N-1;i++)
    {
      s.write((char *)blocks[i],blocksize*sizeof(T));
    }
    s.write((char *)blocks[N-1],count*sizeof(T));
  }
  void xport(T* dest) const;
  enum { nblocks=100, defblocksize=200000 };
  const int blocksize;
  T *blocks[nblocks];
  T *block;
  int count;
  int N;
};

template <class T>
Collector<T>::Collector(int n) : blocksize((n>0)?n:defblocksize)
{
  for (int i=0;i<nblocks;i++) blocks[i] = 0;
  block = blocks[0] = new T[blocksize];
  count = 0;
  N = 1;
}

template <class T>
Collector<T>::~Collector()
{
  for (int i=0;i<nblocks;i++)
    delete[] blocks[i];
}

template <class T>
inline bool Collector<T>::add(const T& t)
{
  if (count>=blocksize)
  {
    if (N>=nblocks) return false;
    if (blocks[N]==0) blocks[N] = new T[blocksize];
    block = blocks[N++];
    count = 0;
  }
  block[count++] = t;
  return true;
}

template <class T>
void Collector<T>::xport(T* dest) const
{
  for (int i=0;i<N-1;i++)
  {
    T *b = blocks[i];
    for (int j=0;j<blocksize;j++) *dest++ = b[j];
  }
  T *b = blocks[N-1];
  for (int j=0;j<count;j++) *dest++ = b[j];
}

#endif
