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

#ifndef HARDIRenderer_H
#define HARDIRenderer_H

#include <harditool.h>
#include <surfaceinstances.h>

class HARDIRenderer {
public:
  HARDIRenderer(HARDITool &hardiTool);
  void updateGlyphs(bool recomputeBasis);
  void updateGlyphs(Vol3D<uint8> &vMask, bool recomputeBasis);
  void draw(IPoint3D &pCenter);
  void drawMasked(IPoint3D &point, Vol3D<uint8> &vMask);
  float setScale(float scale);

  SurfaceInstanceSet odfInstancesXY;
  SurfaceInstanceSet odfInstancesXZ;
  SurfaceInstanceSet odfInstancesYZ;
  HARDITool &hardiTool;
  bool drawXY;
  bool drawXZ;
  bool drawYZ;
  IPoint3D pCenter;
  int radius;
  float scale;
  bool dirty;
};

#endif
