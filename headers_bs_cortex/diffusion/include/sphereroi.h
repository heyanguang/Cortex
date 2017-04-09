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

#ifndef SphereROI_H
#define SphereROI_H

#include <dspoint.h>
#include <ipoint3d.h>

class SphereROI {
public:
  SphereROI() : radius(10.0f), color(1,1,1), active(false), include(true), andop(true) {}
  float radius;
  DSPoint color;
  IPoint3D voxelPosition;
  bool active;
  bool include;
  bool andop;
};

#endif


