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

#ifndef HTracker_H
#define HTracker_H

#include <list>
#include <vol3d.h>
class DSPoint;

class HTrackerBase {
public:
  HTrackerBase() : voxels(false), nSteps(100), stepsize(0.1f) {}
  bool voxels;
  int nSteps;
  float stepsize;
  virtual bool track(std::list<DSPoint> &tract, int &seedIndex, const Vol3D<EigenSystem3x3f> &vMax, DSPoint seedPoint, const float fibertrackDotProductThresh) const =0;
};

template <class Interpolator, class Integrator>
class HTracker : public HTrackerBase {
public:
  HTracker() : HTrackerBase() {}
  bool track(std::list<DSPoint> &tract, int &seedIndex, const Vol3D<EigenSystem3x3f> &vMax, DSPoint seedPoint, const float fibertrackDotProductThresh) const;
};


#endif
