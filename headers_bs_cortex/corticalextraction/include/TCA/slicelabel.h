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

#ifndef SliceLabel_H
#define SliceLabel_H

#include <iostream>

class SliceLabel {
public:
  SliceLabel(int id=-1, int slice=-1, int trueID=-1) : id(id), slice(slice), trueID(trueID) {}
	short id;
	short slice;
	short trueID;
  bool operator==(const SliceLabel &l) const
	{
		return ((slice==l.slice)&&(id==l.id));
	}
};

inline std::ostream& operator<<(std::ostream &s, const SliceLabel &a)
{
  return s<<a.id;
}

#endif
