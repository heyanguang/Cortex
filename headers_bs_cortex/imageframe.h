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

#ifndef IMAGEFRAME_H
#define IMAGEFRAME_H

#include <QWidget>
#include <QFrame>

namespace Ui {
class ImageFrame;
}

class BrainSuiteWindow;
class ImageWidget;
class QResizeEvent;

class ImageFrame : public QFrame
{
  Q_OBJECT

public:
  explicit ImageFrame(BrainSuiteWindow *parent);
  ~ImageFrame();
  void setSizes();
  ImageWidget *image() { return imageWidget; }
  void updateSlider();
  void updateText();
  QPoint imagePaneOrigin; // the offset to where it starts
  QSize imagePaneSize;    // how much space is there
protected:
  virtual void resizeEvent ( QResizeEvent * event );
private slots:
  void on_verticalSlider_valueChanged(int value);
private:
  ImageWidget *imageWidget;
  BrainSuiteWindow *brainSuiteWindow;
  Ui::ImageFrame *ui;
};

#endif // IMAGEFRAME_H
