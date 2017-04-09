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

#ifndef GLFrame2D_H
#define GLFrame2D_H

#include <math.h>
#include "qgl.h"
#include <dspoint.h>
#include <triple.h>
#include <ArcBall.h>
#include <vol3ddatatypes.h>

class GLFrame2D {
public:
  class Point2D {
  public:
    Point2D(const int x=0, const int y=0) : x(x), y(y) {}
    template <class QP> Point2D(const QP &p) { x=p.x(); y=p.y(); }
    Point2D operator-(const Point2D &p) { return Point2D(x-p.x,y-p.y); }
    int x,y;
  };
  GLFrame2D();
  DSPoint clearColor;
  void leftButtonDown(Point2D p);
  void setMousePoint(Point2D p) { mouseDownPoint.x = p.x; mouseDownPoint.y = p.y; }
  void setMousePoint(const int x, const int y) { mouseDownPoint.x = x; mouseDownPoint.y = y; }
public:
  bool setup(const int viewportX, const int viewportY);
  bool initialize();
  bool mouseLBDown(uint32  nFlags, Point2D point);
  bool mouseLBUp(uint32  nFlags, Point2D point);
  bool mouseMove(uint32  nFlags, Point2D point);
  bool mouseWheel(uint32  nFlags, short zDelta, Point2D pt);
  float viewportXdim;
  float viewportYdim;
private:
  Point2D mouseDownPoint;
};

#endif
