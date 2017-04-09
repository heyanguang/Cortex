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

#ifndef IPoint3D_H
#define IPoint3D_H

#include <point3d.h>
#include <iostream>

inline std::istream& operator>>(std::istream& s, IPoint3D& p)
{
  return s>>p.x>>p.y>>p.z;
}

inline std::ostream& operator<<(std::ostream& s, const IPoint3D& p)
{
  return s<<p.x<<' '<<p.y<<' '<<p.z;
}

#endif
