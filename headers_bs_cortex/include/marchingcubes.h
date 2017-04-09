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

#ifndef MarchingCubes_H
#define MarchingCubes_H

#include <operators.h>
#include <surface.h>
#include <vol3d.h>

class MarchingCubes {
public:
  static const int vertexTable[12][3];
  static const int triangleTable[256][16];
  template <class T>
  bool cubes(Vol3D<T> &vol, SILT::Surface &tess)
  {
    return cubes(vol,tess,NZ<T>());
  }
  template <class T, class Op>
  bool cubes(Vol3D<T> &vol, SILT::Surface &tess, const Op op);
  void rescale(SILT::Surface &dfs, const float rx, const float ry, const float rz);
  std::vector<DSPoint> vertexStack;
};

#endif
