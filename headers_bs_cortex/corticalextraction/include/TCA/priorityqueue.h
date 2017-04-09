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

#ifndef PriorityQueue_H
#define PriorityQueue_H

#include <vector>

template <class T>
class PriorityQueue {
public:
  PriorityQueue(const int size=1000);
  ~PriorityQueue();
  void push(T v) { d[++n] = v; }
  bool empty() { return (n<1); }
  T remove();
  T popmin();
  std::vector<T> d;
  int n;
};

template <class T>
PriorityQueue<T>::PriorityQueue(const int size) : d(size), n(0)
{
}

template <class T>
PriorityQueue<T>::~PriorityQueue()
{
}

template <class T>
T PriorityQueue<T>::remove()
{
  int max = 1;
  for (int j=2;j<=n;j++)
    if (d[j]>d[max]) max = j;
  T v = d[max];
  d[max] = d[n--];
  return v;
}

template <class T>
T PriorityQueue<T>::popmin()
{
  int min = 1;
  for (int j=2;j<=n;j++)
    if (d[j]<d[min]) min = j;
  T v = d[min];
  d[min] = d[n--];
  return v;
}

#endif
