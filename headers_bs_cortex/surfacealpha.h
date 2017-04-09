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

#ifndef SurfaceAlpha_H
#define SurfaceAlpha_H

#include <surface.h>
#include <dspoint.h>

class RGBAf {
public:
  RGBAf(const float r=0, const float g=0, const float b=0, const float a=0) : r(r), g(g), b(b), a(a) {}
  RGBAf(const DSPoint p, const float a=0.5f) : r(p.x), g(p.y), b(p.z), a(a) {}
  float r,g,b,a;
};

class SurfaceAlpha : public SILT::Surface {
// class specifically for the GUI
public:
  SurfaceAlpha() : SILT::Surface(),
    show(true), wireFrame(false), useVertexColor(true),
    useSolidColor(false), translucent(false),
    alpha(0.5f),
    solidColor(0.7f,0.7f,0.7f),
    recolorchoice(0), autoRecolor(false), dirty(false),
    displayAlternate(false), cycleSurface(true), allowClip(true)
  {
  }
  std::vector<RGBAf> alphaColor;
  std::vector<DSPoint> alternateVertices;
  bool show;
  bool wireFrame;
  bool useVertexColor;
  bool useSolidColor;
  bool translucent;
  float alpha;
  DSPoint solidColor;
  int recolorchoice;
  bool autoRecolor;
  bool dirty;
  bool displayAlternate;
  bool cycleSurface;
  bool allowClip;
};

#endif
