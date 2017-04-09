// Copyright (C) 2016 The Regents of the University of California
//
// Created by David W. Shattuck, Ph.D.
//
// This file is part of HemiSplit.
//
// HemiSplit is free software; you can redistribute it and/or
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

#ifndef BrainSplitter_H
#define BrainSplitter_H

#include <surface.h>
#include <vol3d.h>
#include <vector>

class BrainSplitter {
public:
	static bool biggest(const std::pair<int,int> &a, const std::pair<int,int> &b)
	{
		return a.second>b.second;
	}
	static int clamp(const float x, const int cx)
	{
		if (x<0) return 0;
		if (x>=cx-1) return cx-1;
		return (int) x;
	}
  static bool under(const Point3D<int> &p1, const Point3D<int> &p2)
	{
		return (p1.x<p2.x)&&(p1.y<p2.y)&&(p1.z<p2.z);
	}
	static void initLabels(SILT::Surface &brain, Vol3D<uint8> &labels);
	static bool split(SILT::Surface &brain, Vol3D<uint8> &labels, SILT::Surface &left, SILT::Surface &right, std::vector<int>  &leftMap, std::vector<int>  &rightMap);
	static bool mapVertices(SILT::Surface &dst, SILT::Surface &src, std::vector<int> &map);
	static int  segmentSurface(std::vector<int> &surfaceLabel, const SILT::Surface &brain);
	static void grabSurface(SILT::Surface &left, const SILT::Surface &brain, const std::vector<uint8> &vertexLabels, const int CODE);
  static void labelTriangles(std::vector<uint8> &triangleID, const SILT::Surface &brain);
};

#endif
