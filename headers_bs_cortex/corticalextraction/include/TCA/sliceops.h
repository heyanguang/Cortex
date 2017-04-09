// Copyright (C) 2016 The Regents of the University of California and
// the University of Southern California
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

#ifndef SliceOps_H
#define SliceOps_H

namespace SliceOps {

template <class T, class S>
inline int overlap(T *dst, SliceT<S> &src)
{
	const int ss = src.slicesize;
	int n=0;
	for (int i=0;i<ss;i++) if (src[i]&&dst[i]) n++;
	return n;
}

template <class T, class S>
inline void set(T *dst, SliceT<S> &src, const T n)
{
	const int ss = src.slicesize;
	for (int i=0;i<ss;i++) dst[i] = (src[i]) ? n : 0;
}

template <class T, class S>
inline void incr(T *dst, SliceT<S> &src, const T n)
{
	const int ss = src.slicesize;
	for (int i=0;i<ss;i++) if (src[i]) dst[i] += n;
}

template <class T>
inline void copy(T *dst, SliceT<T> &src)
{
	const int ss = src.slicesize;
	for (int i=0;i<ss;i++) dst[i] = src[i];
}

template <class T>
inline void opOr(uint8 *dst, SliceT<T> &src)
{
	const int ss = src.slicesize;
	for (int i=0;i<ss;i++) dst[i] += (src[i] ? 1 : 0);
}

inline void select(SliceT<uint8> &dst, const sint16 *src, const sint16 labelID)
{
	const int slicesize = dst.cx*dst.cy;
	for (int i=0;i<slicesize;i++)
		dst[i] = ((src[i]==labelID) ? 255 : 0);
}

template <class DataType>
inline void intersect(SliceT<uint8> &dst, const DataType *src) // equivalent to masking by non-zeros.
{
	const int slicesize = dst.cx*dst.cy;
	for (int i=0;i<slicesize;i++) if (!src[i]) dst[i] = 0;
}

inline void intersect(SliceT<uint8> &dst, const SliceT<uint8> &src) // equivalent to masking by non-zeros.
{
	const int slicesize = dst.cx*dst.cy;
	for (int i=0;i<slicesize;i++) if (!src[i]) dst[i] = 0;
}

inline void intersect(SliceT<uint8> &dst, const SliceT<uint8> &srcA, const SliceT<uint8> &srcB) // equivalent to masking by non-zeros.
{
	const int slicesize = dst.cx*dst.cy;
	for (int i=0;i<slicesize;i++) dst[i] = (srcA[i]&srcB[i]) ? 255 : 0;
}

inline void dilate4(SliceT<uint8> &dst, const SliceT<uint8> &src)
// N.B. - this doesn't go to the edges
{
	const int cx = src.cx;
	const int cy = src.cy;
	dst.set(0);
	for (int y=1;y<cy-1;y++)
	{
		int id = y * cx + 1;
		for (int x=1;x<cx-1;x++,id++)
		{
			dst[id] =   src[id-cx]|
				src[id-1]|src[id   ]|src[id+1]
					       |src[id+cx];
		}
	}
}


template <class T>
int count(SliceT<T> &slice)
{
	const int ss = slice.slicesize;
	int cnt=0;
	for (int i=0;i<ss;i++)
		if (slice[i]) cnt++;
	return cnt;
}

inline int findFirst(SliceT<uint8> &sliceCurrent)
{
	int pos=-1;
	const int ss = sliceCurrent.slicesize;
	for (int i=0;i<ss;i++)
	{
		if (sliceCurrent[i]) { pos=i; break; }
	}
	return pos;
}
inline void andSlice(uint8 *r, const uint8 *a, const uint8 *b, const int slicesize)
{
  const uint8 *s = r + slicesize;
  while (r!=s)
  {
    *r++ = (*a++)&(*b++);
  }
}

inline void checkInfo(sint16 *slice, sint16 l, SliceRegionInfo &info, const int ss)
{
  int n = 0;
  int id = 0;
  for (int i=0;i<ss;i++)
  {
    if (slice[i]==l)
    {
      n++;
      if (id==0) id = i;
    }
  }
  info.count = n;
  info.idx = id;
}

inline void select(const sint16 *l, uint8 *d, const sint16 s, const int slicesize)
{
  for (int i=0;i<slicesize;i++)
    d[i] = (l[i]==s) ? 255 : 0;
}

inline int count(SliceT<uint8> &sb)
{
  const int ss = sb.slicesize;
  uint8 *s = sb.data;
  int n=0;
  for (int i=0;i<ss;i++) n += (s[i]!=0);
  return n;
}

inline void subSliceX(uint8 *d, uint8 *m, int slicesize)
{
  for (int i=0;i<slicesize;i++)
  {
    if (m[i]) d[i] = 0;
  }
}

inline bool isSubset(const uint8 *a, const uint8 *b, const int s)
{
  for (int i=0;i<s;i++)
  {
    if (a[i])
      if (!b[i]) return false;
  }
  return true;
}

inline void subSlice(uint8 *r, const uint8 *a, const uint8 *b, const int slicesize)
{
  const uint8 *s = r + slicesize;
  while (r!=s)
  {
    *r = (*b==0) ? *a : 0;
    r++; a++; b++;
  }
}

inline void subSlice(uint8 *r, const uint8 *b, const int slicesize)
{
  subSlice(r,r,b,slicesize);
}

inline void andAdjacentSlices(Vol3D<uint8> &vIntersect, const Vol3D<uint8> &vInput)
{
  vIntersect.makeCompatible(vInput);
  vIntersect.set(0);
  const int slicesize = vInput.cx * vInput.cy;
  const int nz = vInput.cz - 1;
  for (int i=1;i<nz;i++)
    SliceOps::andSlice(vIntersect.slice(i),vInput.slice(i),vInput.slice(i+1),slicesize);
}
}
#endif
