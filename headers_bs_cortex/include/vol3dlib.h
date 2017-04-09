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

#ifndef Vol3DLib_H
#define Vol3DLib_H

#include <vol3d.h>
#include <libversiontext.h>

// For Microsoft Visual C++, links the correct versions of vol3d and zlib
#ifndef QT_BUILD
#ifdef _MSC_VER
#define VOL3DLIB "vol3d" LIBVERSIONTEXT
#define ZLIB "zlib" LIBVERSIONTEXT
#pragma message("will link with " VOL3DLIB " and " ZLIB)
#pragma comment(lib,VOL3DLIB)
#pragma comment(lib,ZLIB)

#endif
#endif

#endif // Vol3DLib_H
