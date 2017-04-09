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

#ifndef BiasFieldCorrector_H
#define BiasFieldCorrector_H

#include <BFC/regularizedsplinef.h>
#include <BFC/biasinfo.h>
#include <fstream>
#include <string>
#include <vector>
#include <vol3d.h>

class BiasFieldCorrector {
public:
// for iterative output
	enum OutputType { Analyze, Nifti, AnalyzeGZ, NiftiGZ };
	enum State { Initializing, ComputeBiasPoints, ComputeSpline, ComputingField, CorrectingImage, Finished };
	State state;
	std::string outputSuffix()
	{
		switch (outputType)
		{
			case Analyze : return "img";
			case AnalyzeGZ : return "img.gz";
			case Nifti : return "nii";
			case NiftiGZ : 
			default:				return "nii.gz";
		}
	}
	class IterationParameters {
	public:
		IterationParameters(int r, int s, int c, float w) : radius(r), sampleSpacing(s), controlPointSpacing(c), stiffness(w) {}
		int radius;
		int sampleSpacing;
		int controlPointSpacing;
		float stiffness;
	};
	static IterationParameters defaultSchedule[];

	typedef std::vector<BiasFieldCorrector::IterationParameters>::iterator ScheduleIterator;
	bool performNextIteration(Vol3D<float32> &vWorking, Vol3D<float> &vSpline, Vol3D<uint8> &vMask);
	ScheduleIterator scheduleIterator;
	size_t iterationNo;
	size_t nIterations() const	{ return schedule.size(); }
	size_t iterationNumber() const	{ return iterationNo; }
	bool atEnd() const			{ 	return (scheduleIterator==schedule.end()); }
	bool resetIterations();

	BiasFieldCorrector();
	~BiasFieldCorrector();

	bool readSchedule(std::string ifname);
	bool loadDefaultSchedule();
	bool computeNextPoint();
	int innerLoop();
	bool correct(Vol3D<float> &vSpline, Vol3DBase *vIn, Vol3D<uint8> &vMask);
	bool correct();

	std::string error;
	void removeBias(Vol3D<uint8> &va);
	void removeBias(Vol3D<uint16> &vs) { 	spline.removeBiasMasked((short *)vs.start(),vol.start()); }
	void removeBias(Vol3D<float> &vf) { 	spline.removeBiasMasked(vf.start(),vol.start()); }
	void computeBiasPoints();
	void useTruth();
	void saveBiasPoints();
	bool loadPrevious();
	void computeSpline();
	void computeField(Vol3D<float> &f);
	void computeFieldMasked(Vol3D<float> &f);
	void generateOutput();
	void saveBiasFieldByte(std::string ofname, bool useMask);
	void saveBiasFieldFloat(std::string ofname, bool useMask);
	void saveCorrectedVolume(std::string ofname, bool useMask);
	void save(char *ofname);
	void prune(std::vector<BiasInfo> &bi, const int nx, const int ny, const int nz, float threshmult);
	int localSmoothness(std::vector<BiasInfo> &bi, const int nx, const int ny, const int nz, float thresh=-1, float threshmult=1);
  template <class T> bool initialize(Vol3D<T> &vIn, Vol3D<uint8> &vMask);
  bool initialize(Vol3DBase *vIn, Vol3D<uint8> &vMask);
  bool initializeIterations(Vol3DBase *vIn, Vol3D<uint8> &vMask);
  bool performAllIterations(Vol3DBase *vIn, Vol3D<uint8> &vMask, Vol3D<float> &vSpline);
  Vol3D<uint8> vol;
	Vol3D<uint8> biasEstimateMask;		// mask for spline fit
	Vol3D<uint16> biasEstimateIndex; // indicates which bias estimates go where
	Vol3D<float32> biasSampleField;		// mask for spline fit
	Vol3D<uint8> mask;
	Vol3D<uint8> biasCentroids;
	std::vector<BiasInfo> biasInfo;	// compacted sampled bias field; one float for each
	std::vector<float> biasPoints;
	std::vector<BiasFieldCorrector::IterationParameters> schedule;
	int histogramRadius;
	int biasEstimateSpacing;
	int controlPointSpacing;
	float splineLambda;
	std::pair<float,float> biasRange;

	enum ROIType { Ellipsoid = 0, Block = 1 };
	ROIType roiType;
	bool debug;
	bool timer;
	int verbosity;

	float neighborhoodThreshold;
	bool scaleVariance;
  float varScale; //(-1.0), <= 0 means not specified
  float epsilon;
	float biasEpsilon;
	bool center;
  bool smooth;
	bool replaceWithMean;
	int nBiasPoints;
	uint8 *maskdata;
	bool correctWholeVolume;
	bool iterative;
	bool needFullField;
	std::string imagePrefix; // for saving iterations
  std::string biasPrefix;  // for saving iterations
	OutputType outputType;
	bool halt;
  RegularizedSplineF spline;
};

#endif
