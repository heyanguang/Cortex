// Copyright (C) 2016 The Regents of the University of California and
// the University of Southern California
//
// Created by David W. Shattuck, Ph.D.
//
// This file is part of Vol3D.
//
// Vol3D is free software; you can redistribute it and/or
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

#ifndef RegionInfo_H
#define RegionInfo_H

#include <vol3ddatatypes.h>

class RegionInfo {
public:
  RegionInfo() : label(0), count(0), selected(0), cx(0), cy(0), cz(0)  {}
  sint32 label;
  sint32 count;
  sint32 selected;
  uint64 cx, cy, cz; // centroid
};

#endif
