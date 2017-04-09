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

#ifndef PVC_PartialVolumeModel_H
#define PVC_PartialVolumeModel_H

#include <vector>
#include <vol3d.h>

class PartialVolumeModel {
public:
    PartialVolumeModel(int verbosity) : verbosity(verbosity) {}
    enum { MeanCSF=0, MeanGM=1, MeanWM=2, Stdev=3, PCSF=4, PGM=5, PWM=6, PCG=7, PGW=8, PCO=9 };
    enum { CSF=0, GM=1, WM=2, CG=3, GW=4, CO=5 }; // these are for internal indexing only; IDs were changed
    void generatePmeas(const float theta[]);
    void classify6(Vol3D<uint8> &vb, Vol3D<uint8> &vl, float theta[]);
    int ICM(Vol3D<uint8> &vb, Vol3D<uint8> &vl, float theta[], float lambda, const int maxIterations);
    void crisp(Vol3D<uint8> &vImage, Vol3D<uint8> &vLabel, float theta[]);
    void pX(std::vector<float> &pdf, float theta[10]);
    void pPure (std::vector<float> &pdf, float m, float sigma);
    void pMixed(std::vector<float> &pdf, float u, float v, float sigma);
    void cluster3(std::vector<int> &histogram, float theta[]);	// three class cluster model.
    void cluster6(std::vector<int> &histogram, float theta[]);	// six class cluster model.
    void initICM(float theta[]);
    void initTheta(const std::vector<float> &histogram, float theta[]);
    std::vector< std::vector<float> > logLikelihood;
    std::vector<float> pt[6];		// tissue pdfs (p(x|l=CSF), etc).
    int verbosity;
private:
    float computeVariance(int *p, int n);
    int findPeak(const int *d, int n);
    int findPeak(const int *d, int m, int n);
    float average(float a, float b);
    float square(const float f);
    float square(const int f);
    float gmixed(float x, float u, float v, float s);
    float merf(const float f);
    static int cliquePotential1stOrder[9][9];
    static float cliquePotential2ndOrder[9][9];
    static const float SR2;
    static const float SPI;
    static const float SQRT2PI;
    static const int backgroundLabel;
};

#endif
