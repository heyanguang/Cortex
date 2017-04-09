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

#ifndef RegularizedSplineF_H
#define RegularizedSplineF_H

#include <vol3d.h>
#include <DS/range.h>
#include <vector>

class RegularizedSplineF {
public:
  RegularizedSplineF();
  ~RegularizedSplineF();
  void initializeSplineEnergy();
  float32 splineCrossEnergy(float32 *p1, float32 *p2);
  void create(int x, int y, int z, int dx, int dy, int dz);
  void setMeasured(float32 *m)	{ measured = m; }
  void setMask(uint8 *m);
  float32 cgm();
  unsigned char dclamp(float f) { return (f<255) ? (unsigned char)(f) : 255; }
  short sclamp(float f) { return (f<32767) ? short(f) : 32767; }
  void removeBias(uint8 *img);
  void removeBias(sint16 *img);
  template <class T> void divideInto(Vol3D<T> &vIn); // vIn /= spline
  template <class T> void divideIntoMasked(Vol3D<T> &vIn, Vol3D<uint8> &vMask); // vIn(vMask!=0) /= spline(vMask!=0)
  void removeBiasMasked(uint8 *img, uint8 *imask);
  void removeBiasMasked(sint16 *img, uint8 *imask);
  void removeBiasMasked(float32 *img, uint8 *imask);

  template <class T> void removeBias(Vol3D<T> &vImage)
  {
    removeBias(vImage.start());
  }
  template <class T>
  void removeBiasMasked_t(Vol3D<T> &vImage, Vol3D<uint8> &vMask)
  {
    removeBiasMasked(vImage.start(),vMask.start());
  }
  void computeBias(float32 *b);
  void computeBiasMasked(float32 *b, uint8 *imask);

  Range<float32> computeBiasMasked(uint8 *bias, uint8 *imask);
  Range<float32> computeBias(uint8 *bias);
  float splineLambda;

private:
  void dEdp(std::vector<float> &vec);
  void init();
  void resetCP();
  void computeGradient();
  float32 computeResidual();
  void computeSplineEnergyMatrix();
  void compute(float32 *cp, std::string desc="");
  float32 computeAlpha();
  float32 computeBeta();
  void updateDirection(float32 beta);
  void updateCP(float32 alpha);
  static const float Ib2_[7];
  static const float Idb2_[7];
  static const float Id2b2_[7];

  static const float *Ib2;
  static const float *Idb2;
  static const float *Id2b2;

  float E[4][4][4];
public:
  int verbosity;
  float stopError;
  float stopDelta;
  int stopCount;
private:
  int imagecount; // number of brain voxels.
  int imagesize;
  int cx;					// width of actual image
  int cy;					// width of actual image
  int cz;
  int dx;					// spacing between control points
  int dy;
  int dz;
  int nx;					// number of control points
  int ny;
  int nz;
  int cpsize;
  int czstride;
  float32 *CP;				// vector of control points.
  float32 *bx[4];		// sampled basis functions.
  float32 *by[4];		// sampled basis functions.
  float32 *bz[4];		// sampled basis functions.
  float32 *measured;
  std::vector<float32> residual;
  std::vector<float32> grad;
  std::vector<float32> gradR; // residual gradient
  std::vector<float32> gradS; // smoothness penalty  gradient
  std::vector<float32> gradPrev; // float32 *gradPrev;
  float32 *splineImg;
  uint8 *mask;
  float32 *direx;
  std::vector<float32> energyMatrix;
};

#endif
