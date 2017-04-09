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

#ifndef RENDERTEMPLATES_H
#define RENDERTEMPLATES_H

template <class T, class Operation>
void renderXY(DSImage &bitmap, const Vol3D<T> &vol, const size_t z, Operation operation)
{
  QRgb* pixel = reinterpret_cast<QRgb*>(bitmap.image.bits());
  if ((z<0)||(z>=vol.cz))
  {
    std::fill(pixel,pixel+vol.cx*vol.cy,0);
  }
  else
  {
  const auto cx = vol.cx;
  const auto cy = vol.cy;
    auto *ps = vol.start() + cx*cy * z;
		for (size_t y=0;y<cy;y++)
    {
      auto *p = ps + cx * y;
			for (size_t x=0;x<cx;x++)
      {          
        operation(*pixel++,p[x]);
      }
    }
  }
}

template <class T, class Operation>
void renderXZ(DSImage &bitmap, const Vol3D<T> &vol, const size_t y, Operation operation)
{
  QRgb* pixel = reinterpret_cast<QRgb*>(bitmap.image.bits());
  if ((y<0)||(y>=vol.cy))
  {
    std::fill(pixel,pixel+vol.cx*vol.cz,0);
  }
  else
  {
    const auto cx = vol.cx;
    const auto cy = vol.cy;
    const auto cz = vol.cz;
    auto *ps = vol.start() + cx * y;
		for (size_t z=0;z<cz;z++)
    {
      auto *p = ps + cx * cy * z;
			for (size_t x=0;x<cx;x++)
      {          
          operation(*pixel++,*p++);
      }
    }
  }
}

template <class T, class Operation>
void renderYZ(DSImage &bitmap, const Vol3D<T> &vol, const size_t x, Operation operation)
{
  QRgb* pixel = reinterpret_cast<QRgb*>(bitmap.image.bits());
  if ((x<0)||(x>=vol.cx))
  {
    std::fill(pixel,pixel+vol.cy*vol.cz,0);
  }
  else
  {
    const auto cx = vol.cx;
    const auto cy = vol.cy;
    const auto cz = vol.cz;
    T *ps = vol.start() + x;
		for (size_t z=0;z<cz;z++)
    {
      T *p = ps + cx * cy * z;
			for (size_t y=0;y<cy;y++,p+=cx)
      {
          operation(*pixel++,*p);
      }
    }
  }
}


template <class RenderOp, class Type>
bool renderVolumeT(DSImage &targetBitmap,
                  const Vol3D<Type> &volume, const IPoint3D position,
                  RenderOp &op, DSPoint scaleFactor, Orientation::Code orientation)
{
	const float scale = std::min(volume.rx,std::min(volume.ry,volume.rz));
	switch (orientation)
  {
    case Orientation::XY :
    {
      targetBitmap.resize(volume.cx,volume.cy);
			targetBitmap.setRes(volume.rx,volume.ry,scale);
      const auto slice = size_t((position.z) * scaleFactor.z);
      renderXY(targetBitmap,volume,slice,op);
      break;
    }
    case Orientation::XZ :
    {
      targetBitmap.resize(volume.cx,volume.cz);
			targetBitmap.setRes(volume.rx,volume.rz,scale);
      const auto slice = size_t((position.y) * scaleFactor.y);
      renderXZ(targetBitmap,volume,slice,op); break;
    }
    case Orientation::YZ :
    {
      targetBitmap.resize(volume.cy,volume.cz);
			targetBitmap.setRes(volume.ry,volume.rz,scale);
      const auto slice = size_t((position.x) * scaleFactor.x);
      renderYZ(targetBitmap,volume,slice,op); break;
    }
    default:
        return false;
  }
  return true;
}

#endif // RENDERTEMPLATES_H

