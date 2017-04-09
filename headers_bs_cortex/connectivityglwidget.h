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

#ifndef CONNECTIVITYGLWIDGET_H
#define CONNECTIVITYGLWIDGET_H

#include <QGLWidget>
#include <glframe2d.h>

class BrainSuiteWindow;
class FiberTrackSet;
class Vol3DBase;

class ConnectivityGLWidget : public //QOpenGLWidget
    QGLWidget
{
public:
  ConnectivityGLWidget(BrainSuiteWindow *parent);
  BrainSuiteWindow *brainSuiteWindow;
  void regroup();
  Vol3DBase *vLabel();
  FiberTrackSet *getSubgroup();
  FiberTrackSet *applyFilter(FiberTrackSet *tractSet);
  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent * event);
  void wheelEvent ( QWheelEvent * event );
  void resizeEvent(QResizeEvent * event);
  void paintEvent(QPaintEvent *event);
  void initialize() { initializeGL(); }
  void initializeGL();
  bool computing;
  GLFrame2D glFrame;
private:
  bool sliding;
};

#endif // CONNECTIVITYGLWIDGET_H
