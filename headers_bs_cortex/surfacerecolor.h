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

#ifndef SURFACERECOLOR_H
#define SURFACERECOLOR_H

#include <surface.h>
#include <vol3d.h>

class Vol3DBase;
class RangeLUTOp;

class SurfaceRecolor
{
public:
  SurfaceRecolor();
  template <class VecT>
  static float quantify(VecT &curvature, const float percent=0.95f);
  static bool recolorSurfaceWithCurvature(SILT::Surface *surface);
  static bool recolorSurfaceWithVertexLabels(SILT::Surface *surface);
  template <class T>
  static bool recolorSurfaceWithVolumeLabels(SILT::Surface &surface, Vol3D<T> &vLabel);
  static bool recolorSurfaceWithVolumeLabels(SILT::Surface *surface, Vol3DBase *vLabel);
  template <class T>
  static bool colorSurfaceWithScaledImage_T(SILT::Surface &dfs, Vol3D<T> &vColor, const RangeLUTOp &op);
  static bool colorSurfaceWithScaledImage(SILT::Surface &dfs, Vol3DBase *base, const RangeLUTOp &op);
};

#endif // SURFACERECOLOR_H
