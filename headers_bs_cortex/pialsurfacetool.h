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

#ifndef PialSurfaceTool_H
#define PialSurfaceTool_H

#include "surflib.h"
#include "surfaceexpander.h"

class PialSurfaceTool : public SurfaceExpander {
public:
  PialSurfaceTool();
  size_t nIterations() const	{ return numIterations; }
  size_t iterationNumber() const	{ return iterationNo; }
  bool atEnd() const { return iterationNo>=nIterations(); }

  size_t iterationNo;
  int numIterations;
  int presmoothIterations;
  bool estimateCorticalThickness;
  Surface sIn,sOut;
  Vol3D<float> vTissue;
  bool resetIterations();
  void showParameters();
  void performNextIteration();
  void copySurf(Surface &second, const Surface &first);
  Surface sSave;
};

#endif
