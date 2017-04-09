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

#ifndef TCA_DAD_H
#define TCA_DAD_H

#include <vector>

template<class Link>
class DAD {
public:
	DAD(const int nEdges) : dad(nEdges,-1)
  {
  }
  bool find(const Link &link, bool mark = true)
  {
    int i=link.a.id;
    int j=link.b.id;
    while (dad[i]>0) i = dad[i];
    while (dad[j]>0) j = dad[j];
    if ((mark)&&(i!=j)) dad[j] = i;
    return (i!=j);
  }
private:
  std::vector<int> dad;
};


#endif
