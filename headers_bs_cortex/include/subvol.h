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

#ifndef SubVol3D_H
#define SubVol3D_H

#include <vol3d.h>
#include <DS/timer.h>

template <class T>
class SubVol3D {
public:
  IPoint3D lower,upper,originalSize;
  void create(const Vol3D<T> &vIn, IPoint3D lower_, IPoint3D upper_)
  {
    upper = upper_;
    lower = lower_; // use min/max on each x,y,z
    originalSize=IPoint3D((int)vIn.cx,(int)vIn.cy,(int)vIn.cz);
    const int cx = upper.x - lower.x + 1;
    const int cy = upper.y - lower.y + 1;
    const int cz = upper.z - lower.z + 1;
    vol.setsize(cx,cy,cz);
    vol.copyInfo(vIn);
    vol.set(0);
    const int z0 = (lower.z<0) ? 0 : lower.z;
    const int y0 = (lower.y<0) ? 0 : lower.y;
    const int x0 = (lower.x<0) ? 0 : lower.x;
    const int x1 = (upper.x<(int)vIn.cx) ? upper.x : (int)vIn.cx-1;
    const int y1 = (upper.y<(int)vIn.cy) ? upper.y : (int)vIn.cy-1;
    const int z1 = (upper.z<(int)vIn.cz) ? upper.z : (int)vIn.cz-1;
    for (int z=z0;z<=z1;z++)
    {
      for (int y=y0;y<=y1;y++)
      {
        for (int x=x0;x<=x1;x++)
        {
          vol(x-lower.x,y-lower.y,z-lower.z) = vIn(x,y,z);
        }
      }
    }
  }
  void expand(Vol3D<T> &vOut)
  {
    const int cx = upper.x - lower.x + 1;
    const int cy = upper.y - lower.y + 1;
    const int cz = upper.z - lower.z + 1;
    vOut.setsize(originalSize.x,originalSize.y,originalSize.z);
    vOut.copyInfo(vol);
    vOut.set(0);
    for (int z=0;z<cz;z++)
      for (int y=0;y<cy;y++)
      {
        T *src = vol.start() + vol.index(0,y,z);
        T *dst = vOut.start() + vOut.index(lower.x,y+lower.y,z+lower.z);
        for (int x=0;x<cx;x++)
        {
          *dst++ = *src++;
        }
      }
  }
  Vol3D<T> vol;
};

#endif
