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

#ifndef FiberTrackerThread_H
#define FiberTrackerThread_H

#include <thread>
#include <vol3d.h>
#include <list>
#include <queue>
#include <mutex>

class FiberTrackerThreadManager;
class HTrackerBase;
class FiberTrackSet;

class FiberTrackerThread {
public:
  FiberTrackerThread(FiberTrackerThreadManager *parent, HTrackerBase *tracker, const Vol3D<EigenSystem3x3f> &vEig, const float dotProductThresh);
  void run();
  FiberTrackerThreadManager *parent;
  size_t slice;
  HTrackerBase *tracker;
  const Vol3D<EigenSystem3x3f> &vEig;
  float fibertrackDotProductThresh;
  const int threadNumber;
  static int threadCount;
};

class FiberTrackerThreadManager {
public:  
  FiberTrackerThreadManager(FiberTrackSet &fiberTrackSet, const Vol3D<EigenSystem3x3f> &vEigIn, const Vol3D<uint8> &vMask,
                            const float vStep, float stepsize, int nSteps, const float angleThresh);
  ~FiberTrackerThreadManager();
  bool launch(int nThreads);
  void reportFinished(int index, std::list<DSPoint> &track, int seedIndex);
  int nextPoint(DSPoint &point);
  int currentSlice() const;
  int nSlices() const;
  bool stop();
private:
  void initEigen();
  FiberTrackSet &fiberTrackSet;
  const Vol3D<EigenSystem3x3f> &vEigIn;
  const Vol3D<uint8> &vMask;
  Vol3D<EigenSystem3x3f> vEig; // working one
  std::mutex fiberMutex;
  int pointIndex;
  DSPoint currentPosition;
  DSPoint stepSizes;
  float zMax;
  float fibertrackDotProductThresh;
  bool useMask;
  const float vStep;
  const float stepsize;
  const int nSteps;
  const float angleThresh;
  bool halt;
  std::priority_queue<std::pair<size_t,size_t>> indexMap;
};

#endif
