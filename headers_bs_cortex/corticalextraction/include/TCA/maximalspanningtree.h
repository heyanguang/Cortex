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

#ifndef MaximalSpanningTree_H
#define MaximalSpanningTree_H

#define MYQ

#include <TCA/priorityqueue.h>
#include <TCA/dad.h>
#include <TCA/edgetable.h>

//TODO: replace priorityqueue with std version
template <class LinkT>
class MaximalSpanningTree {
public:
  EdgeTable<LinkT> tree;
  EdgeTable<LinkT>	dead;
  void create(const EdgeTable<LinkT> &et);
};

template <class LinkT>
void MaximalSpanningTree<LinkT>::create(const EdgeTable<LinkT> &et)
{
	dead.clear();
	tree.clear();
  const size_t N = et.nedges;
  PriorityQueue<LinkT> priorityQueue((int)(N*2));
  for (size_t i=0;i<N;i++)
  {
    priorityQueue.push(et.edge[i]);
  }
	DAD<LinkT> dad(et.maxLinkID+1);
  while (!priorityQueue.empty())
	{
    LinkT l = priorityQueue.remove();
		if (dad.find(l))
			tree.add(l);
		else
			dead.add(l);
	}
}

#endif
