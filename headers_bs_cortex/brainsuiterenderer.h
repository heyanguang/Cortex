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

#ifndef BrainSuiteRenderer_H
#define BrainSuiteRenderer_H

#include <vol3d.h>
#include <brainsuitesettings.h>
#include <surface.h>

class FiberTrackSet;
class ProtocolCurveSet;
class SurfaceAlpha;

class BrainSuiteRenderer {
// provides OpenGL 3D functionality
public:
  static void initialize();
  static void drawCrossHairs(const Vol3DBase *volume, const IPoint3D &point);
  static void drawTrackROISphere(const DSPoint &position, const float radius, const DSPoint &color, bool wireFrame=false);
  static void setClippingPlane(BrainSuiteSettings::Clipping clipping, int glClipCode, DSPoint normal, DSPoint point, float offset=0);
  static void setClip(bool flag);
  static void resetClip();
  static void drawFiberTrackSet(FiberTrackSet &fiberTrackSet);
  static void drawCurveset(ProtocolCurveSet &curveSet, int selected=-1);
  static void draw(std::vector<DSPoint> &points, DSPoint color, bool selected);
  static void drawTubes(std::vector<DSPoint> &points, DSPoint color, int selected=-1);
  static void drawLineStrip(std::vector<DSPoint> &points, DSPoint color, bool selected);
  static void drawSphereStrip(std::vector<DSPoint> &points, DSPoint color, float scale);
  static void drawLineStrips(ProtocolCurveSet &curveSet, int selected);
  static void drawSolidSurface(SurfaceAlpha &surface, bool viewLighting=true);
  static void drawSolidColorSurface(const SILT::Surface &surface, const DSPoint &color, bool viewLighting=true);
  static SurfaceAlpha unitSphere;
};

#endif
