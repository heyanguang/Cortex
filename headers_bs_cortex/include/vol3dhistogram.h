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

#ifndef Vol3DHistogram_H
#define Vol3DHistogram_H

#include <vol3d.h>
#include <vector>
#include <limits.h>

class Vol3DHistogram {
public:
  inline int typemin(const uint8  &) { return 0; }
  inline int typemin(const uint16 &) { return 0; }
  inline int typemin(const sint8 &) { return SCHAR_MIN; }
  inline int typemin(const sint16 &) { return SHRT_MIN; }

  inline int typemax(const uint8  &) { return UCHAR_MAX; }
  inline int typemax(const uint16 &) { return USHRT_MAX; }
  inline int typemax(const sint8 &) { return SCHAR_MIN; }
  inline int typemax(const sint16 &) { return SHRT_MAX; }
  int operator[](int n) const
  {
    return count[n - tmin];
  }
  template <class T> void compute(Vol3D<T> &v)
  {
    tmin = typemin(v.start()[0]);
    tmax = typemax(v.start()[0]);
    count.resize(tmax - tmin + 1);
    std::fill(count.begin(),count.end(),0);
    auto *map = &count[0] - tmin;
    const size_t ds = v.size();
    auto *d = v.start();
    for (size_t i=0;i<ds;i++) map[d[i]]++;
  }
  template <class T> void computeMasked(Vol3D<T> &v, Vol3D<uint8> &vMask)
  {
    tmin = typemin(v.start()[0]);
    tmax = typemax(v.start()[0]);
    count.resize(tmax - tmin + 1);
    std::fill(count.begin(),count.end(),0);
    auto *map = &count[0] - tmin;
    const auto ds = v.size();
    auto *d = v.start();
    for (size_t i=0;i<ds;i++)
      if (vMask[i])
        map[d[i]]++;
  }
  bool compute(Vol3DBase *volume)
  {
    switch (volume->typeID())
    {
      case SILT::Uint8 : compute(*(Vol3D<uint8>*)volume); break;
      case SILT::Sint8 : compute(*(Vol3D<sint8>*)volume); break;
      case SILT::Uint16 : compute(*(Vol3D<uint16>*)volume); break;
      case SILT::Sint16 : compute(*(Vol3D<sint16>*)volume); break;
      case SILT::Uint32 : compute(*(Vol3D<uint16>*)volume); break;
      case SILT::Sint32 : compute(*(Vol3D<sint16>*)volume); break;
      default:
        std::cerr<<"Datatype of is not supported for this operation."<<std::endl;
        return false;
    }
    return true;
  }
  bool computeMasked(Vol3DBase *volume, Vol3D<uint8> &vMask)
  {
    switch (volume->typeID())
    {
      case SILT::Uint8 : computeMasked(*(Vol3D<uint8>*)volume,vMask); break;
      case SILT::Sint8 : computeMasked(*(Vol3D<sint8>*)volume,vMask); break;
      case SILT::Uint16 : computeMasked(*(Vol3D<uint16>*)volume,vMask); break;
      case SILT::Sint16 : computeMasked(*(Vol3D<sint16>*)volume,vMask); break;
      default:
        std::cerr<<"Datatype of is not supported for this operation."<<std::endl;
        return false;
    }
    return true;
  }
  std::vector<size_t> count;
  int tmin; // type minimum
  int tmax; // type maximum
};

#endif
