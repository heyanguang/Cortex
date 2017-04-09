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

#ifndef Dewisp_H
#define Dewisp_H

#include <vol3d.h>
#include <vector>
#include <TCA/edgetable.h>
#include <TCA/link.h>

class Dewisp {
public:
  Dewisp(int sizeThreshold=15) :
    totalSym(0), sizeThreshold(sizeThreshold)
	{}
	bool process(Vol3D<uint8> &volume);
	void labelSlices(Vol3D<uint8> &vin);
	int analyze(Vol3D<uint8> &vin);
	Vol3D<sint16> foregroundLabels;
  Vol3D<uint8>  intersect;
	Vol3D<sint16> labels;
  Vol3D<uint16> vUnique;
  std::vector<int> labelCount;
	std::vector<int> nsym;
	std::vector<int> offset;
	EdgeTable<Link> edgeTable;
	std::vector<int> degree;
	int totalSym;
	int sizeThreshold;
};

#endif
