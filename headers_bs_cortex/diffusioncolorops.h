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

#ifndef DiffusionColorOps_H
#define DiffusionColorOps_H
#include <eigensystem3x3.h>
#include <cmath>

class EigColorOp {
public:
  virtual DSPoint operator()(const EigenSystem3x3f &src)=0;
};

class DECOp : public EigColorOp {
public:
  DSPoint operator()(const EigenSystem3x3f &src)
  {
    return(std::abs(src.v0.z),std::abs(src.v0.y),std::abs(src.v0.x));
  }
};

class MajorVector {
public:
  MajorVector() : bright(255.0f) {}
  inline float32 fclamp(const float32 v) { return (v<1.0f) ? v : 1.0f; }
  MajorVector(const ImageScale &imscale) : bright(imscale.maxv) {}
  DSPoint operator()(EigenSystem3x3f &data)
  {
    return DSPoint(fabsf(data.v0.x) * 255.0f/bright,
                   fabsf(data.v0.y) * 255.0f/bright,
                   fabsf(data.v0.z) * 255.0f/bright);
  }
  float bright;
};

class MajorVectorFA {
public:
  MajorVectorFA() : bright(255.0f) {}
  inline float32 fclamp(const float32 v) { return (v<1.0f) ? v : 1.0f; }
  MajorVectorFA(const ImageScale &imscale) : bright(imscale.maxv) {}
  inline float fractionalAnisotropy(const EigenSystem3x3f &e)
  {
    float d=(e.l0*e.l0+e.l1*e.l1+e.l2*e.l2);

    return (d>0) ? sqrtf(0.5 *
                         (square(e.l0-e.l1)+square(e.l1-e.l2)+square(e.l2-e.l0))
                         /d) : 0;
  }
  DSPoint operator()(const EigenSystem3x3f &data)
  {
    const float FA=fractionalAnisotropy(data) * 255.0f/bright;
    return DSPoint(fabsf(data.v0.x) * FA,
                   fabsf(data.v0.y) * FA,
                   fabsf(data.v0.z) * FA);
  }
  float bright;
};

#endif
