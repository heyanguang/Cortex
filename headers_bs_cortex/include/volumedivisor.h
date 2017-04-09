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

#ifndef VolumeDivisor_H
#define VolumeDivisor_H

#include <limits.h>

class VolumeDivisor {
public:
  template <class DestT, class FloatT> static inline DestT divide(const DestT &dest, const FloatT &f)
  {
    if (f==0) return 0;
    return (DestT)(dest/f);
  }
  template <class FloatT> static inline sint8 divide(const sint8 &dest, const FloatT &f)
  {
    if (f==0) return 0;
    const float rv = dest/f;
    return (rv<CHAR_MAX) ? (sint8)rv : CHAR_MAX;
  }
  template <class FloatT> static inline sint16 divide(const sint16 &dest, const FloatT &f)
  {
    if (f==0) return 0;
    const float rv = dest/f;
    return (rv<SHRT_MAX) ? (sint16)rv : SHRT_MAX;
  }
  template <class FloatT> static inline sint32 divide(const sint32 &dest, const FloatT &f)
  {
    if (f==0) return 0;
    const float rv = dest/f;
    return (rv<INT_MAX) ? (sint32)rv : INT_MAX;
  }
  template <class FloatT> static inline uint8 divide(const uint8 &dest, const FloatT &f)
  {
    if (f==0) return 0;
    const float rv = dest/f;
    return (rv>0) ? ((rv<UCHAR_MAX) ? (uint8)rv : UCHAR_MAX) : 0;
  }
  template <class FloatT> static inline uint16 divide(const uint16 &dest, const FloatT &f)
  {
    if (f==0) return 0;
    const float rv = dest/f;
    return (rv>0) ? ((rv<USHRT_MAX) ? (uint16)rv : USHRT_MAX) : 0;
  }
  template <class FloatT> static inline uint32 divide(const uint32 &dest, const FloatT &f)
  {
    if (f==0) return 0;
    const float rv = dest/f;
    return (rv>0) ? ((rv<INT_MAX) ? (uint32)rv : INT_MAX) : 0;
  }
  template <class FloatT, class T>
  static bool divideByT(Vol3D<T> &vIn, Vol3D<FloatT> &vSpline)
  {
    if (!vIn.dimensionsMatch(vSpline))
    {
      std::cerr<<"dimensions do not match"<<std::endl;
      return false;
    }
    const int ds = vIn.size();
    for (int i=0;i<ds;i++)
    {
      vIn[i] = divide(vIn[i],vSpline[i]);
    }
    return true;
  }
  template <class FloatT, class T>
  static bool divideByT(Vol3D<T> &vIn, Vol3D<FloatT> &vSpline, Vol3D<uint8> &vMask)
  {
    if (!vIn.dimensionsMatch(vSpline))
    {
      std::cerr<<"dimensions do not match"<<std::endl;
      return false;
    }
    if (!vIn.dimensionsMatch(vMask))
    {
      std::cerr<<"mask dimensions do not match"<<std::endl;
    }
    const int ds = vIn.size();
    for (int i=0;i<ds;i++)
    {
      vIn[i] = vMask[i] ? divide(vIn[i],vSpline[i]) : 0;
    }
    return true;
  }
  template <class FloatT>
  static bool divideBy(Vol3DBase *vIn, Vol3D<FloatT> &vSpline)
  {
    switch (vIn->typeID())
    {
      case SILT::Uint8:   return divideByT(*(Vol3D<uint8> *)vIn,vSpline); break;
      case SILT::Sint8:   return divideByT(*(Vol3D<sint8> *)vIn,vSpline); break;
      case SILT::Uint16:  return divideByT(*(Vol3D<uint16> *)vIn,vSpline); break;
      case SILT::Sint16:  return divideByT(*(Vol3D<sint16> *)vIn,vSpline); break;
      case SILT::Uint32:  return divideByT(*(Vol3D<uint32> *)vIn,vSpline); break;
      case SILT::Sint32:  return divideByT(*(Vol3D<sint32> *)vIn,vSpline); break;
      case SILT::Float32: return divideByT(*(Vol3D<float32> *)vIn,vSpline); break;
      case SILT::Float64: return divideByT(*(Vol3D<float64> *)vIn,vSpline); break;
      default:
        std::cerr<<"cannot process data of type "<<vIn->datatypeName();
        return false;
    }
  }
  template <class FloatT>
  static bool divideByMasked(Vol3DBase *vIn, Vol3D<FloatT> &vSpline, Vol3D<uint8> &vMask)
  {
    switch (vIn->typeID())
    {
      case SILT::Uint8:   return divideByT(*(Vol3D<uint8> *)vIn,vSpline,vMask); break;
      case SILT::Sint8:   return divideByT(*(Vol3D<sint8> *)vIn,vSpline,vMask); break;
      case SILT::Uint16:  return divideByT(*(Vol3D<uint16> *)vIn,vSpline,vMask); break;
      case SILT::Sint16:  return divideByT(*(Vol3D<sint16> *)vIn,vSpline,vMask); break;
      case SILT::Uint32:  return divideByT(*(Vol3D<uint32> *)vIn,vSpline,vMask); break;
      case SILT::Sint32:  return divideByT(*(Vol3D<sint32> *)vIn,vSpline,vMask); break;
      case SILT::Float32: return divideByT(*(Vol3D<float32> *)vIn,vSpline,vMask); break;
      case SILT::Float64: return divideByT(*(Vol3D<float64> *)vIn,vSpline,vMask); break;
      default:
        std::cerr<<"cannot process data of type "<<vIn->datatypeName();
        return false;
    }
  }
};

#endif
