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

#ifndef Cylinder_H
#define Cylinder_H

#include <cmath>
#include <vector>
#include <dspoint.h>

class Cylinder {
public:
  Cylinder() : nPanels(10) { create(0.1f,10); }
  bool create(const float radius, const int nCylinderPanels)
  {
    nPanels = nCylinderPanels;
    vertices.resize(nPanels*2+2);
    normals.resize(nPanels*2+2);
    colors.resize(nPanels*2+2);
    for (int i=0,idx=0;i<nPanels;i++)
    {
      const float x = std::cos(i*2*(float)M_PI/nCylinderPanels);
      const float y = std::sin(i*2*(float)M_PI/nCylinderPanels);
      vertices[idx] = DSPoint(radius*x,radius*y,0);
      normals[idx++] = DSPoint(x,y,0);
      vertices[idx] = DSPoint(radius*x,radius*y,1);
      normals[idx++] = DSPoint(x,y,0);
    }
    vertices[nPanels*2] = vertices[0];
    normals [nPanels*2] = normals[0];
    vertices[nPanels*2+1] = vertices[1];
    normals [nPanels*2+1] = normals[1];
    return true;
  }
  void twoColor(const DSPoint &a, const DSPoint &b)
  {
    int idx=0;
    for (int i=0;i<nPanels;i++)
    {
      colors[idx++] = a;
      colors[idx++] = b;
    }
    colors[idx++] = a;
    colors[idx++] = b;
  }
  size_t size() { return vertices.size(); }
  std::vector<DSPoint> normals;
  std::vector<DSPoint> vertices;
  std::vector<DSPoint> colors;
  int nPanels;
};

#endif
