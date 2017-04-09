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


#ifndef VOLUMEPAINTER_H
#define VOLUMEPAINTER_H

#include <labelbrush.h>
class PaintVolume {
public:
  template <class T>
  inline bool operator()(Vol3D<T> &v, const IPoint3D point, LabelBrush &brush, const int brushRadius, bool brush3D, const int labelID)
  {
    brush.resize(brushRadius,brush3D);
    IPoint3D *b = &brush.points[0];
    const size_t n = brush.points.size();
    const int cx = v.cx;
    const int cy = v.cy;
    const int cz = v.cz;
    for (size_t i=0;i<n;i++)
    {
      const IPoint3D p(point.x+b[i].x,point.y+b[i].y,point.z+b[i].z);
      if ((p.x>=0)&&(p.x<cx)&&(p.y>=0)&&(p.y<cy)&&(p.z>=0)&&(p.z<cz))
        v(p.x,p.y,p.z)=labelID;
    }
    return true;
  }
};

class PaintMasked {
public:
  template <class T>
  bool operator()(Vol3D<T> &vol, const Vol3D<uint8> &vMask, const IPoint3D point, LabelBrush &brush, const int brushRadius, bool brush3D,
                  const int labelID, const MaskStates maskState)
  {
    if ((vol.cx!=vMask.cx||vol.cy!=vMask.cy||(vol.cz!=vMask.cz))
        ||(maskState==DrawEverywhere))
    {
      PaintVolume painter;
      painter(vol,point,brush,brushRadius,brush3D,labelID);
      return true;
    }
    brush.resize(brushRadius,brush3D);
    IPoint3D *b = &brush.points[0];
    const size_t n = brush.points.size();
    const int cx = vol.cx;
    const int cy = vol.cy;
    const int cz = vol.cz;
    switch (maskState)
    {
      case DrawInsideMask :
        for (size_t i=0;i<n;i++)
        {
          const IPoint3D p(point.x+b[i].x,point.y+b[i].y,point.z+b[i].z);
          if ((p.x>=0)&&(p.x<cx)&&(p.y>=0)&&(p.y<cy)&&(p.z>=0)&&(p.z<cz))
            if (vMask(p.x,p.y,p.z)) vol(p.x,p.y,p.z)=labelID;
        }
        break;
      case DrawOutsideMask :
        for (size_t i=0;i<n;i++)
        {
          const IPoint3D p(point.x+b[i].x,point.y+b[i].y,point.z+b[i].z);
          if ((p.x>=0)&&(p.x<cx)&&(p.y>=0)&&(p.y<cy)&&(p.z>=0)&&(p.z<cz))
            if (!vMask(p.x,p.y,p.z)) vol(p.x,p.y,p.z)=labelID;
        }
        break;
      default:
        for (size_t i=0;i<n;i++)
        {
          const IPoint3D p(point.x+b[i].x,point.y+b[i].y,point.z+b[i].z);
          if ((p.x>=0)&&(p.x<cx)&&(p.y>=0)&&(p.y<cy)&&(p.z>=0)&&(p.z<cz))
            vol(p.x,p.y,p.z)=labelID;
        }

    }
    return true;
  }
};

class PaintNoClobber {
public:
  template <class T>
  void operator()(Vol3D<T> &vol, const Vol3D<uint8> &/*vMask*/, const IPoint3D point, LabelBrush &brush, const int brushRadius, bool brush3D,
                  const int labelID, const MaskStates /*maskState*/)
  {
    operator()(vol,point,brush,brushRadius,brush3D,labelID);
  }
  template <class T>
  void operator()(Vol3D<T> &vol, const IPoint3D point, LabelBrush &brush, const int brushRadius, bool brush3D, const int labelID)
  {
    brush.resize(brushRadius,brush3D);
    IPoint3D *b = &brush.points[0];
    const size_t n = brush.points.size();
    const int cx = vol.cx;
    const int cy = vol.cy;
    const int cz = vol.cz;
    for (size_t i=0;i<n;i++)
    {
      const IPoint3D p(point.x+b[i].x,point.y+b[i].y,point.z+b[i].z);
      if ((p.x>=0)&&(p.x<cx)&&(p.y>=0)&&(p.y<cy)&&(p.z>=0)&&(p.z<cz))
        if (!vol(p.x,p.y,p.z))
          vol(p.x,p.y,p.z)=labelID;
    }
  }
};

class PaintNoClobberErase {
public:
  template <class T>
  void operator()(Vol3D<T> &vol, const Vol3D<uint8> &/*vMask*/, const IPoint3D point, LabelBrush &brush, const int brushRadius, bool /*brush3D*/,
                  const int labelID, const MaskStates /*maskState*/)
  {
    operator()(vol,point,brush,brushRadius,labelID);
  }
  template <class T>
  void operator()(Vol3D<T> &vol, const IPoint3D point, LabelBrush &brush, const int brushRadius, bool brush3D, const int labelID)
  {
    brush.resize(brushRadius,brush3D);
    IPoint3D *b = &brush.points[0];
    const size_t n = brush.points.size();
    const int cx = vol.cx;
    const int cy = vol.cy;
    const int cz = vol.cz;
    for (size_t i=0;i<n;i++)
    {
      const IPoint3D p(point.x+b[i].x,point.y+b[i].y,point.z+b[i].z);
      if ((p.x>=0)&&(p.x<cx)&&(p.y>=0)&&(p.y<cy)&&(p.z>=0)&&(p.z<cz))
        if (vol(p.x,p.y,p.z)==(T)labelID)
          vol(p.x,p.y,p.z)=0;
    }
  }
};

class PaintMaskedNoClobber {
public:
  template <class T>
  void operator()(Vol3D<T> &vol, const Vol3D<uint8> &vMask, const IPoint3D point, LabelBrush &brush, const int brushRadius, bool brush3D,
                  const int labelID, const MaskStates maskState)
  {
    if (vol.cx!=vMask.cx||vol.cy!=vMask.cy||(vol.cz!=vMask.cz))
    {
      PaintNoClobber painter;
      painter(vol,point,brush,brushRadius,brush3D,labelID);
      return;
    }
    brush.resize(brushRadius,brush3D);
    IPoint3D *b = &brush.points[0];
    const size_t n = brush.points.size();
    const int cx = vol.cx;
    const int cy = vol.cy;
    const int cz = vol.cz;
    switch (maskState)
    {
      case DrawInsideMask :
        for (size_t i=0;i<n;i++)
        {
          const IPoint3D p(point.x+b[i].x,point.y+b[i].y,point.z+b[i].z);
          if ((p.x>=0)&&(p.x<cx)&&(p.y>=0)&&(p.y<cy)&&(p.z>=0)&&(p.z<cz))
            if ((vMask(p)!=0)&&(vol(p)==0))
              vol(p)=labelID;
        }
        break;
      case DrawOutsideMask :
        for (size_t i=0;i<n;i++)
        {
          const IPoint3D p(point.x+b[i].x,point.y+b[i].y,point.z+b[i].z);
          if ((p.x>=0)&&(p.x<cx)&&(p.y>=0)&&(p.y<cy)&&(p.z>=0)&&(p.z<cz))
            if ((vMask(p.x,p.y,p.z)==0)&&(vol(p.x,p.y,p.z)==0))
              vol(p.x,p.y,p.z)=labelID;
        }
        break;
      default:
        for (size_t i=0;i<n;i++)
        {
          const IPoint3D p(point.x+b[i].x,point.y+b[i].y,point.z+b[i].z);
          if ((p.x>=0)&&(p.x<cx)&&(p.y>=0)&&(p.y<cy)&&(p.z>=0)&&(p.z<cz))
            if (vol(p.x,p.y,p.z)==0)
              vol(p.x,p.y,p.z)=labelID;
        }
    }
    return;
  }
};

class PaintMaskedNoClobberErase {
public:
  template <class T>
  void operator()(Vol3D<T> &vol, const Vol3D<uint8> &vMask, const IPoint3D point, LabelBrush &brush, const int brushRadius, bool brush3D,
                  const int labelID, const MaskStates maskState)
  {
    if (vol.cx!=vMask.cx||vol.cy!=vMask.cy||(vol.cz!=vMask.cz))
    {
      PaintNoClobberErase painter;
      painter(vol,point,brush,brushRadius,brush3D,labelID);
      return;
    }
    brush.resize(brushRadius,brush3D);
    IPoint3D *b = &brush.points[0];
    const size_t n = brush.points.size();
    const int cx = vol.cx;
    const int cy = vol.cy;
    const int cz = vol.cz;
    switch (maskState)
    {
      case DrawInsideMask :
        for (size_t i=0;i<n;i++)
        {
          const IPoint3D p(point.x+b[i].x,point.y+b[i].y,point.z+b[i].z);
          if ((p.x>=0)&&(p.x<cx)&&(p.y>=0)&&(p.y<cy)&&(p.z>=0)&&(p.z<cz))
            if ((vMask(p)!=0)&&(vol(p)==(T)labelID))
              vol(p)=0;
        }
        break;
      case DrawOutsideMask :
        for (size_t i=0;i<n;i++)
        {
          const IPoint3D p(point.x+b[i].x,point.y+b[i].y,point.z+b[i].z);
          if ((p.x>=0)&&(p.x<cx)&&(p.y>=0)&&(p.y<cy)&&(p.z>=0)&&(p.z<cz))
            if ((vMask(p.x,p.y,p.z)==0)&&(vol(p.x,p.y,p.z)==(T)labelID))
              vol(p.x,p.y,p.z)=0;
        }
        break;
      default:
        for (size_t i=0;i<n;i++)
        {
          const IPoint3D p(point.x+b[i].x,point.y+b[i].y,point.z+b[i].z);
          if ((p.x>=0)&&(p.x<cx)&&(p.y>=0)&&(p.y<cy)&&(p.z>=0)&&(p.z<cz))
            if (vol(p.x,p.y,p.z)==(T)labelID)
              vol(p.x,p.y,p.z)=0;
        }
    }
    return;
  }
};

template <class PaintStrategy>
void volumePainter(PaintStrategy &paintStrategy,
                     Vol3DBase *vol, Vol3D<uint8> &vMask, const IPoint3D point, LabelBrush &brush, const int brushRadius, bool brush3D,
                     const int labelID, const MaskStates maskState)
{
  if (!vol) return;
  switch (vol->typeID())
  {
    case SILT::Sint8  : paintStrategy(*(Vol3D<sint8> *)vol,vMask,point,brush,brushRadius,brush3D,labelID,maskState); break;
    case SILT::Uint8  : paintStrategy(*(Vol3D<uint8> *)vol,vMask,point,brush,brushRadius,brush3D,labelID,maskState); break;
    case SILT::Sint16 : paintStrategy(*(Vol3D<sint16> *)vol,vMask,point,brush,brushRadius,brush3D,labelID,maskState); break;
    case SILT::Uint16 : paintStrategy(*(Vol3D<uint16> *)vol,vMask,point,brush,brushRadius,brush3D,labelID,maskState); break;
    case SILT::Sint32 : paintStrategy(*(Vol3D<sint32> *)vol,vMask,point,brush,brushRadius,brush3D,labelID,maskState); break;
    case SILT::Uint32 : paintStrategy(*(Vol3D<uint32> *)vol,vMask,point,brush,brushRadius,brush3D,labelID,maskState); break;
    default: break;
  }
}

#endif // VOLUMEPAINTER_H
