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

#ifndef ClampCopy_H
#define ClampCopy_H

#include <vol3d.h>

class ClampCopy {
public:
	template <class S, class T>
	static S dclamp(const T&t, const T &min, const T &max) { return (S)((t>min) ? ((t<max) ? t : max) : min); }

	template <class T> static void clamp(uint8 &dst, const T&t) { dst = dclamp<uint8,T>(t,0,255); }
	template <class T> static void clamp(sint8 &dst, const T&t) { dst = dclamp<sint8,T>(t,SCHAR_MIN,SCHAR_MAX); }
	template <class T> static void clamp(uint16 &dst, const T&t) { dst = dclamp<uint16,T>(t,0,USHRT_MAX); }
	template <class T> static void clamp(sint16 &dst, const T&t) { dst = dclamp<sint16,T>(t,SHRT_MIN,SHRT_MAX); }
	template <class T> static void clamp(uint32 &dst, const T&t) { dst = dclamp<uint16,T>(t,0,ULONG_MAX); }
	template <class T> static void clamp(sint32 &dst, const T&t) { dst = dclamp<sint16,T>(t,LONG_MIN,LONG_MAX); }
	template <class T> static void clamp(float32 &dst, const T&t) { dst = (float32)t; }
	template <class T> static void clamp(float64 &dst, const T&t) { dst = t; }

	template <class DstType, class SrcType>
	static bool copy(Vol3D<DstType> &vOut, Vol3D<SrcType> &vIn)
	{
		if (!vOut.makeCompatible(vIn)) return false;
		const int ds = vOut.size();
		for (int i=0;i<ds;i++) clamp<SrcType>(vOut[i],vIn[i]);
		return true;
	}

	static bool vcopy(Vol3D<float> &vOut, Vol3DBase *vIn);
	static bool vcopy(Vol3DBase *vOut, Vol3D<float> &vIn);	
};

#endif
