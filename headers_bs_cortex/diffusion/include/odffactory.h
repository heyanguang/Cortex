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

#ifndef ODFFactory_H
#define ODFFactory_H

#include <cmath>
#include <vol3d.h>
#include <surflib.h>
#include <slicet.h>
#include <spherebase.h>
#include <vol3d.h>

class Coefficients;
class SurfaceInstanceSet;
class SurfaceInstance;

class ODFFactory {
public:
  enum Values { NBasisFunctions = 45 };
  enum ColorModel { Grey=0, MaxDirection=1, FMI=2, DS=3, DS2=4, R0=5, R2=6, RMulti=7 };
  ODFFactory();
  std::string colormodelName(ColorModel model) const;
  std::string colormodelName() const { return colormodelName(colorModel); }
// helper functions
  DSPoint sph2cart(const float theta, const float phi, const float R);
  float samplePhi(int i, int NX) const;
  float sampleTheta(int i, int NX) const;
  int nonzero(Vol3D<uint8> &vMask, IPoint3D &pMin, IPoint3D &pMax);
// make planes of glyphs
  int setMaxCoefficient(const int n);
  void minmaxODF(Surface &odfSurface, Coefficients &shc);
  void makeGlyph(SurfaceInstance &instance, Vol3D<float32> vSphericalHarmonicCoefficients[], const IPoint3D &voxel);
  void makeGlyphs(SurfaceInstanceSet &instances, Vol3D<float32> vIn[], IPoint3D p0, IPoint3D p1);
  void makeGlyphs(SurfaceInstanceSet &instances, Vol3D<float32> vIn[], Vol3D<uint8> &vMask, IPoint3D p0, IPoint3D p1);
  void makeGlyph(SurfaceInstance &instance, Vol3D<Coefficients> &vSphericalHarmonicCoefficients, const IPoint3D &voxel);
  void makeGlyphs(SurfaceInstanceSet &instances, Vol3D<Coefficients> &vSphericalHarmonicCoefficients, IPoint3D p0, IPoint3D p1);
  void makeGlyphs(SurfaceInstanceSet &instances, Vol3D<Coefficients> &vSphericalHarmonicCoefficients, Vol3D<uint8> &vMask, IPoint3D p0, IPoint3D p1);
  void makeGlyphs(Surface &surface, Vol3D<float32> vIn[], IPoint3D p0, IPoint3D p1, float base);
  void makeGlyphs(Surface &surface, Vol3D<float32> vIn[], Vol3D<uint8> &vMask, IPoint3D p0, IPoint3D p1, float base);
// basis functions
  void makeBasis(Surface &surface, const int level, const int NX);
  void makeBasis(const int resX);
  void newODF (Surface &s, DSPoint position, const std::vector<float> &shc);
  void minmaxODF (Surface &s, const std::vector<float> &shc);
// computed data
  Surface basisFunctions[NBasisFunctions];
  std::vector<float> sphereValues[NBasisFunctions];
  ColorModel colorModel;
  bool constrainRadius;
  bool nonNegative;
  bool flipX,flipY,flipZ;
  int nCoefficients;
  float scale;
  bool normalize;
  SphereBase sphereBase;
  std::string message;
};

class Coefficients {
public:
  float32 d[ODFFactory::NBasisFunctions];
  float32 operator[](const size_t &idx) const { return d[idx]; }
  Coefficients()
  {
  }
  Coefficients(const float32 v)
  {
    std::fill(d,d+ODFFactory::NBasisFunctions,v);
  }
};



#endif
