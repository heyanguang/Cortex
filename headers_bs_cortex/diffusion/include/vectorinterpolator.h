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

#ifndef VectorInterpolator_H
#define VectorInterpolator_H

#include <vol3d.h>
#include <eigensystem3x3.h>

template <class Alignment>
class VectorInterpolator {
public:
  static inline DSPoint samplePoint(const DSPoint &p, const DSPoint &direx, const Vol3D<EigenSystem3x3f> &vol)
  {
    const float px = p.x/vol.rx + 0.5f;
    const float py = p.y/vol.ry + 0.5f;
    const float pz = p.z/vol.rz + 0.5f;
    const int x = (int)px;
    const float ax = px - x;
    const int y = (int)py;
    const float ay = py - y;
    const int z = (int)pz;
    const float az = pz - z;
    const int offset = vol.index(x,y,z);
    const EigenSystem3x3f *src = vol.start();
    const int cx = vol.cx;
    const int cy = vol.cy;
    const int ss = cx * cy;
    const int sx = vol.cx-1;
    const int sy = vol.cy-1;
    const int sz = vol.cz-1;
    DSPoint vec;
    if ((x>=0)&&(y>=0)&&(z>0)&&(x<sx)&&(y<sy)&&(z<sz))
    {
      vec = ((1-az)*(
         (1-ay) * ((1-ax)*Alignment::align(src[offset],direx)    + ax*Alignment::align(src[offset+1],direx))
        +(  ay) * ((1-ax)*Alignment::align(src[offset+cx],direx) + ax*Alignment::align(src[offset+cx+1],direx)))
      +(az)*(
         (1-ay) * ((1-ax)*Alignment::align(src[offset+ss],direx)    + ax*Alignment::align(src[offset+ss+1],direx))
        +(  ay) * ((1-ax)*Alignment::align(src[offset+ss+cx],direx) + ax*Alignment::align(src[offset+ss+cx+1],direx))));
    }
    float m = vec.pwr();
    return (m>0) ? vec/sqrtf(m) : 0;
  }
};

#endif
