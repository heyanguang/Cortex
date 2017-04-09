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

#ifndef Vol3DCrop_H
#define Vol3DCrop_H

#include <vol3d.h>

template <class T>
bool crop(Vol3D<T>&vout, const Vol3D<T>&vin, int xl, int xr, int yl, int yr, int zl, int zr)
{
  const int cx = vin.cx - xl - xr;
  const int cy = vin.cy - yl - yr;
  const int cz = vin.cz - zl - zr;
  vout.setsize(cx,cy,cz);
  vout.copyInfo(vin);
  vout.set(0);
  for (int z=0;z<cz;z++)
  {
    for (int y=0;y<	cy;y++)
    {
      T *s = vin .slice(z + zl) + ((y + yl) * vin.cx) + xl;
      T *d = vout.slice(z) + y * cx;
      memcpy(d,s,cx*sizeof(T));
    }
  }
  return true;
}

template <class T>
bool zeropad(Vol3D<T> &vout, const Vol3D<T>&vin, int xp, int yp, int zp)
{
  vout.setsize(vin.cx+xp*2,vin.cy+yp*2,vin.cz+zp*2);
  vout.copyInfo(vin);
  vout.set(0);
  for (int i=0;i<vin.cz;i++)
  {
    for (int y=0;y<vin.cy;y++)
    {
      T *s = vin .slice(i) + (y * vin.cx);
      T *d = vout.slice(i+zp) + (y + yp) * vout.cx + xp;
      memcpy(d,s,vin.cx*sizeof(T));
    }
  }
  return true;
}

#endif
