// Copyright (C) 2016 The Regents of the University of California and
// the University of Southern California
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

#ifndef TCAFixBackground_H
#define TCAFixBackground_H

#include <vol3d.h>
#include <vector>

class TCAFixBackground {
public:
  TCAFixBackground();
  int labelSliceSegments(const Vol3D<uint8> &vMaskIn);
  int checkTopology(const Vol3D<uint8> &vMaskIn);
  int checkTopology3Axes(const Vol3D<uint8> &vMaskIn);
  int correctTopology3Axes(Vol3D<uint8> &vMaskIn, const int nMaxCorrectionSize);
  int correctTopology(Vol3D<uint8> &vMaskIn, const int nMaxCorrectionSize);
  short uniqueLabels(const Vol3D<sint16> &labels);
  void ensureCC(Vol3D<uint8> &vMask);
  Vol3D<sint16> vSliceSegments; // 0 = foreground, n = background.
	Vol3D<sint16> vSliceLabels; // uniquely labeled segments.
	std::vector<int> nSliceSymbols;
	int nTotalRegions;
  int verbosity;
};

#endif
