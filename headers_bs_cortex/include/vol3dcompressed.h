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

#ifndef Vol3DCompressed_H
#define Vol3DCompressed_H

#include <vector>
#include <iostream>
#include <zlib.h>
#include <vol3d.h>

template <class T>
class Vol3DCompressed : public Vol3DBase {
public:
  Vol3DCompressed()
  {
  }
  bool compress(const Vol3D<T> &vIn)
  {
    uLong inputSize = vIn.size() * sizeof(vIn[0]);
    uLong bound = compressBound(inputSize);
    compressedData.resize(bound); // make sure buffer is large enough for the upper bound of the size of the compressed data
    ::compress(&compressedData[0],&bound,(uint8 *)vIn.begin(),inputSize);
    compressedData.resize(bound); // resize the vector to the actual size of the compressed data
    std::vector<uint8>(compressedData).swap(compressedData); // reduce the memory footprint to the actual size of the compressed data
    return true;
  }
  bool uncompress(Vol3D<T> &vOut)
  {
    if (compressedData.size()==0) return false;
    uLong inputSize = vOut.size() * sizeof(vOut[0]);
    ::uncompress((uint8*)vOut.begin(),&inputSize,&compressedData[0],(uLong)compressedData.size());
    return true;
  }
  std::vector<uint8> compressedData;
  bool setsize(const dim_type cx_, const dim_type cy_, const dim_type cz_) { cx=cx_; cy=cy_; cz=cz_; return true; }
  virtual Vol3DBase *duplicate() const { return 0; }
  virtual bool maskWith(const Vol3D<uint8> &/*vMask*/) { return false; } // not implemented for compressed data
  bool operator>>(const Vol3D<T> &vIn) { return compress(vIn); }
  bool operator<<(Vol3D<T> &vOut) { return uncompress(vOut);}
  void release() { cx=cy=cz=0; std::vector<uint8>().swap(compressedData); }
};


#endif
