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

#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <dspoint.h>
#include <orientation.h>
#include <vol3dbase.h>
#include <dsimage.h>
#include <imagestate.h>
#include <lutmenusystem.h>

class BrainSuiteWindow;
class QLabel;
class ImageFrame;

class ImageWidget : public QWidget
{
  Q_OBJECT
public:
  static bool blockPainting;
  explicit ImageWidget(ImageFrame *parent=0, BrainSuiteWindow *brainSuiteWindow = 0);
  template <class RenderOp>
  bool render(DSImage &targetBitmap, const Vol3DBase *volume, const IPoint3D position,
              RenderOp &op, DSPoint scaleFactor);
  bool renderScaledVolume(DSImage &targetBitmap, const uint32 *LUT,
                          const Vol3DBase *volume, const ImageScale &brightnessScale,
                          const IPoint3D position);
  void drawCurveXY(QPainter *painter, std::vector<DSPoint> &points);
  void drawCurveXZ(QPainter *painter, std::vector<DSPoint> &points);
  void drawCurveYZ(QPainter *painter, std::vector<DSPoint> &points);
  bool renderVolume(const Vol3DBase *volume, const IPoint3D position);
  void blendLayers();
  Orientation::Code orientation;
  ImageState imageState;
  void keyUp(const int step);
  void keyDown(const int step);
  void updateOffsets();
  float zoomBestFit();
  void setZoom(int level);
  QPoint voxelCoordinateToPort(const IPoint3D &wp);
  QPoint currentScreenPosition();
  QPoint displayOffset;
  IPoint3D getPosition(int x, int y);
  IPoint3D screenToVolumePosition(int x, int y) const;
  QPoint volumeToScreenPosition(const IPoint3D &) const;
  void drawCurve(QPainter *pDC, std::vector<DSPoint> &points);
  bool drawSphere(QPainter &painter, const IPoint3D &sphereROIPositionVC, const DSPoint &sphereROIColor, const float R);
  static const float zoomMultiplier;
  bool markDirty();
  void resetOffsets();
  void shiftOffsets(QPoint shift);
  void validateOffsets();
  void stencilOutline(DSImage &stencilBitmap, const DSImage &labelBitmap);
  void stencilLabelOutline(DSImage &labelOutlineBitmap, const DSImage &labelBitmap);
  QPoint lastClick;
  void updateImage();
  void paintIt(QPainter &painter);
  static float curveCutoff;
private:
  static int serialPool;
  int serial;
  bool dirty;
  ImageFrame *imageFrame;
  BrainSuiteWindow *brainSuiteWindow;
public:
  DSImage volumeBitmap,imageOverlay1Bitmap,imageOverlay2Bitmap,labelBitmap,labelOutlineBitmap,maskBitmap,maskStencilBitmap,blendBitmap,channelBitmap;
signals:

public slots:
protected:
  virtual void paintEvent(QPaintEvent *event);
  virtual void wheelEvent ( QWheelEvent * event );
  virtual void mousePressEvent(QMouseEvent *event);
  virtual void mouseDoubleClickEvent(QMouseEvent * event);
  virtual void mouseMoveEvent(QMouseEvent *event);
  virtual void mouseReleaseEvent(QMouseEvent * event);
};

#endif // IMAGEWIDGET_H
