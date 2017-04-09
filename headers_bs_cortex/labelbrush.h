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

#ifndef LabelBrush_H
#define LabelBrush_H

#include <orientation.h>
#include <dsimage.h>
#include <ipoint3d.h>

class EditDSBitmap : public DSImage {
public:
  QPoint offset;
  Orientation::Code orientation;
};

class LabelBrush
{
public:
  enum { maxBrushSize = 128 } ;
  LabelBrush(Orientation::Code orientation=Orientation::XY, const int size_=0) : use3D(false), size(-1), orientation(orientation) { resize(size_,use3D); }
  EditDSBitmap bitmap;
  bool use3D;
  void resize(int n, bool use3D_)
  {
    if (n<0) n = 0;
    if (n>maxBrushSize) n = maxBrushSize;
    if ((n==size)&&(use3D_==use3D)) return;
    use3D = use3D_;
    size = n;
    bitmap.orientation = orientation;
    bitmap.offset = QPoint(-size,-size);
    bitmap.resize(2*size + 1, 2*size + 1);
    {
      const int np = bitmap.size().width() * bitmap.size().height();
      uint32 *bits = bitmap();
      for (int i=0;i<np;i++) bits[i] = 0;
    }
    int count = 0;
    const float s2 = (size+0.5f)*(size+0.5f);
    uint32 *bits = bitmap();
    if (use3D)
    {
      int nPoints=0;
      for (int z=-size;z<=size;z++)
        for (int y=-size;y<=size;y++)
          for (int x=-size;x<=size;x++)
          {
            if ((z*z+x*x+y*y)<=s2)
            {
              nPoints++;
            }
          }
      points.resize(nPoints);
      for (int z=-size;z<=size;z++)
        for (int y=-size;y<=size;y++)
          for (int x=-size;x<=size;x++)
          {
            if ((z*z+x*x+y*y)<=s2)
            {
              points[count++] = IPoint3D(x,y,z);
              if (z==0) *bits = 0xFFFFFF;
            }
            if (z==0) bits++;
          }
    }
    else
    {
      points.resize((2*size+1)*(2*size+1));
      switch (orientation)
      {
        case Orientation::XY :
          for (int y=-size;y<=size;y++)
            for (int x=-size;x<=size;x++)
            {
              if ((x*x+y*y)<=s2)
              {
                points[count++] = IPoint3D(x,y,0);
                *bits = 0xFFFFFF;
              }
              bits++;
            }
          break;
        case Orientation::XZ :
          for (int y=-size;y<=size;y++)
            for (int x=-size;x<=size;x++)
            {
              if ((x*x+y*y)<=s2)
              {
                points[count++] = IPoint3D(x,0,y);
                *bits = 0xFFFFFF;
              }
              bits++;
            }
          break;
        case Orientation::YZ :
          for (int y=-size;y<=size;y++)
            for (int x=-size;x<=size;x++)
            {
              if ((x*x+y*y)<=s2)
              {
                points[count++] = IPoint3D(0,x,y);
                *bits = 0xFFFFFF;
              }
              bits++;
            }
          break;
        default:
          break;
      }
    }
    points.resize(count);
  }
  std::vector<IPoint3D> points;
  int size;
  const Orientation::Code orientation;
};

#endif // BRUSHQT_H
