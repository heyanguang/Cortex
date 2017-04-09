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

#ifndef ConnectivityProperties_H
#define ConnectivityProperties_H

#include <vector>
#include <connectivitymap.h>
#include <vol3d.h>

class ConnectivityProperties {
public:
  void sumWeights(ConnectivityMap &connectivityMap, Vol3D<uint16> &vLabel);
  void computeLabelCentroids(Vol3D<uint16> &vLabel);
  std::vector<uint32> count;
  std::vector<DSPoint> labelCentroids;
  std::vector<float32> nodeWeights;
  Vol3D<uint16> vMergedLabels;
  float maxWeight;
};

#endif // ConnectivityProperties_H
