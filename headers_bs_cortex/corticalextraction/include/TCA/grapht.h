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

#ifndef GraphT_H
#define GraphT_H

#include <allocator.h>
#include <vector>

template <class LabelT>
class GraphT {
public:
  class GraphNode {
  public:
    int data;
    GraphNode* next;
  };
  typedef GraphNode *GraphNodePtr;

  GraphT(int blocksize, int stacksize= 300000) : lists(0), tails(0), allocator(blocksize), nlists(0), stacksize(stacksize), stack(stacksize)
  {
  }
  ~GraphT()
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
//  static const int SENTINEL;
  std::vector<GraphNode *> lists;
  std::vector<GraphNode *> tails;
  Allocator<GraphNode> allocator;
  int nlists;
  const int stacksize;
  std::vector<int> stack;
};

template <class LabelT>
void GraphT<LabelT>::link(int a, int b)
{
  GraphNode *node = memcheck(allocator.newNode());
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



template <class LabelT>
int GraphT<LabelT>::makemap(LabelT *map)
{
  int nLabels = 0;//n-1;
  for (int i=0;i<nlists;i++) map[i] = 0;
  for (int i=0;i<nlists;i++)
  {
    if (map[i]==0)
    {
      ++nLabels;
      visit(map, i, nLabels);
    }
  }
  return nLabels;
}

template <class LabelT>
void GraphT<LabelT>::visit(LabelT *map, int iNode, int labels)
{
  GraphNode *node;
  int stackpos = 0;
  stack[stackpos++] = iNode;
  // add a loop over possible stacks
  while (stackpos>0)
  {
    iNode = stack[--stackpos];
    map[iNode] = labels;
    for (node = lists[iNode]; node != 0; node = node->next)
    {
      if (map[node->data]==0)
      {
        stack[stackpos++] = node->data;
        if (stackpos>=stacksize)
        {
          // add additional stack; reset stackpos to 1;
          std::cerr<<"Fatal error: out of stack in GraphT::visit()"<<std::endl;
          std::cerr<<"Stack position is "<<stackpos<<std::endl;
          return;
        }
        map[node->data] = -1;
      }
    }
  }
}

#endif
