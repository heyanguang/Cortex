// Copyright (C) 2016 The Regents of the University of California
//
// Created by David W. Shattuck, Ph.D.
//
// This file is part of PialMesh.
//
// PialMesh is free software; you can redistribute it and/or
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

#ifndef SurfaceExpander_H
#define SurfaceExpander_H

#include <vector>
#include <vol3d.h>
#include <collisionlist.h>

class SurfaceExpander {
public:
  SurfaceExpander() : halt(false), timer(false), verbosity(1), nSteps(20), smoothingConstant(0.1f), stepSize(0.1f), searchRadius(2.0f),
    maximumThickness(10.0f), tissueThreshold(1.1f), firstVertex(0), lastVertex(-1), computeNormals(false),
    tanConstant(0.0f), radConstant(0.0f)
  {
  }
  void step(SILT::Surface &movingSurface, SILT::Surface &initSurface, const Vol3D<float> &volume);
  std::string status;
  bool halt;
  bool timer;
  int verbosity;
  int nSteps;
  float smoothingConstant;
  float stepSize;
  float searchRadius;
  float maximumThickness;
  float tissueThreshold;
  int firstVertex;
  int lastVertex;
  bool computeNormals;
  float tanConstant;
  float radConstant;
  CollisionVolume collisionVolume;
protected:
  std::vector<float> thickness;
};

#endif
