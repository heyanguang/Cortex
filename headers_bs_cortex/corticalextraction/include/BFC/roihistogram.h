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

#ifndef ROIHistogram_H
#define ROIHistogram_H

#include <DS/histogram.h>
#include <vector>

class Vol3DBase;

class ROIHistogram : public HistogramBase {
public:
	enum ROIType { Ellipse = 0, Box = 1 };
	ROIHistogram();
	void setup(Vol3DBase &v, const float radius_, const ROIType roiType_=Box);
	void compute(Vol3D<uint8> &vImage, int x, int y, int z);
	void compute(Vol3D<uint8> &vImage, Vol3D<uint8> &vMask, int x, int y, int z);
	size_t nVoxels() const;
	DSPoint centroid;
protected:
	ROIType roiType;
	float rx,ry,rz;
	float radius;
	std::vector<IPoint3D> deltas;
};

#endif
