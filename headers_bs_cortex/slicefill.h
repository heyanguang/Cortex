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

#ifndef SliceFill_H
#define SliceFill_H

#include <DS/runlengthsegmenter.h>

class SliceFill {
public:
  template <class T>
  void sliceFill(Vol3D<T> &volume, const IPoint3D point, const int newValue)
  {
    if (point.x<0) return;
    if (point.y<0) return;
    if (point.z<0) return;
    if (point.x>=(int)volume.cx) return;
    if (point.y>=(int)volume.cy) return;
    if (point.z>=(int)volume.cz) return;
    T label = volume(point.x,point.y,point.z);
    Vol3D<uint8> slice;
    Vol3D<VBit> sl2;
    slice.setsize(volume.cx,volume.cy,1);
    const int ss = volume.cx*volume.cy;
    T *v = volume.slice(point.z);
    for (int i=0;i<ss;i++) slice[i] = (v[i]==label) ? 255 : 0;
    sl2.encode(slice);
    fillRLS.segmentFG(sl2);
    int lID = fillRLS.labelID(point.x,point.y,0);
    if (lID>=0)
    {
      RegionInfo *ri = &fillRLS.regionInfo[0];
      const size_t nr = fillRLS.regionInfo.size();
      for (size_t i=0;i<nr;i++)
        ri[i].selected = (ri[i].label==lID) ? 1 : 0;
      fillRLS.label32FG(sl2);
      sl2.decode(slice);
      for (int i=0;i<ss;i++)
        if (slice[i]) v[i] = newValue;
    }
  }
  template <class T>
  void sliceFillXZ(Vol3D<T> &volume, const IPoint3D point, const int newValue)
  {
    if (point.x<0) return;
    if (point.y<0) return;
    if (point.z<0) return;
    if (point.x>=(int)volume.cx) return;
    if (point.y>=(int)volume.cy) return;
    if (point.z>=(int)volume.cz) return;
    T label = volume(point.x,point.y,point.z);
    Vol3D<uint8> slice;
    Vol3D<VBit> sl2;
    slice.setsize(volume.cx,volume.cz,1);
    {
      const int cx=volume.cx;
      const int cz = volume.cz;
      for (int z=0;z<cz;z++)
        for (int x=0;x<cx;x++)
          slice(x,z,0) = (volume(x,point.y,z)==label) ? 255 : 0;
    }
    sl2.encode(slice);
    fillRLS.segmentFG(sl2);
    int lID = fillRLS.labelID(point.x,point.z,0);
    if (lID>=0)
    {
      RegionInfo *ri = &fillRLS.regionInfo[0];
      const size_t nr = fillRLS.regionInfo.size();
      for (size_t i=0;i<nr;i++)
        ri[i].selected = (ri[i].label==lID) ? 1 : 0;
      fillRLS.label32FG(sl2);
      sl2.decode(slice);
      {
        const int cx=volume.cx;
        const int cz = volume.cz;
        for (int z=0;z<cz;z++)
          for (int x=0;x<cx;x++)
            if (slice(x,z,0)) volume(x,point.y,z) = newValue;
      }
    }
  }
  template <class T>
  void sliceFillYZ(Vol3D<T> &volume, const IPoint3D point, const int newValue)
  {
    if (point.x<0) return;
    if (point.y<0) return;
    if (point.z<0) return;
    if (point.x>=(int)volume.cx) return;
    if (point.y>=(int)volume.cy) return;
    if (point.z>=(int)volume.cz) return;
    T label = volume(point.x,point.y,point.z);
    Vol3D<uint8> slice;
    Vol3D<VBit> sl2;
    slice.setsize(volume.cy,volume.cz,1);
    {
      const int cy=volume.cy;
      const int cz = volume.cz;
      for (int z=0;z<cz;z++)
        for (int y=0;y<cy;y++)
          slice(y,z,0) = (volume(point.x,y,z)==label) ? 255 : 0;
    }
    sl2.encode(slice);
    fillRLS.segmentFG(sl2);
    int lID = fillRLS.labelID(point.y,point.z,0);
    if (lID>=0)
    {
      RegionInfo *ri = &fillRLS.regionInfo[0];
      const size_t nr = fillRLS.regionInfo.size();
      for (size_t i=0;i<nr;i++)
        ri[i].selected = (ri[i].label==lID) ? 1 : 0;
      fillRLS.label32FG(sl2);
      sl2.decode(slice);
      {
        const int cy = volume.cy;
        const int cz = volume.cz;
        for (int z=0;z<cz;z++)
          for (int y=0;y<cy;y++)
            if (slice(y,z,0)) volume(point.x,y,z) = newValue;
      }
    }
  }
  template <class T>
  void sliceFillMasked(Vol3D<T> &volume, Vol3D<uint8> &vMask, const IPoint3D point, const int newValue, const bool invertMask=false)
  {
    if (point.x<0) return;
    if (point.y<0) return;
    if (point.z<0) return;
    if (point.x>=(int)volume.cx) return;
    if (point.y>=(int)volume.cy) return;
    if (point.z>=(int)volume.cz) return;
    if (vMask.isCompatible(volume)==false) return;
    if (invertMask)
    {
      if (vMask(point)) return;
    }
    else
    {
      if (!vMask(point)) return;
    }
    T label = volume(point.x,point.y,point.z);
    Vol3D<uint8> slice;
    Vol3D<VBit> sl2;
    slice.setsize(volume.cx,volume.cy,1);
    const int ss = volume.cx*volume.cy;
    T *v = volume.slice(point.z);
    uint8 *m = vMask.slice(point.z);
    if (invertMask)
      for (int i=0;i<ss;i++) slice[i] = ((v[i]==label)&&(m[i]==0)) ? 255 : 0;
    else
      for (int i=0;i<ss;i++) slice[i] = ((v[i]==label)&&(m[i]!=0)) ? 255 : 0;
    sl2.encode(slice);
    fillRLS.segmentFG(sl2);
    int lID = fillRLS.labelID(point.x,point.y,0);
    if (lID>=0)
    {
      RegionInfo *ri = &fillRLS.regionInfo[0];
      const size_t nr = fillRLS.regionInfo.size();
      for (size_t i=0;i<nr;i++)
        ri[i].selected = (ri[i].label==lID) ? 1 : 0;
      fillRLS.label32FG(sl2);
      sl2.decode(slice);
      for (int i=0;i<ss;i++)
        if (slice[i]) v[i] = newValue;
    }
  }
  template <class T>
  void sliceFillMaskedXZ(Vol3D<T> &volume, Vol3D<uint8> &vMask, const IPoint3D point, const int newValue, const bool invertMask=false)
  {
    if (point.x<0) return;
    if (point.y<0) return;
    if (point.z<0) return;
    if (point.x>=(int)volume.cx) return;
    if (point.y>=(int)volume.cy) return;
    if (point.z>=(int)volume.cz) return;
    if (vMask.isCompatible(volume)==false) return;
    if (invertMask)
    {
      if (vMask(point)) return;
    }
    else
    {
      if (!vMask(point)) return;
    }
    T label = volume(point.x,point.y,point.z);
    Vol3D<uint8> slice;
    Vol3D<VBit> sl2;
    slice.setsize(volume.cx,volume.cz,1);
    {
      const int cx=volume.cx;
      const int cz = volume.cz;
      if (invertMask)
        for (int z=0;z<cz;z++)
          for (int x=0;x<cx;x++)
            slice(x,z,0) = ((volume(x,point.y,z)==label)&&!vMask(x,point.y,z)) ? 255 : 0;
      else
        for (int z=0;z<cz;z++)
          for (int x=0;x<cx;x++)
            slice(x,z,0) = ((volume(x,point.y,z)==label)&&vMask(x,point.y,z)) ? 255 : 0;

    }
    sl2.encode(slice);
    fillRLS.segmentFG(sl2);
    int lID = fillRLS.labelID(point.x,point.z,0);
    if (lID>=0)
    {
      RegionInfo *ri = &fillRLS.regionInfo[0];
      const size_t nr = fillRLS.regionInfo.size();
      for (size_t i=0;i<nr;i++)
        ri[i].selected = (ri[i].label==lID) ? 1 : 0;
      fillRLS.label32FG(sl2);
      sl2.decode(slice);
      {
        const int cx=volume.cx;
        const int cz = volume.cz;
        for (int z=0;z<cz;z++)
          for (int x=0;x<cx;x++)
            if (slice(x,z,0)) volume(x,point.y,z) = newValue;
      }
    }
  }
  template <class T>
  void sliceFillMaskedYZ(Vol3D<T> &volume, Vol3D<uint8> &vMask, const IPoint3D point, const int newValue, const bool invertMask=false)
  {
    if (point.x<0) return;
    if (point.y<0) return;
    if (point.z<0) return;
    if (point.x>=(int)volume.cx) return;
    if (point.y>=(int)volume.cy) return;
    if (point.z>=(int)volume.cz) return;
    if (vMask.isCompatible(volume)==false) return;
    if (invertMask)
    {
      if (vMask(point)) return;
    }
    else
    {
      if (!vMask(point)) return;
    }
    T label = volume(point.x,point.y,point.z);
    Vol3D<uint8> slice;
    Vol3D<VBit> sl2;
    slice.setsize(volume.cy,volume.cz,1);
    {
      const int cy=volume.cy;
      const int cz = volume.cz;
      if (invertMask)
        for (int z=0;z<cz;z++)
          for (int y=0;y<cy;y++)
            slice(y,z,0) = ((volume(point.x,y,z)==label)&&!vMask(point.x,y,z)) ? 255 : 0;
      else
        for (int z=0;z<cz;z++)
          for (int y=0;y<cy;y++)
            slice(y,z,0) = ((volume(point.x,y,z)==label)&&vMask(point.x,y,z)) ? 255 : 0;
    }
    sl2.encode(slice);
    fillRLS.segmentFG(sl2);
    int lID = fillRLS.labelID(point.y,point.z,0);
    if (lID>=0)
    {
      RegionInfo *ri = &fillRLS.regionInfo[0];
      const size_t nr = fillRLS.regionInfo.size();
      for (size_t i=0;i<nr;i++)
        ri[i].selected = (ri[i].label==lID) ? 1 : 0;
      fillRLS.label32FG(sl2);
      sl2.decode(slice);
      {
        const int cy = volume.cy;
        const int cz = volume.cz;
        for (int z=0;z<cz;z++)
          for (int y=0;y<cy;y++)
            if (slice(y,z,0)) volume(point.x,y,z) = newValue;
      }
    }
  }
  void floodFillXY(Vol3DBase *b, const IPoint3D point, const int labelID)
  {
    switch (b->typeID())
    {
      case SILT::Uint8  : sliceFill(*(Vol3D<uint8 >*)b,point,labelID); break;
      case SILT::Sint16 : sliceFill(*(Vol3D<uint16>*)b,point,labelID); break;
      case SILT::Uint16 : sliceFill(*(Vol3D<uint16>*)b,point,labelID); break;
      default: break;
    }
  }

  void floodFillXZ(Vol3DBase *b, const IPoint3D point, const int labelID)
  {
    switch (b->typeID())
    {
      case SILT::Uint8  : sliceFillXZ(*(Vol3D<uint8 >*)b,point,labelID); break;
      case SILT::Sint16 : sliceFillXZ(*(Vol3D<uint16>*)b,point,labelID); break;
      case SILT::Uint16 : sliceFillXZ(*(Vol3D<uint16>*)b,point,labelID); break;
      default: break;
    }
  }

  void floodFillYZ(Vol3DBase *b, const IPoint3D point, const int labelID)
  {
    switch (b->typeID())
    {
      case SILT::Uint8  : sliceFillYZ(*(Vol3D<uint8 >*)b,point,labelID); break;
      case SILT::Sint16 : sliceFillYZ(*(Vol3D<uint16>*)b,point,labelID); break;
      case SILT::Uint16 : sliceFillYZ(*(Vol3D<uint16>*)b,point,labelID); break;
      default: break;
    }
  }

  void floodFillMaskedXY(Vol3DBase *b, Vol3D<uint8> &vMask, const IPoint3D point, const int labelID, const bool invertMask=false)
  {
    switch (b->typeID())
    {
      case SILT::Uint8  : sliceFillMasked(*(Vol3D<uint8 >*)b,vMask,point,labelID,invertMask); break;
      case SILT::Sint16 : sliceFillMasked(*(Vol3D<uint16>*)b,vMask,point,labelID,invertMask); break;
      case SILT::Uint16 : sliceFillMasked(*(Vol3D<uint16>*)b,vMask,point,labelID,invertMask); break;
      default: break;
    }
  }

  void floodFillMaskedXZ(Vol3DBase *b, Vol3D<uint8> &vMask, const IPoint3D point, const int labelID, const bool invertMask=false)
  {
    switch (b->typeID())
    {
      case SILT::Uint8  : sliceFillMaskedXZ(*(Vol3D<uint8 >*)b,vMask,point,labelID,invertMask); break;
      case SILT::Sint16 : sliceFillMaskedXZ(*(Vol3D<uint16>*)b,vMask,point,labelID,invertMask); break;
      case SILT::Uint16 : sliceFillMaskedXZ(*(Vol3D<uint16>*)b,vMask,point,labelID,invertMask); break;
      default: break;
    }
  }

  void floodFillMaskedYZ(Vol3DBase *b, Vol3D<uint8> &vMask, const IPoint3D point, const int labelID, const bool invertMask=false)
  {
    switch (b->typeID())
    {
      case SILT::Uint8  : sliceFillMaskedYZ(*(Vol3D<uint8 >*)b,vMask,point,labelID,invertMask); break;
      case SILT::Sint16 : sliceFillMaskedYZ(*(Vol3D<uint16>*)b,vMask,point,labelID,invertMask); break;
      case SILT::Uint16 : sliceFillMaskedYZ(*(Vol3D<uint16>*)b,vMask,point,labelID,invertMask); break;
      default: break;
    }
  }
  Vol3D<uint8> fillmask;
  Vol3D<VBit> fillmaskBit;
  RunLengthSegmenter fillRLS;
};

#endif // SliceFill_H
