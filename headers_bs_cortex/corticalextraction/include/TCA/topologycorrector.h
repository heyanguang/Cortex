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

#ifndef TopologyCorrector_H
#define TopologyCorrector_H

#include <vol3d.h>
#include <TCA/tcafixforeground.h>

class TopologyCorrector {
public:
  TopologyCorrector();
	int checkTopology(Vol3D<uint8> &vMask);		
	void analyzeOnly(Vol3D<uint8> &mask, int mode=0);
	int analyzeAndFix(Vol3D<uint8> &mask, int thresh);
	int checkTopology3Axes(Vol3D<uint8> &vMask);
	int loopFG(Vol3D<uint8> &vm, const int size, const int fgDelta=0);
	void selectCC(Vol3D<uint8> &vb);
  int nextSmallest(EdgeTable<Link> &et, int thresh);
  TCAFixForeground fg;
	bool list;
  bool bgOnly;
	int topomode; // 1 bg only, 2 fg only, else do both
  int verbosity;
protected:
	Vol3D<uint8> tr;
};

#endif
