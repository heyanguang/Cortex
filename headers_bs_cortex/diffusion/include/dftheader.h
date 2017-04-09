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

#ifndef DFTHeader_H
#define DFTHeader_H

#include <vol3ddatatypes.h>
#include <iostream>
#define BSTDFT "DFT_LE\0\0"

class Version {
public:
  Version(const uint8 a_=1, const uint8 b_=0, const uint8 c_=0, const uint8 d_=0) :
    a(a_), b(b_), c(c_), d(d_) { }
  uint8 a,b,c,d;
  uint32 hex() const { return a*0x01000000+b*0x010000+c*0x100+d; }
};

inline std::ostream &operator<<(std::ostream &s, Version &v)
{
  return s<<(int)v.a<<'.'<<(int)v.b<<'.'<<(int)v.c<<'.'<<(int)v.d;
}

class DFTHeader {
// Fiber Track Header
// curves are stored in real world coordinates.
public:
  DFTHeader() :
    version(1,0,0,3),
    hdrsize(sizeof(DFTHeader)),
    dataStart(0),
    mdoffset(0),
    pdoffset(0),
    nTracks(0),
    seedPoints(0) // if present, nTracks
  {
    for (std::size_t i=0;i<sizeof(magic);i++)
      magic[i]=BSTDFT[i];
    std::fill_n(padding,sizeof(padding),0);
  }
  char magic[8];			//  0 -  7
  Version version;    //  8 - 11
  sint32	hdrsize;		// 12 - 15
  sint32   dataStart;	// 16 - 19 start of contour data
  sint32	mdoffset;		// 20 - 23
  sint32	pdoffset;		// 24 - 27 [ unused ]
  uint32  nTracks;		// 28 - 31
  uint64  seedPoints;	// 32 - 39 offset to seed point indices
  char	padding[24];	// 40 - 63 (header is now 64 bytes, allowing for more extensions in the future)
};

#endif
