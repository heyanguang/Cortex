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

#ifndef BFCTool_H
#define BFCTool_H

#include <BFC/biasfieldcorrector.h>

class BFCTool {
public:
  enum State { Init=0, ComputePoints=1, ComputeSpline=2, RemoveBias=3, Finished=4 };
  State state;
  BiasFieldCorrector bfc;
  std::string nextStepName() const;
  std::string runningStepName() const;
  bool load(Vol3DBase *volume);
  bool removeBias(Vol3DBase *vIn);
  bool removeBias(Vol3DBase *vIn, Vol3D<uint8> &vMask);
  bool step();
  bool initialize(Vol3DBase *volume, Vol3D<uint8> &vMask);
  bool computePointwiseBiasEstimates();
  bool estimateCorrectionField();
};

#endif
