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

#ifndef PVCTool_H
#define PVCTool_H

#include <PVC/pvmodel.h>
#include <vol3d.h>

class PVCTool {
public:
	class Settings {
	public:
		Settings();
		float spatialPrior;
		bool threeClass;
		int maxICMIterations;
	};
	Settings settings;
	enum PVCState { MLCassify = 0, ICM = 1, Finished = 2 };
	PVCTool(int verbosity_=1);
	std::string nextStepName();
	bool stepForward(Vol3D<uint8> &vLabel, Vol3DBase *imageVolume, const Vol3D<uint8> &vMask);
	bool stepBack(Vol3D<uint8> &vLabel, Vol3DBase *imageVolume, const Vol3D<uint8> &vMask); // go back one step, return false if at beginning
	bool initializeML(Vol3D<uint8> &vLabel, Vol3DBase *volume, const Vol3D<uint8> &vMask);
	int icm(Vol3D<uint8> &vLabel, const float lambda, const int iterations, bool threeClass = false);
	void computeFractions(Vol3D<float> &vFractions, Vol3D<uint8> &vb, Vol3D<uint8> &vLabel, float theta[]);
	Vol3D<uint8> vb;
	Vol3D<uint8> vl;
	float theta[10];
	PartialVolumeModel partialVolumeModel;
	PVCState state;
	int verbosity;
};


#endif
