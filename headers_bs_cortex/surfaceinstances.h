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

#ifndef SurfaceInstanceSet_H
#define SurfaceInstanceSet_H

#include <dspoint.h>
#include <triangle.h>
#include <vector>

class SurfaceInstance {
public:
  DSPoint position;
  std::vector<DSPoint> vertex;
  std::vector<DSPoint> vertexColor;
  std::vector<DSPoint> vertexNormal;
};

class SurfaceInstanceSet {
public:
  SurfaceInstanceSet();
  bool initialize(std::vector<Triangle> &triangles, std::vector<DSPoint> &vertexColors, const size_t nInstances);
  void draw(bool viewLighting=true);
  std::vector<Triangle> triangles;
  std::vector<DSPoint> vertexColors;
  std::vector<SurfaceInstance> instances;
  float scale;
  bool wireframe;
};

#endif
