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

#ifndef SurfLib_H
#define SurfLib_H

#include <list>
#include <surface.h>
#include <libversiontext.h>
#include <vol3ddatatypes.h>

#ifndef QT_BUILD
#ifdef _MSC_VER
#define SURFLIB "surflib" LIBVERSIONTEXT
#pragma message("will link with " SURFLIB)
#pragma comment(lib,SURFLIB)
#endif
#endif

typedef SILT::Surface Surface;

class SurfLib {
public:
  typedef std::list<int> EdgeList;
  static void computeCurvature(Surface &surface); // really the convexity
  static void computeGaussianCurvature(std::vector<float> &vGaussianCurvature, Surface &surface);
  static int  segmentSurface(std::vector<int> &surfaceLabels, const Surface &brain);
  static void fastFill(Surface &surface, bool verbose=false);
  static void smoothCurvature(Surface &surf, const float alpha = 0.5f);
  static void erode(Surface &dfs, std::vector<uint8> &v);
  static void dilate(Surface &dfs, std::vector<uint8> &v);
  static bool findBorders(std::vector<uint16> &boundaryPoints, Surface &surface, const int structure);
  static bool sortBorders(std::list< std::list<int> >&borders, std::vector<uint16> &boundaryPoints, Surface &surface);
  static void laplaceSmooth(Surface &surface, const int n, const float alpha);
  static void laplaceSmoothCurvatureWeighted(Surface &s, int niter, float alpha, float c);
  static void selectLargestPatches(Surface &surface);
  static void revtri(Surface &s);
  static bool verbose;
};

#endif
