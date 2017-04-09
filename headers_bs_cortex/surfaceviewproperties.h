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

#ifndef SurfaceViewProperties_H
#define SurfaceViewProperties_H

class SurfaceViewProperties {
public:
  SurfaceViewProperties() :
    showXYPlane(true), showXZPlane(true), showYZPlane(true),
    useAlpha(false), drawCube(true), useVolumeBlending(true), smoothShading(true)
	{}
	bool showXYPlane;
	bool showXZPlane;
	bool showYZPlane;
	bool useAlpha;
	bool drawCube;
	bool useVolumeBlending;
	bool smoothShading;
};

#endif
