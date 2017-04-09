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

#ifndef DSIMAGERANGECONTROL_H
#define DSIMAGERANGECONTROL_H

#include <QWidget>
#include <dsimage.h>
#include <vol3ddatatypes.h>

class ImageScale;

class DSImageRangeControl : public QWidget
{
  Q_OBJECT
public:
  explicit DSImageRangeControl(QWidget *parent = 0);
  void setLUT(uint32 *LUT);
  DSImage lutBox;
  void setRange(const float a, const float b);
  void setRange(const ImageScale& imageScale);
  float maximumValue() const { return maxValue; }
  float minimumValue() const { return minValue; }
  void setUpperValue(const float f) { upperVal=f; }
  void setLowerValue(const float f) { lowerVal=f; }
  ImageScale imageScale() const;
  bool symmetric;
protected:
  void paintEvent(QPaintEvent *ev);
  void mouseMoveEvent(QMouseEvent *ev);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent * event);
  float upperVal;
  float lowerVal;
  float minValue;
  float maxValue;
  static const int triangleWidth;
  QPoint lastPoint;
signals:
  void rangeChanged();
  void rightClick(const QPoint &point);
public slots:

};

#endif // DSIMAGERANGECONTROL_H
