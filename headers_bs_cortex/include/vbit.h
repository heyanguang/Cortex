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

#ifndef VBit_H
#define VBit_H

#include <vol3d.h>
#include <DS/codec32.h>

class VBit {
public:
  uint32 data; // place holder
};

template<> inline Vol3DBase::dim_type Vol3D<VBit>::size() const
{
  return wordsPerLine(cx) * cy * cz;
}

template<> inline bool Vol3D<VBit>::maskWith(const Vol3D<uint8> &vMask)
{
  if (isCompatible(vMask)==false) return false;
  return true;
}

template<> inline bool Vol3D<VBit>::copy(const Vol3D<VBit> &vSource)
{
  if (!makeCompatible(vSource)) return false;
  const	int ds = size();
  uint32 *dst = raw32();
  const uint32 *src = vSource.raw32();
  for (int i=0;i<ds;i++) dst[i] = src[i];
  return true;
}

inline bool setDiff(Vol3D<VBit> &dst, Vol3D<VBit> &src)
{
  if (dst.isCompatible(src))
  {
    int ds = dst.size();
    uint32 *d = dst.raw32();
    uint32 *s = src.raw32();
    for (int i=0;i<ds;i++) d[i] ^= (d[i]&s[i]);
    return true;
  }
  else
    return false;
}

template<> inline int Vol3D<VBit>::analyzeTypeID() const { return DT_BINARY; }
template<> inline SILT::DataType Vol3D<VBit>::typeID() const { return SILT::Unknown; }

template<> inline bool Vol3D<VBit>::write(std::string /* ofname */)
{
  std::cerr<<"writing of Vol3D<VBit> is not currently implemented."<<std::endl;
  return false;
}

template<> inline bool Vol3D<VBit>::encode(const Vol3D<uint8> &mask)
{
  if (makeCompatible(mask)==false) return false;
  description = mask.description;
  auto wpl = (cx/32);
  if (wpl*32 != cx) wpl++;
  const auto nElements = wpl * cy * cz;
  memset(raw32(),0,nElements);
  Codec32::encode(mask.start(),raw32(),cx,cy,cz);
  return true;
}

template<> inline bool Vol3D<VBit>::decode(Vol3D<uint8> &mask)
{
  if (mask.makeCompatible(*this)==false) return false;
  mask.description = description;
  Codec32::decode(raw32(),mask.start(),cx,cy,cz);
  return true;
}

template<> inline bool Vol3D<VBit>::setsize(const dim_type cx_, const dim_type cy_, const dim_type cz_)
{
  auto wpl = (cx_/32);
  if (wpl*32 != cx_) wpl++;
  const auto nElements = wpl * cy_ * cz_;
  if (nElements<allocsize)
  {
    cx = cx_;
    cy = cy_;
    cz = cz_;
  }
  else
  {
    delete[] data;
    data = (VBit *)(new uint32[nElements]);
    if (data)
    {
      cx = cx_;
      cy = cy_;
      cz = cz_;
      allocsize = nElements;
    }
    else
    {
      allocsize = 0;
      return false;
    }
  }
  return true;
}

// move to vBit
inline bool opAnd(Vol3D<VBit> &dst, Vol3D<VBit> &src)
{
  if (dst.isCompatible(src))
  {
    int ds = dst.size();
    uint32 *d = dst.raw32();
    uint32 *s = src.raw32();
    for (int i=0;i<ds;i++) d[i] &= s[i];
    return true;
  }
  else
    return false;
}

inline bool opAnd(Vol3D<uint8> &dst, Vol3D<uint8> &src)
{
  if (dst.isCompatible(src))
  {
    int ds = dst.size();
    uint8 *d = dst.start();
    uint8 *s = src.start();
    for (int i=0;i<ds;i++) d[i] &= s[i];
    return true;
  }
  else
    return false;
}

inline bool copy(Vol3D<VBit> &dst, Vol3D<VBit> &src)
{
  if (dst.makeCompatible(src))
  {
    int ds = dst.size();
    uint32 *d = dst.raw32();
    uint32 *s = src.raw32();
    for (int i=0;i<ds;i++) d[i] = s[i];
    return true;
  }
  else
    return false;
}

inline bool opOr(Vol3D<VBit> &dst, const Vol3D<VBit> &src)
{
  if (dst.isCompatible(src))
  {
    int ds = dst.size();
    uint32 *d = dst.raw32();
    uint32 *s = src.raw32();
    for (int i=0;i<ds;i++) d[i] |= s[i];
    return true;
  }
  else
    return false;
}

inline bool opAnd(Vol3D<VBit> &dst, const Vol3D<VBit> &src)
{
  if (dst.isCompatible(src))
  {
    int ds = dst.size();
    uint32 *d = dst.raw32();
    uint32 *s = src.raw32();
    for (int i=0;i<ds;i++) d[i] &= s[i];
    return true;
  }
  else
    return false;
}

inline bool setDifference(Vol3D<VBit> &dst, const Vol3D<VBit> &src)
// computes dst = dst \ src
{
  if (dst.isCompatible(src))
  {
    int ds = dst.size();
    uint32 *d = dst.raw32();
    uint32 *s = src.raw32();
    for (int i=0;i<ds;i++) d[i] &= (d[i] ^ s[i]);
    return true;
  }
  else
    return false;
}

#endif
