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

#ifndef ConnectionList_H
#define ConnectionList_H

#include <vector>
#include <algorithm>

class ConnectionList {
public:
  ConnectionList() {}
  size_t size() const { return list.size(); }
  void clear() { list.clear(); }
  int *begin() { return &list[0]; }
  int operator[](const int n) const { return list[n]; }
  void insert(const int n)
  {
    if (std::find(list.begin(),list.end(),n)==list.end())
    {
      list.push_back(n);
    }
  }
private:
  std::vector<int> list;
};

#endif
