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

#ifndef GLViewController_H
#define GLViewController_H

#include <qgl.h>
#include <math.h>
#include <dspoint.h>
#include <triple.h>
#include <ArcBall.h>
#include <dslight.h>
#include <vol3ddatatypes.h>

class GLViewController {
public:
  GLViewController();
  class Point2D {
  public:
    Point2D(const int x=0, const int y=0) : x(x), y(y) {}
    template <class QP> Point2D(const QP &p) : x(p.x()), y(p.y()) {}
    Point2D operator-(const Point2D &p) { return Point2D(x-p.x,y-p.y); }
    int x,y;
  };
  class Properties {
  public:
    Properties() : extent(125.0f), zoom(1.0f), xAngle(-90.0f), yAngle(180.0f), zAngle(0.0f), xShift(0), yShift(0) {}
    float extent;
    float zoom;
    float xAngle;
    float yAngle;
    float zAngle;
    float xShift;	// screen pos, not wcs
    float yShift;	// screen pos, not wcs
  };
  void leftButtonDown(Point2D p);
  DSPoint clearColor;
  Properties properties;
  void setMousePoint(Point2D p) { mouseDownPoint.x = p.x; mouseDownPoint.y = p.y; }
  void setMousePoint(const int x, const int y) { mouseDownPoint.x = x; mouseDownPoint.y = y; }
  bool initialize();
  bool setup(const int viewportX, const int viewportY); // viewport size
  bool mouseLBDown(uint32  nFlags, Point2D point);
  bool mouseLBUp(uint32  nFlags, Point2D point);
  bool mouseMove(uint32  nFlags, Point2D point);
  bool mouseWheel(uint32  nFlags, short zDelta, Point2D pt);
  void setRotation(const float xAngle, const float yAngle, const float zAngle);
  void lighting(bool on=true);
  void axes();
  void rotation();
  ArcBall_t arcBall;
  Matrix4fT Transform;
  Matrix3fT LastRot;
  Matrix3fT ThisRot;
  DSLight light0,light1,light2;
  float viewportXdim;
  float viewportYdim;
  float retinaScale;
private:
  Point2D mouseDownPoint;
};

#endif
