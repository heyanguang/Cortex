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

#ifndef FindODFMaximaThread_H
#define FindODFMaximaThread_H

#include <thread>
#include <vol3d.h>

class HARDITool;
class FindODFMaximaManager;

class FindODFMaximaThread {
public:
  FindODFMaximaThread(FindODFMaximaManager *parent, Vol3D<EigenSystem3x3f> &vEig, const Vol3D<uint8> &vMask, const HARDITool &hardiTool);
  void run();
  bool runSlice(size_t z);
  FindODFMaximaManager *parent;
  size_t slice;
  bool useMask;
  Vol3D<EigenSystem3x3f> &vEig; // output
  const HARDITool &hardiTool;
  const Vol3D<uint8> &vMask;
  const int threadNumber;
  static int threadCount;
};

#endif
