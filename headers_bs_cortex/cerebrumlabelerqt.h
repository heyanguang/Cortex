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

#ifndef CerebrumLabelerQt_H
#define CerebrumLabelerQt_H

#include <string>
#include <vol3d.h>

class BrainSuiteWindow;

class CerebrumLabelerQt {
public:
	enum State { Initialize=0, AlignLinear=1, AlignWarp=2, ResliceWarp=3, Finished=4};
	CerebrumLabelerQt();
	~CerebrumLabelerQt();
	std::string stepName() const;
	bool makeTempDir();
	bool initNames();

  template <class T> bool threshold(Vol3D<uint8> &vMask, Vol3D<T> &vIn);
	template <class T> bool maskDataT(Vol3D<uint16> &vOut, Vol3D<T> &volume, Vol3D<uint8> &vMask);
	bool maskData(Vol3D<uint16> &vOut, Vol3DBase *volume, Vol3D<uint8> &vMask, int verbosity=0);
	template <class FloatT> bool clampToUint16Masked(Vol3D<uint16> &vOut, const Vol3D<FloatT> &vf, const Vol3D<uint8> &vMask);
  bool writeInitializer(std::string ofname, Vol3DBase *vSubject, Vol3DBase *vAtlas);

	bool runAll(Vol3DBase *volume, Vol3D<uint8> &vMask);
	bool alignLinear(Vol3DBase *volume, std::string &atlasName);
	bool alignWarp(std::string &ofname);
	bool labelLobes(Vol3DBase *volume);
	bool labelLobes(Vol3DBase *volume, Vol3D<uint8> &vCerebrumLabels);
	bool extractBrain(Vol3DBase *volume, Vol3D<uint8> &vMask);
	void selectCerebrum(Vol3D<uint8> &vMask, Vol3D<uint8> &vLabel);
	void cleanup();
	void removeAnalyze(std::string imgfilename); //!< helper function for cleanup

	State state;
	int verbosity;
	bool madeTempDir;
	int costFunction;
	float linearConvergence;
	float warpConvergence;
	int warpLevel;

	bool keepAIR;
	bool keepWarp;
	bool keepAll;
	bool cleanOnClose;
	bool useCentroids;

	Vol3D<uint8> vLabeledLobes;
	std::string createdTempPath;
	std::string tempDirectory;
	std::string tempDirectoryBase;
	std::string atlasPath;
	std::string atlasBrain;
	std::string atlasTemplate;
	std::string brainFile;
	std::string centroidInitializerFile;
	std::string atlasToBrainAirFile;
	std::string initFile;
	std::string atlasToBrainWarpFile;
	std::string warpedLabelFile;
	std::string alignedAtlasFile;
	std::string warpedAtlasFile;
	std::string cerebroHelper;
};

#endif
