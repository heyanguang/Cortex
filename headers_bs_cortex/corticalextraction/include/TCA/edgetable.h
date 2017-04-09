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

#ifndef EdgeTable_H
#define EdgeTable_H

#include <vector>
#include <TCA/dad.h>
#include <TCA/slicelabel.h>

template <class LinkT>
class EdgeTable {
public:
	typedef LinkT LinkType;
  EdgeTable(const EdgeTable &et);
  EdgeTable() : nedges(0), edge(sizeIncrement), maxLinkID(0) {  }
  ~EdgeTable() {  }
	void remove(const int n)
	{
    nedges--;
		for (int i=n;i<nedges;i++)
			edge[i] = edge[i+1];
	}
	void add(const LinkT &link)
	{
		if (nedges>=edge.size())
		{
			edge.resize(edge.size()+sizeIncrement);
		}
    if (link.a.id>maxLinkID) maxLinkID = link.a.id;
    if (link.b.id>maxLinkID) maxLinkID = link.b.id;
    edge[nedges++] = link;
	}
	void clear()
	{
		nedges = 0;
	}
	enum { sizeIncrement = 6000 };
	LinkT *begin() { return &edge[0]; }
	LinkT *end() { return &edge[nedges]; }
	int find(int tag, int id);
  int count(SliceLabel sl) const;
	int genus();
	void show(std::ostream &s);
	size_t nedges;
	std::vector<LinkT> edge;
  int maxLinkID;
};

template <class LinkT>
inline std::ostream &operator<<(std::ostream &s, const EdgeTable<LinkT> & e)
{
	for (int i=0;i<e.nedges;i++)
		s<<e.edge[i]<<'\n';
	s<<std::flush;
	return s;
}

template <class LinkT>
EdgeTable<LinkT>::EdgeTable(const EdgeTable &et)
{
	edge.resize(et.edge.size());
	nedges = et.nedges;
	for (int i=0;i<nedges;i++)
		edge[i] = et.edge[i];
}

template <class LinkT>
int EdgeTable<LinkT>::genus()
{
	int g = 0;
	DAD<LinkT> dad(maxLinkID+1);
	for (size_t i=0;i<nedges;i++)
	{
		if (!dad.find(edge[i])) g++;
	}
	return g;
}

template <class LinkT>
int EdgeTable<LinkT>::find(int tag, int id)
{
	int count = 0;
	for (int i=0;i<nedges;i++)
	{
		if (edge[i].tag == tag)
			if (edge[i].id == id)
				count++;
	}
	return count;
}

template <class LinkT>
int EdgeTable<LinkT>::count(SliceLabel sl) const
{
  int count = 0;
	for (size_t i=0;i<nedges;i++)
	{
    if (edge[i].a == sl) count++;
    if (edge[i].b == sl) count++;
	}
  return count;
}

#endif
