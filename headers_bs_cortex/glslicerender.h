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

#ifndef GLSliceRender_H
#define GLSliceRender_H

#include <vol3d.h>

template <class T> void renderSliceXY(const Vol3D<T> &vol, const int slice, const float bright);
template <class T> void renderSliceXZ(const Vol3D<T> &vol, const int slice, const float bright);
template <class T> void renderSliceYZ(const Vol3D<T> &vol, const int slice, const float bright);
template <class T> void renderSliceXYM(const Vol3D<T> &vol, const Vol3D<uint8> &mask, const int slice, const float bright);
template <class T> void renderSliceXZM(const Vol3D<T> &vol, const Vol3D<uint8> &mask, const int slice, const float bright);
template <class T> void renderSliceYZM(const Vol3D<T> &vol, const Vol3D<uint8> &mask, const int slice, const float bright);

#endif
