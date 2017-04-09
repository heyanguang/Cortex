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

#ifndef TCAFixForeground_H
#define TCAFixForeground_H

#include <vector>
#include <vol3d.h>
#include <TCA/slicetemplates.h>
#include <TCA/seeker.h>
#include <TCA/edgetable.h>
#include <TCA/maximalspanningtree.h>
#include <TCA/link.h>

class TCAFixForeground {
// TCAForeground analysis class. Segments a 3D volume and returns the genus of the associated foreground graph.
public:
  TCAFixForeground();
  ~TCAFixForeground();
  int analyze(Vol3D<uint8> &vin); // analyze the volume;
  void labelSlices(Vol3D<uint8> &vin);  // label each slice in the foreground
  void findAndRemove(sint16 *s, sint16 *slice1, sint16 *slice2, const int cx, const int cy);
  int findNextFix(const int t); // find the next topology error to remove
  int fixNext(Vol3D<uint8> &vin); // fix the next problem
  int fixNextG(Vol3D<uint8> &vIn, const int thresh);
  int thresh() { return thresh_; }
  Vol3D<sint16> foregroundLabels;			// foreground labels
  Vol3D<uint8>  intersect;		// scratch volume for merging
  Vol3D<sint16> labels;
  static Vol3D<uint8> vtest;
  SliceT<uint8> sliceBuffer;
  SliceT<uint8> s1,s2,s3;
  EdgeTable<Link> edgeTable;
  MaximalSpanningTree<Link> mst;
  Seeker seeker;
  std::vector<int> nsym;
  std::vector<int> offset;
  int smallest;
  int largestFGChange;
  bool verbose;
  int currentEdge;
  int thresh_;
  bool tryFixes(Vol3D<uint8> &vin, const int thresh); // try to fix it, testing for probs.
};

#endif
