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

#ifndef BiasInfo_H
#define BiasInfo_H

#include <dspoint.h>

class BiasInfo {
public:
	BiasInfo() : bias(0.0), nBrainVoxels(0), valid(false), rejected(okay),
    fitnessError(0), neighborhood(0),
		pos(0), x(0), y(0), z(0), nbrs(0), mean(0)
	{}
	enum Failure { okay = 0x0, tooFew = 0x01, outOfRange = 0x02, bigError = 0x04, neighbors = 0x08 };

	float bias;
	int nBrainVoxels; // number of brain voxels in region
	bool valid;
	Failure rejected;
	float fitnessError; 
	float neighborhood;
	int pos;
	int x,y,z;
	int nbrs;
	float mean;
	DSPoint centroid;
};

#endif
