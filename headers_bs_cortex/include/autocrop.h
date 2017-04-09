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

#ifndef AutoCrop_H
#define AutoCrop_H

#include <subvol.h>

template <class T>
void extents(const Vol3D<T> &vMask, IPoint3D &lower, IPoint3D &upper)
{
  const int cx = (int)vMask.cx;
  const int cy = (int)vMask.cy;
  const int cz = (int)vMask.cz;
  const int ss = cx*cy;
  lower = IPoint3D(-1,-1,-1);
  upper = IPoint3D(-1,-1,-1);
  for (int z=0;z<cz;z++)
  {
    T *start = vMask.slice(z);
    for (int i=0;i<ss;i++) if (start[i]) { lower.z = z; break; }
  }
  for (int z=cz-1;z>=0;z--)
  {
    T *start = vMask.slice(z);
    for (int i=0;i<ss;i++) if (start[i]) { upper.z = z; break; }
  }
  for (int x=0;x<cx;x++)
    for (int z=0;z<cz;z++)
      for (int y=0;y<cy;y++)
        if (vMask(x,y,z)) { lower.x = x; break; }

  for (int x=cx-1;x>=0;x--)
    for (int z=0;z<cz;z++)
      for (int y=0;y<cy;y++)
        if (vMask(x,y,z)) { upper.x = x; break; }

  for (int y=0;y<cy;y++)
    for (int z=0;z<cz;z++)
      for (int x=0;x<cx;x++)
        if (vMask(x,y,z)) { lower.y = y; break; }

  for (int y=cy-1;y>=0;y--)
    for (int z=0;z<cz;z++)
      for (int x=0;x<cx;x++)
        if (vMask(x,y,z)) { upper.y = y; break; }
}


template <class T>
void autocrop(SubVol3D<T> &sv, const Vol3D<T> &vIn, int pad)
{
  IPoint3D upper,lower;
  IPoint3D delta(pad,pad,pad);
  extents(vIn,upper,lower);
  upper += delta;
  lower -= delta;
  if (lower.x<0) lower.x=0;
  if (lower.y<0) lower.y=0;
  if (lower.z<0) lower.z=0;
  if (upper.x>(int)(vIn.cx-1)) upper.x=(int)vIn.cx-1;
  if (upper.y>(int)(vIn.cy-1)) upper.y=(int)vIn.cy-1;
  if (upper.z>(int)(vIn.cz-1)) upper.z=(int)vIn.cz-1;
  sv.create(vIn,lower,upper);
}


#endif
