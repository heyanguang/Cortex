// Copyright (C) 2016 The Regents of the University of California and
// the University of Southern California
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

#ifndef VOL3D_Graph_H
#define VOL3D_Graph_H

#include <vol3ddatatypes.h>
#include <allocator.h>
#include <vector>

class Graph {
public:
  class GraphNode {
  public:
    int data;
    GraphNode* next;
  };
  typedef GraphNode *GraphNodePtr;
  typedef int LabelT;
  Graph(int blocksize, int stacksize=1000000) : lists(0), tails(0), allocator(blocksize), nlists(0), stacksize(stacksize), stack(stacksize)
  {
  }
  ~Graph()
  {
  }
  void reset(int n)
  {
    allocator.purge();
    nlists = n;
    lists.resize(nlists);
    tails.resize(nlists);
    for (int i=0;i<nlists;i++)
    {
      tails[i] = 0;
      lists[i] = 0;
    }
  }
  void link(int a, int b);
  int makemap(LabelT *map);
private:
  void visit(LabelT *map, int iNode, int label);
  static const int SENTINEL;
  std::vector<GraphNode *> lists;
  std::vector<GraphNode *> tails;
  Allocator<GraphNode> allocator;
  int nlists;
  const int stacksize;
  std::vector<int> stack;
};

inline void Graph::link(int a, int b)
{
  GraphNode *node = allocator.newNode();
  if (node==0)
  {
    std::cerr<<"Error ("<<__FILE__<<":"<<__LINE__<<") : unable to allocate memory for GraphNodes"<<std::endl;
    return;
  }
  node->data = b;
  node->next = 0;
  if (lists[a]==0)
  {
    lists[a] = node;
    tails[a] = lists[a];
  }
  else
  {
    tails[a]->next = node;
    tails[a] = tails[a]->next;
  }
}

#endif

































