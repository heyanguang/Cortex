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

#ifndef DSIMAGE_H
#define DSIMAGE_H

#include <QImage>
#include <vol3ddatatypes.h>

class DSImage
{
public:
  explicit DSImage(bool alpha=false);
  QSize size() const { return image.size(); }
  QImage image;
  void resize(const int cx, const int cy);
  void resize(QSize newsize) { resize(newsize.width(),newsize.height()); }
  void blank();
  void setAlpha(int alpha);
  void setRes(const float rx_, const float ry_, const float scale);
  QRgb* pixels() { return reinterpret_cast<QRgb*>(image.bits());	}
  uint32* operator()() { return reinterpret_cast<uint32*>(image.bits());	}
  float rx,ry,scale;
  int npix() const { return image.width()*image.height(); }
signals:

protected:
  bool alpha;

public slots:

};

#endif // DSIMAGE_H
