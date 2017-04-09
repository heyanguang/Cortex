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

#ifndef LinkBG_H
#define LinkBG_H

#include <TCA/slicelabel.h>

class CorrectionIndexBG {
public:
  CorrectionIndexBG(const int slice_=-1, const int sliceLabelA_=-1, const int label_=-1) : slice(slice_), sliceLabelA(sliceLabelA_), label(label_) {}
	int slice;
	int sliceLabelA;
	int label;
};

class LinkBG {
public:
  LinkBG() {}
  LinkBG(const SliceLabel &a, const SliceLabel &b) : a(a), b(b), weight(0), weightA(0), weightB(0), id(-1), index(-1), tag(-1) {}
  SliceLabel a,b;
	float weight;
	float weightA,weightB;
	int id;
	int index;
	int tag;
  CorrectionIndexBG correctionIndex;
  bool operator<(const LinkBG &l) const { return weight<l.weight; }
  bool operator>(const LinkBG &l) const { return weight>l.weight; }
};

#endif
