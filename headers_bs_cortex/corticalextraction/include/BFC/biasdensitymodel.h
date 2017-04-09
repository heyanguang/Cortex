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

#ifndef BiasDensityModel_H
#define BiasDensityModel_H
#include <BFC/means3.h>
#include <BFC/weighting.h>

class BiasDensityModel {
public:
	enum { NClasses = 6, NParameters = 7 };
	enum { IBias = 6 };
	BiasDensityModel();
	~BiasDensityModel();
	float werror(float *a, float *b, float *w, int n=256);
  void fit(float h[], const Means3& m, float *theta0,	Weighting::Types weighting);
	void makeHistogram(float h[], const Means3& m) { makeHistogram(h,m,theta); }
	void makeHistogram(float h[], const Means3& m, float theta_[NParameters])	{ makeHistogram(h,m,theta_[IBias],theta_); }
	void computePv(float *P[NClasses],	float ic, float ig, float iw, float sigma, float beta);
	void computeGPv(float *Gv[NClasses],float *Pv[NClasses],float ic,float ig, float iw, float sigma,float beta);
	void gradient(float gPa[], float h[], float ic, float ig, float iw, float sigma, float thetaK[], float *w=0);
	void ppure(float p[], float m, float s);
	void pmixed(float P[], float ia, float ib, float sigma);
	void pmixed(float P[], float ia, float ib, float sigma, float beta) { pmixed(P,beta*ia,beta*ib,sigma); }
	float gmixed(float v, float ia, float ib, float sigma, float beta);
	void makeHistogram(float h[], const Means3& m, float beta, float pt[]);
	float theta[NParameters];
	float *Pv[NParameters];
	float *GPv[NParameters];
	float R[256];
	float Pa[256];
  float epsilon;
  float biasEpsilon;
	float lastError;
	int lastStop;
	int verbosity;
};

#endif
