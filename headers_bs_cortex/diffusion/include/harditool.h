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

#ifndef HARDITool_H
#define HARDITool_H 

#include <odffactory.h>

class HARDITool {
public:
  enum { MAX_ODFs = ODFFactory::NBasisFunctions };
  HARDITool();
  bool isFRACT;
  int samplingRes;
  int filecount;
  void updateBasis();
  int setMaxCoefficient(const int n);
  bool loadSHClist(std::string filename);
  bool makeODFVolume(Vol3D<Coefficients> &vODF, Vol3D<float32> vODFC[], const int nCoeffs);
  float generalizedFractionalAnisotropy(const Coefficients &coeff, const size_t n);
  bool nonzero(const Coefficients &coeff, const size_t n);
  float l2norm(const Coefficients &coeff, const size_t n);
  Vol3D<float32> vODFC[MAX_ODFs];
  Vol3D<float32> vGFA;
  Vol3D<Coefficients> vODF;
  void computeGFA(Vol3D<float32> &vGFA);
  void computeGFA();
  ODFFactory odfFactory;
  EigenSystem3x3f findODFMaxima(const int x, const int y, const int z) const;
};

#endif
