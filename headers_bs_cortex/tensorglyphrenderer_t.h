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

#ifndef TENSORGLYPHRENDERER_T_H
#define TENSORGLYPHRENDERER_T_H

#include <cstdlib>
#include <tensorglyphrenderer.h>
#include <glglyphs.h>

GLEllipse *currentEllipse();

template <class ColorOp>
void TensorGlyphRenderer::drawEllipsesXY(const Vol3D<EigenSystem3x3f> &vol, const int slice, ColorOp &colorOp)
{
  glEnableClientState( GL_VERTEX_ARRAY );						// Enable Vertex Arrays
  glEnableClientState( GL_NORMAL_ARRAY );						// Enable Normal Arrays
  glDisableClientState(GL_COLOR_ARRAY);             // No per-vertex color
  glEnable(GL_COLOR_MATERIAL);                      // Use material color
  GLGlyph glyph;
  GLEllipse *ellipse = currentEllipse();
  const int cx=vol.cx;
  const int cy= vol.cy;
  const float rx = vol.rx;
  const float ry = vol.ry;
  const float rz = vol.rz;
  const int z = slice;
  EigenSystem3x3f *data = vol.slice(slice);
  for (int y=0;y<cy;y++)
    for (int x=0;x<cx;x++,data++)
    {
      glyph.create(*ellipse,DSPoint(x*rx,y*ry,z*rz),*data,BrainSuiteSettings::ellipseRadius);
      glyph.displayColor = colorOp(*data);
      glyph.draw();
    }
  ::glEnd();
}

template <class ColorOp>
void TensorGlyphRenderer::drawEllipsesXZ(const Vol3D<EigenSystem3x3f> &vol, const int slice, ColorOp &colorOp)
{
  glEnableClientState( GL_VERTEX_ARRAY );						// Enable Vertex Arrays
  glEnableClientState( GL_NORMAL_ARRAY );						// Enable Normal Arrays
  glDisableClientState(GL_COLOR_ARRAY);             // No per-vertex color
  glEnable(GL_COLOR_MATERIAL);                      // Use material color
  GLGlyph glyph;
  GLEllipse *ellipse = currentEllipse();
  const int cx=vol.cx;
  const int cz=vol.cz;
  const float rx = vol.rx;
  const float ry = vol.ry;
  const float rz = vol.rz;
  const int y = slice;
  for (int z=0;z<cz;z++)
  {
    EigenSystem3x3f *data = vol.slice(z) + slice * cx;
    for (int x=0;x<cx;x++,data++)
    {
      glyph.create(*ellipse,DSPoint(x*rx,y*ry,z*rz),*data,BrainSuiteSettings::ellipseRadius);
      glyph.displayColor = colorOp(*data);
      glyph.draw();
    }
  }
}

template <class ColorOp>
void TensorGlyphRenderer::drawEllipsesYZ(const Vol3D<EigenSystem3x3f> &vol, const int slice, ColorOp &colorOp)
{
  glEnableClientState( GL_VERTEX_ARRAY );						// Enable Vertex Arrays
  glEnableClientState( GL_NORMAL_ARRAY );						// Enable Normal Arrays
  glDisableClientState(GL_COLOR_ARRAY);             // No per-vertex color
  glEnable(GL_COLOR_MATERIAL);                      // Use material color
  const int cx=vol.cx;
  const int cy=vol.cy;
  const int cz=vol.cz;
  const float rx = vol.rx;
  const float ry = vol.ry;
  const float rz = vol.rz;
  const int x = slice;
  GLGlyph glyph;
  GLEllipse *ellipse = currentEllipse();
  for (int z=0;z<cz;z++)
  {
    EigenSystem3x3f *data = vol.slice(z) + x;
    for (int y=0;y<cy;y++)
    {
      glyph.create(*ellipse,DSPoint(x*rx,y*ry,z*rz),*data,BrainSuiteSettings::ellipseRadius);
      glyph.displayColor = colorOp(*data);
      glyph.draw();
      data += cx;
    }
  }
}

template <class ColorOp>
void TensorGlyphRenderer::drawEllipsesMaskedXY(const Vol3D<EigenSystem3x3f> &vol, const Vol3D<uint8> &vMask, const int slice, ColorOp &colorOp)
{
  if (vol.isCompatible(vMask)==false) { drawEllipsesXY(vol,slice,colorOp); return; }
  glEnableClientState( GL_VERTEX_ARRAY );						// Enable Vertex Arrays
  glEnableClientState( GL_NORMAL_ARRAY );						// Enable Normal Arrays
  glDisableClientState(GL_COLOR_ARRAY);             // No per-vertex color
  glEnable(GL_COLOR_MATERIAL);                      // Use material color
  GLGlyph glyph;
  GLEllipse *ellipse = currentEllipse();
  const int cx=vol.cx;
  const int cy= vol.cy;
  const float rx = vol.rx;
  const float ry = vol.ry;
  const float rz = vol.rz;
  const int z = slice;
  EigenSystem3x3f *data = vol.slice(slice);
  uint8 *mask = vMask.slice(slice);
  for (int y=0;y<cy;y++)
    for (int x=0;x<cx;x++,data++,mask++)
    {
      if (!*mask) continue;
      glyph.create(*ellipse,DSPoint(x*rx,y*ry,z*rz),*data,BrainSuiteSettings::ellipseRadius);
      glyph.displayColor = colorOp(*data);
      glyph.draw();
    }
  ::glEnd();
}

template <class ColorOp>
void TensorGlyphRenderer::drawEllipsesMaskedXZ(const Vol3D<EigenSystem3x3f> &vol, const Vol3D<uint8> &vMask, const int slice, ColorOp &colorOp)
{
  if (vol.isCompatible(vMask)==false) { drawEllipsesXZ(vol,slice,colorOp); return; }
  glEnableClientState( GL_VERTEX_ARRAY );						// Enable Vertex Arrays
  glEnableClientState( GL_NORMAL_ARRAY );						// Enable Normal Arrays
  glDisableClientState(GL_COLOR_ARRAY);             // No per-vertex color
  glEnable(GL_COLOR_MATERIAL);                      // Use material color
  GLGlyph glyph;
  GLEllipse *ellipse = currentEllipse();
  const int cx=vol.cx;
  const int cz=vol.cz;
  const float rx = vol.rx;
  const float ry = vol.ry;
  const float rz = vol.rz;
  const int y = slice;
  for (int z=0;z<cz;z++)
  {
    EigenSystem3x3f *data = vol.slice(z) + slice * cx;
    uint8 *mask = vMask.slice(z) + slice * cx;
    for (int x=0;x<cx;x++,data++,mask++)
    {
      if (!*mask) continue;
      glyph.create(*ellipse,DSPoint(x*rx,y*ry,z*rz),*data,BrainSuiteSettings::ellipseRadius);
      glyph.displayColor = colorOp(*data);
      glyph.draw();
    }
  }
}

template <class ColorOp>
void TensorGlyphRenderer::drawEllipsesMaskedYZ(const Vol3D<EigenSystem3x3f> &vol, const Vol3D<uint8> &vMask, const int slice, ColorOp &colorOp)
{
  if (vol.isCompatible(vMask)==false) { drawEllipsesYZ(vol,slice,colorOp); return; }
  glEnableClientState( GL_VERTEX_ARRAY );						// Enable Vertex Arrays
  glEnableClientState( GL_NORMAL_ARRAY );						// Enable Normal Arrays
  glDisableClientState(GL_COLOR_ARRAY);             // No per-vertex color
  glEnable(GL_COLOR_MATERIAL);                      // Use material color
  GLGlyph glyph;
  const int cx=vol.cx;
  const int cy=vol.cy;
  const int cz=vol.cz;
  const float rx = vol.rx;
  const float ry = vol.ry;
  const float rz = vol.rz;
  const int x = slice;
  GLEllipse *ellipse = currentEllipse();
  for (int z=0;z<cz;z++)
  {
    EigenSystem3x3f *data = vol.slice(z) + x;
    for (int y=0;y<cy;y++)
    {
      if (vMask(x,y,z))
      {
        glyph.create(*ellipse,DSPoint(x*rx,y*ry,z*rz),*data,BrainSuiteSettings::ellipseRadius);
        glyph.displayColor = colorOp(*data);
        glyph.draw();
      }
      data += cx;
    }
  }
}

#endif // TENSORGLYPHRENDERER_T_H
