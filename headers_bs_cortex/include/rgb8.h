// Copyright (C) 2016 The Regents of the University of California
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

#ifndef RGB8_H
#define RGB8_H

#include <dspoint.h>
#include <vol3ddatatypes.h>

class rgb8 {
public:
  rgb8(const DSPoint &d) : r((uint8)d.x), g((uint8)d.y), b((uint8)d.z) {}
  rgb8(const uint8 r=0, const uint8 g=0, const uint8 b=0) : r(r), g(g), b(b) {}
  uint8 r,g,b;
};

#endif
