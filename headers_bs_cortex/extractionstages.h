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

#ifndef ExtractionStages_H
#define ExtractionStages_H

#include <string>

class ExtractionStages {
public:
  enum Stages
  {
    SkullStripping = 0,
    SkullAndScalp = 1,
    BiasFieldCorrection = 2,
    TissueClassification = 3,
    CerebrumLabeling = 4,
    InnerCorticalMask = 5,
    ScrubMask = 6,
    TopologyCorrection = 7,
    WispFilter = 8,
    InnerCorticalSurface = 9,
    PialSurface = 10,
    SplitHemispheres = 11,
    RegisterAndLabel = 12,
    Finished = 13
  };
  static std::string stageName(Stages stage);
};

#endif // ExtractionStages_H
