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

#ifndef GLGlyphs_H
#define GLGlyphs_H

#include <glcompatibility.h>
#include <vector>

class EigenSystem3x3f;

typedef Triple<int> Triangle;

class GLEllipse {
public:
  GLEllipse(const int level = 0);
  std::vector<Triangle> t;
  std::vector<DSPoint> v;
};

class GLGlyph {
public:
  typedef Triple<int> Triangle;
  void create(GLEllipse &shape, DSPoint center, float r);
  void create(GLEllipse &shape, DSPoint center, EigenSystem3x3f & es, float r = 1);
  std::vector<DSPoint> points;
  std::vector<Triangle> triangles;
  std::vector<DSPoint> normals;
  DSPoint displayColor;
  DSPoint center;
  void draw()
  {
    glColor3fv(&displayColor.x);
    glVertexPointer(3,GL_FLOAT,0,&points[0]);
    glNormalPointer(GL_FLOAT,0,&normals[0]);
    glDrawElements(GL_TRIANGLES,(GLsizei)triangles.size()*3,GL_UNSIGNED_INT,&triangles[0]);
  }
};

#endif
