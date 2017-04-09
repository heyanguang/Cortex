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

#ifndef FiberRenderer_H
#define FiberRenderer_H

#include <vector>
#include <dspoint.h>
#include <surface.h>
#include <cylinder.h>

class FiberTrack;
class FiberTrackSet;

class FiberRenderer {
public:
	FiberRenderer();
  enum ColorModel { Solid=0, AvgAngle=1, ByAngle=2 };
  bool draw(FiberTrackSet &fiberSet);
  void drawCylinder(DSPoint &p0, DSPoint &p1, DSPoint color, float radius);
  void render(const std::vector<DSPoint> &pointBuffer, DSPoint color, float radius);
  void renderFiberTrack(const FiberTrack &curve, float radius);
  void drawPolyline(const FiberTrack &curve, DSPoint color);
  void drawLineAngleColor(const FiberTrack &curve);
	void rotateCylinder(const DSPoint &d);
	void setup(float radius, int nCylinderPanels);
	Cylinder cylinder;
  ColorModel colorModel;
};

#endif
