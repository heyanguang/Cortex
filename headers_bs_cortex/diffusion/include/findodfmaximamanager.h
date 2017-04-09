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

#ifndef FindODFMaximaManager_H
#define FindODFMaximaManager_H

#include <vol3d.h>
#include <mutex>

class HARDITool;

class FindODFMaximaManager {
public:
  FindODFMaximaManager(Vol3D<EigenSystem3x3f> &vEig, const Vol3D<uint8> &vMask, const HARDITool &hardiTool);
  ~FindODFMaximaManager();
  void launch(int nThreads);
  int nextSlice();
  int nSlices() const { return vEig.cz; }
  int currentPosition() const { return currentSlice; }
  void stop() { halt=true; }
private:
  Vol3D<EigenSystem3x3f> &vEig;
  const HARDITool &hardiTool;
  const Vol3D<uint8> &vMask;
  size_t currentSlice;
  std::mutex sliceMutex;
  bool halt;
};

#endif
