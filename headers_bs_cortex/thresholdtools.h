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

#ifndef ThresholdTools_H
#define ThresholdTools_H

#include <vol3d.h>

class ThresholdTools {
public:
  template <class T>
  static bool conditionalThresholdT(Vol3D<uint8> &mask, Vol3D<T> &vol, const double thresholdValueMin, const double thresholdValueMax)
  {
    if (!mask.makeCompatible(vol)) return false;
    const size_t ds = mask.size();
    uint8 *m = mask.start();
    T *v = vol.start();
    for (size_t i=0;i<ds;i++)
    {
      if (m[i])
        m[i] = (v[i]>thresholdValueMin) ? ((v[i]<thresholdValueMax) ? 255 : 0) : 0;
    }
    return true;
  }
  template <class T>
  static bool thresholdT(Vol3D<uint8> &mask, Vol3D<T> &vol, const double thresholdValue)
  {
    if (!mask.makeCompatible(vol)) return false;
    const size_t ds = mask.size();
    uint8 *m = mask.start();
    T *v = vol.start();
    for (size_t i=0;i<ds;i++)
    {
      m[i] = (v[i]>thresholdValue) ? 255 : 0;
    }
    return true;
  }
  static float fractionalAnisotropy(const EigenSystem3x3f &e)
  {
    float d=(e.l0*e.l0+e.l1*e.l1+e.l2*e.l2);

    return (d>0) ? sqrtf(0.5 * (square(e.l0-e.l1)+square(e.l1-e.l2)+square(e.l2-e.l0)) /d) : 0;
  }
  static bool thresholdEig(Vol3D<uint8> &mask, Vol3D<EigenSystem3x3f> &vol, const double thresholdValue)
  {
    if (!mask.makeCompatible(vol)) return false;
    const size_t ds = mask.size();
    uint8 *m = mask.start();
    EigenSystem3x3f *v = vol.start();
    for (size_t i=0;i<ds;i++)
    {
      m[i] = (fractionalAnisotropy(v[i])>thresholdValue) ? 255 : 0;
    }
    return true;
  }
  static bool thresholdRGB(Vol3D<uint8> &mask, Vol3D<rgb8> &vol, const double thresholdValue)
  {
    if (!mask.makeCompatible(vol)) return false;
    const size_t ds = mask.size();
    uint8 *m = mask.start();
    rgb8 *v = vol.start();
    for (size_t i=0;i<ds;i++)
    {
      m[i] = (v[i].r>thresholdValue) ? 255 : 0;
    }
    return true;
  }

  static bool threshold(Vol3D<uint8> &mask, Vol3DBase *vol, const double thresholdValue)
  {
    if (!vol) return false;
    switch (vol->typeID())
    {
      case SILT::Uint8 : return thresholdT(mask,*(Vol3D<uint8 > *)vol,thresholdValue); break;
      case SILT::Sint8 : return thresholdT(mask,*(Vol3D<sint8 > *)vol,thresholdValue); break;
      case SILT::Sint16: return thresholdT(mask,*(Vol3D<sint16> *)vol,thresholdValue); break;
      case SILT::Uint16: return thresholdT(mask,*(Vol3D<uint16> *)vol,thresholdValue); break;
      case SILT::Sint32: return thresholdT(mask,*(Vol3D<sint32> *)vol,thresholdValue); break;
      case SILT::Uint32: return thresholdT(mask,*(Vol3D<uint32> *)vol,thresholdValue); break;
      case SILT::Float32: return thresholdT(mask,*(Vol3D<float32> *)vol,thresholdValue); break;
      case SILT::Float64: return thresholdT(mask,*(Vol3D<float64> *)vol,thresholdValue); break;
      case SILT::RGB8: return thresholdRGB(mask,*(Vol3D<rgb8> *)vol,thresholdValue); break;
      case SILT::Eigensystem3x3f: return thresholdEig(mask,*(Vol3D<EigenSystem3x3f> *)vol,thresholdValue); break;
      default:
        std::cerr<<"unable to mask datatype "<<vol->datatypeName()<<std::endl;
        break;
    }
    return false;
  }
  template <class T>
  static bool thresholdT(Vol3D<uint8> &mask, Vol3D<T> &vol, const double thresholdValueMin, const double thresholdValueMax)
  {
    if (!mask.makeCompatible(vol)) return false;
    const size_t ds = mask.size();
    uint8 *m = mask.start();
    T *v = vol.start();
    for (size_t i=0;i<ds;i++)
    {
      m[i] = (v[i]>thresholdValueMin) ? ((v[i]<thresholdValueMax) ? 255 : 0) : 0;
    }
    return true;
  }

  static bool thresholdRGB(Vol3D<uint8> &mask, Vol3D<rgb8> &vol, const double thresholdValueMin, const double thresholdValueMax)
  {
    if (!mask.makeCompatible(vol)) return false;
    const size_t ds = mask.size();
    uint8 *m = mask.start();
    rgb8 *v = vol.start();
    for (size_t i=0;i<ds;i++)
    {
      m[i] = (v[i].r>thresholdValueMin) ? ((v[i].r<thresholdValueMax) ? 255 : 0) : 0;
    }
    return true;
  }

  static bool threshold(Vol3D<uint8> &mask, Vol3DBase *vol, const double thresholdValueMin, const double thresholdValueMax)
  {
    if (!vol) return false;
    switch (vol->typeID())
    {
      case SILT::Uint8 : return thresholdT(mask,*(Vol3D<uint8 > *)vol,thresholdValueMin,thresholdValueMax); break;
      case SILT::Sint8 : return thresholdT(mask,*(Vol3D<sint8 > *)vol,thresholdValueMin,thresholdValueMax); break;
      case SILT::Sint16: return thresholdT(mask,*(Vol3D<sint16> *)vol,thresholdValueMin,thresholdValueMax); break;
      case SILT::Uint16: return thresholdT(mask,*(Vol3D<uint16> *)vol,thresholdValueMin,thresholdValueMax); break;
      case SILT::Sint32: return thresholdT(mask,*(Vol3D<sint32> *)vol,thresholdValueMin,thresholdValueMax); break;
      case SILT::Uint32: return thresholdT(mask,*(Vol3D<uint32> *)vol,thresholdValueMin,thresholdValueMax); break;
      case SILT::Float32: return thresholdT(mask,*(Vol3D<float32> *)vol,thresholdValueMin,thresholdValueMax); break;
      case SILT::Float64: return thresholdT(mask,*(Vol3D<float64> *)vol,thresholdValueMin,thresholdValueMax); break;
      case SILT::RGB8: return thresholdRGB(mask,*(Vol3D<rgb8> *)vol,thresholdValueMin,thresholdValueMax); break;
      default:
        std::cerr<<"unable to mask datatype."<<std::endl;
        break;
    }
    return false;
  }
  static bool conditionalThreshold(Vol3D<uint8> &mask, Vol3DBase *vol, const double thresholdValueMin, const double thresholdValueMax)
  {
    if (!vol) return false;
    switch (vol->typeID())
    {
      case SILT::Uint8 : return conditionalThresholdT(mask,*(Vol3D<uint8 > *)vol,thresholdValueMin,thresholdValueMax); break;
      case SILT::Sint8 : return conditionalThresholdT(mask,*(Vol3D<sint8 > *)vol,thresholdValueMin,thresholdValueMax); break;
      case SILT::Sint16: return conditionalThresholdT(mask,*(Vol3D<sint16> *)vol,thresholdValueMin,thresholdValueMax); break;
      case SILT::Uint16: return conditionalThresholdT(mask,*(Vol3D<uint16> *)vol,thresholdValueMin,thresholdValueMax); break;
      case SILT::Sint32: return conditionalThresholdT(mask,*(Vol3D<sint32> *)vol,thresholdValueMin,thresholdValueMax); break;
      case SILT::Uint32: return conditionalThresholdT(mask,*(Vol3D<uint32> *)vol,thresholdValueMin,thresholdValueMax); break;
      case SILT::Float32: return conditionalThresholdT(mask,*(Vol3D<float32> *)vol,thresholdValueMin,thresholdValueMax); break;
      case SILT::Float64: return conditionalThresholdT(mask,*(Vol3D<float64> *)vol,thresholdValueMin,thresholdValueMax); break;
      default:
        std::cerr<<"unable to mask datatype."<<std::endl;
        break;
    }
    return false;
  }
};

#endif // ThresholdTools_H
