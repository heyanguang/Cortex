// Copyright (C) 2016 The Regents of the University of California
//
// Created by David W. Shattuck, Ph.D.
//
// This file is part of Dewisp.
//
// Dewisp is free software; you can redistribute it and/or
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

#ifndef DewispTool_H
#define DewispTool_H

#include <vol3d.h>
#include <vector>

class DewispTool {
public:
  DewispTool() : sizeThreshold(15) {}
	int sizeThreshold;
	void ensureCC(Vol3D<uint8> &vMask);
	void process(Vol3D<uint8> &volume, int verbosity);
	void processXZ(Vol3D<uint8> &volume, int verbosity);
	void processYZ(Vol3D<uint8> &volume, int verbosity);
	void transposeXZ(Vol3D<uint8> &vDst, const Vol3D<uint8> &vSrc);
	void transposeYZ(Vol3D<uint8> &vDst, const Vol3D<uint8> &vSrc);
	int delta(const Vol3D<uint8> &vA, const Vol3D<uint8> &vB);
	int loop(Vol3D<uint8> &vOut, const Vol3D<uint8> &vIn, int verbosity=1);
};

#endif
