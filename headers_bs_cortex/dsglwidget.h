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

#ifndef DSGLWIDGET_H
#define DSGLWIDGET_H

#include <QGLWidget>
#include <glviewcontroller.h>
#include <surfaceviewproperties.h>
#include <surfacealpha.h>
#include <qglshaderprogram.h>

class ImageWidget;
class BrainSuiteWindow;
class Vol3DBase;

class DSGLWidget : public QGLWidget
{
  Q_OBJECT
public:
  DSGLWidget(BrainSuiteWindow *brainSuiteWindow);
  void setRotation(const DSPoint &rotationAngles);
  void toggleShowSurfaces();
  void toggleShowFibers();
  void toggleShowTensorGlyphs();
  void toggleShowHARDI();
  void toggleShowVolumes();
  void resetView();
  DSPoint getBackgroundColor();
  void setBackgroundColor(DSPoint backgroundColor);
protected:
  DSPoint getOGLPos(const QPoint &p);
  void setOrigin();
  void paintSlices(bool translucent);
  void paintBoundingBoxes();
  void paintTranslucentSurfaces();
  void paintOpaqueSurfaces();
  void paintTensors();
  void paintODFs();
  void paintFibers();
  void drawSphereROIs();
  void paintCurves();

  void glRenderPortXY(ImageWidget *port, const float alpha=1.0f, const bool mask=false);
  void glRenderPortXZ(ImageWidget *port, const float alpha=1.0f, const bool mask=false);
  void glRenderPortYZ(ImageWidget *port, const float alpha=1.0f, const bool mask=false);
  void glRenderPort(ImageWidget *port, const float alpha=1.0f);

  void mousePressEvent(QMouseEvent *event);
  void mouseDoubleClickEvent(QMouseEvent * event);

  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent * event);
  void wheelEvent ( QWheelEvent * event );
  void initializeGL();
  void resizeGL( int w, int h );
  void paintGL();
  bool hasMouse;
  QPoint previousPosition;
  BrainSuiteWindow *brainSuiteWindow;
  GLint viewport[4];
  GLdouble modelview[16];
  GLdouble projection[16];
public:
  GLViewController glViewController;
  SurfaceViewProperties surfaceViewProperties;
  SurfaceAlpha unitSphere;
  bool tracing;
  bool blockSpin;
};

#endif // DSGLWidget_H
