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

#ifndef Operators_H
#define Operators_H

#include <iostream>

template <class T>
class NZ {
public:
  void name() const { std::cout<<"nz"; }
  unsigned char operator()(const T x) const { return (unsigned char)(x!=0); }
};

template <class T>
class GTZ {
public:
  void name() const { std::cout<<"gtz"; }
  unsigned char operator()(const T x) const { return (unsigned char)(x>0); }
};

template <class T>
class EQ {
public:
  void name() const { std::cout<<"eq"; }
  EQ(const T &v) : value(v) {}
  unsigned char operator()(const T x) const { return (unsigned char)(x==value); }
  const T value;
};

template <class T>
class GT {
public:
  void name() const { std::cout<<"gt"; }
  GT(const T &v) : value(v) {}
  unsigned char operator()(const T x) const { return (unsigned char)(x>value); }
  const T value;
};

template <class T>
class LT {
public:
  void name() const { std::cout<<"lt"; }
  LT(const T &v) : value(v) {}
  unsigned char operator()(const T x) const { return (unsigned char)((x!=0)&&(x<value)); }
  const T value;
};

#endif
