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

#ifndef CorticalExtractionSettings_H
#define CorticalExtractionSettings_H

#include <vol3ddatatypes.h>
#include <utility>
#include <string>

class CorticalExtractionSettings
{
public:
  CorticalExtractionSettings();
  bool saveAsXML(std::string ofname);
  bool readFromXML(std::string ifname);
  bool saveAsPlainText(std::string ofname);
  bool readFromPlainText(std::string ifname);
  class BSE {
  public:
    BSE();
    uint32	diffusionIterations;
    float32	diffusionConstant;
    float32	edgeConstant;
    uint32	erosionSize;
    bool	trimSpinalCord;
    bool	dilateFinalMask;
  };
  class Skullfinder {
  public:
    Skullfinder();
    bool computeThresholds;
    int skullThreshold;
    int scalpThreshold;
  };
  class BFC {
  public:
    enum ROIType { Ellipsoid = 0, Block = 1 };
    BFC();
    uint32	histogramRadius;
    uint32	biasEstimateSampleSpacing;
    uint32	controlPointSpacing;
    float32	splineStiffness;
    ROIType	roiType;
    std::pair<float,float> biasRange;
    bool iterative;
  };
  class PVC {
  public:
    PVC();
    float32	spatialPrior;
  };
  class Cerebrum {
  public:
    Cerebrum();
    bool useCentroids;
    float linearConvergence;
    float warpConvergence;
    int warpLevel; // limited range
    int costFunction;
    bool verbose;
    bool showAtlasOverlay;
    std::string atlasFilename;
    std::string labelFilename;
    std::string tempDirectory;
  };
  class Cortex {
  public:
    Cortex();
    float tissueThreshold;
    bool includeAllSubcorticalAreas;
  };
  class ScrubMask {
  public:
    ScrubMask();
    int foregroundThreshold;
    int backgroundThreshold;
    int nScrubIterations;
  };
  class TCA {
  public:
    TCA();
    int minimumCorrectionSize;
    int maximumCorrectionSize;
    int fillOffset;
  };
  class Dewisp {
  public:
    Dewisp();
    int threshold;
    int maximumIterations;
  };
  class InnerCorticalSurface {
  public:
    InnerCorticalSurface();
    int smoothingIterations;
    float smoothingConstant;
    float curvatureWeight;
  };
  class Pial {
  public:
    Pial();
    int pialPresmoothIterations;
    int pialIterations;
    float pialCollisionDetectionRadius;
    float pialThicknessLimit;
    float pialStepSize;
    float pialTissueThreshold;
    float pialSmoothingConstant;
    float pialRadialConstant;
    int pialUpdateSurfaceInterval;
    bool pialConstrainWithCerebrumMask;
  };
  class SVReg {
  public:
    SVReg();
    bool surfaceOnly;
    bool refineSulci;
    bool extendLabels;
    bool computeStats;
    bool removeTempFiles;
    std::string atlasName;
    int atlasIndex;
  };
  BSE bse;
  Skullfinder skullfinder;
  BFC bfc;
  PVC pvc;
  Cerebrum cbm;
  Cortex ctx;
  ScrubMask scrubMask;
  TCA tca;
  Dewisp dewisp;
  InnerCorticalSurface ics;
  Pial pial;
  SVReg svreg;
};

#endif // CorticalExtractionSettings_H
