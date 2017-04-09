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

#ifndef CorticalExtractionData_H
#define CorticalExtractionData_H

#include <string>
#include <vol3d.h>
class SurfaceAlpha;

class CorticalExtractionData {
public:
  CorticalExtractionData();
  ~CorticalExtractionData();
  std::string basefile;
  Vol3D<uint8> vBrainMask;
  Vol3DBase *vBSE;
  Vol3DBase *vBFC;
  Vol3D<uint8> vPVCLabels;
  Vol3D<float> vPVCFractions;
  Vol3D<uint8> vCerebrumMask;
  Vol3D<uint8> vHemiLabels;
  Vol3D<uint8> vCortexInitMask;
  Vol3D<uint8> vCortexScrubbedMask;
  Vol3D<uint8> vCortexTCAMask;
  Vol3D<uint8> vCortexDewispMask;
  SurfaceAlpha *innerCorticalSurface;
  SurfaceAlpha *pialSurface;
  SurfaceAlpha *leftInnerCorticalSurface,*rightInnerCorticalSurface;
  SurfaceAlpha *leftPialSurface,*rightPialSurface;
  SurfaceAlpha *innerSkullSurface,*outerSkullSurface,*scalpSurface,*brainSurface;
  enum Stages { BSE=1, BFC=2, PVC=3, CB=4, CTX=5, ScrubMask=6, TCA=7, Dewisp=8, InnerCorticalSurface=9, PialSurface=10 };
  bool load(std::string filebasename, std::ostream &errstream, Stages stage);
  std::ostringstream loadStream;
};
#endif // CORTICALEXTRACTIONDATA_H
