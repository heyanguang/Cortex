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

#ifndef ComputeRange_H
#define ComputeRange_H

#include <vol3dbase.h>

class ComputeRange {
public:
  static double findRange(Vol3DBase *vol, const float percentile=0.999f);
  static uint8 findPercentileT(Vol3D<uint8> &vol, const float f);
  static uint16 findPercentileT(Vol3D<uint16> &vol, const float f);
  static sint16 findPercentileT(Vol3D<sint16> &vol, const float f);
  static uint32 findMax(Vol3D<uint32> &vol);
  static sint32 findMax(Vol3D<sint32> &vol);
  template <class FloatType> static FloatType findPercentFloat(Vol3D<FloatType> &vol,const float f);
  template <class T> static float findMinT(Vol3D<T> &v);
  static float findMin(Vol3DBase *vol);
};

#endif // ComputeRange_H
