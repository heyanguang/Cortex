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

#ifndef SILT_ByteSwap_H
#define SILT_ByteSwap_H

namespace SILT {
inline void wordswap(unsigned int &X)
{
  SILT::endian_swap(X);
}

template <class T>
inline void byteswap(T *, const size_t )
// default action is to do nothing, overridden below
{
}

inline void byteswap(sint16 *p, const size_t n)
{
  unsigned short *d = (unsigned short *)p;
  for (size_t i=0;i<n;i++)
    SILT::endian_swap(d[i]);
}

inline void byteswap(uint16 *p, const size_t n)
{
  unsigned short *d = (unsigned short *)p;
  for (size_t i=0;i<n;i++)
    SILT::endian_swap(d[i]);
}

inline void byteswap(sint32 *p, const size_t n)
{
  unsigned int *d = (unsigned int *)p;
  for (size_t i=0;i<n;i++) wordswap(d[i]);
}

inline void byteswap(uint32 *p, const size_t n)
{
  unsigned int *d = (unsigned int *)p;
  for (size_t i=0;i<n;i++) wordswap(d[i]);
}

inline void byteswap(float32 *p, const size_t n)
{
  unsigned int *d = (unsigned int *)p;
  for (size_t i=0;i<n;i++) wordswap(d[i]);
}
} // end of namespace SILT

#endif
