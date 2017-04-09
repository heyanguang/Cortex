// Copyright (C) 2016 The Regents of the University of California
//
// Created by David W. Shattuck, Ph.D.
//
// This file is part of TCA.
//
// TCA is free software; you can redistribute it and/or
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

#ifndef TopoFixer_H
#define TopoFixer_H

#include <TCA/topologycorrector.h>
#include <TCA/tcafixbackground.h>
#include <subvol.h>

class TopoFixer {
public:
	TopoFixer();
	TopologyCorrector topologicalFilter;
	TCAFixBackground tcaBackground;
	int fixDefects(Vol3D<uint8> &vMask, int minFix=1, int maxFix=200, int delta=0, int verbosity=1, std::ostream &outstream=std::cout);
	bool wrapUp(Vol3D<uint8> &vMask, std::ostream &outstream);
	int verbosity;
	SubVol3D<uint8> vSubMask;
	void initialize(Vol3D<uint8> &vMask);
	bool iterate(int &i, int delta, std::ostream &outstream);
	bool completed;
};

#endif // TOPOFIXER_H
