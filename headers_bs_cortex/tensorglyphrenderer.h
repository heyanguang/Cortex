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

#ifndef TENSORGLYPHRENDERER_H
#define TENSORGLYPHRENDERER_H

#include <vol3d.h>

class TensorGlyphRenderer
{
public:
  template <class ColorOp>
  static void drawEllipsesXY(const Vol3D<EigenSystem3x3f> &vol, const int slice, ColorOp &colorOp);
  template <class ColorOp>
  static void drawEllipsesXZ(const Vol3D<EigenSystem3x3f> &vol, const int slice, ColorOp &colorOp);
  template <class ColorOp>
  static void drawEllipsesYZ(const Vol3D<EigenSystem3x3f> &vol, const int slice, ColorOp &colorOp);
  template <class ColorOp>
  static void drawEllipsesMaskedXY(const Vol3D<EigenSystem3x3f> &vol, const Vol3D<uint8> &vMask, const int slice, ColorOp &colorOp);
  template <class ColorOp>
  static void drawEllipsesMaskedXZ(const Vol3D<EigenSystem3x3f> &vol, const Vol3D<uint8> &vMask, const int slice, ColorOp &colorOp);
  template <class ColorOp>
  static void drawEllipsesMaskedYZ(const Vol3D<EigenSystem3x3f> &vol, const Vol3D<uint8> &vMask, const int slice, ColorOp &colorOp);
};

#endif // TENSORGLYPHRENDERER_H
