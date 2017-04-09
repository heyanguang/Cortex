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

#ifndef TCA_Link_H
#define TCA_Link_H

#include <TCA/slicelabel.h>

class Link {
public:
	Link() : weight(0), id(-1), index(-1), tag(-1) {}
  Link(SliceLabel a, SliceLabel b) : a(a), b(b), weight(0), id(-1), index(-1), tag(-1) {}
	SliceLabel a,b;
	float weight;
	int id;
	int index;
	int tag;
  bool operator<(const Link &l) const { return weight<l.weight; }
  bool operator>(const Link &l) const { return weight>l.weight; }
};

#endif
