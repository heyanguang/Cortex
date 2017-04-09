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

#ifndef VectorUtil_H
#define VectorUtil_H

namespace SILT {

template <class Stream, class T>
inline void writeWord(Stream &s, const T &v) { s.write((char *)&v, sizeof(v)); }

template <class Stream, class Vector>
inline void writeToStream(Stream &outputStream, Vector &vec)
{
  outputStream.write((char *)&vec[0],(std::streamsize)vec.size()*sizeof(vec[0]));
}

template <class Stream, class Vector>
inline void readFromStream(Stream &outputStream, Vector &vec)
{
  outputStream.read((char *)&vec[0],(std::streamsize)vec.size()*sizeof(vec[0]));
}

}

#endif
