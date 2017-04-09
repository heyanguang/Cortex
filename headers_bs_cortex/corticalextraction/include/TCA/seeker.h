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

#ifndef Seeker_H
#define Seeker_H

class Seeker {
public:
	enum { ListSize = 50 };
  int nc;
  int ncn;
  int chains[ListSize][ListSize];
	int mergeList[100][2];

	void insert(int *list, int v)
	{
		for (int i=0;i<ListSize;i++)
		{
			if (list[i] == 0)
			{
				list[i] = v;
				break;
			}
		}
	}
	void mergechains(int a, int b)
	{
		int *ca = chains[a];
		int *cb = chains[b];
		while (*ca++);
		ca--;
    while ((*ca++=*cb++)) {}
    chains[b][0] = 0;
	}
	bool find(int *list, int v)
	{
		for (int i=0;i<ListSize;i++)
		{
			if (list[i] == 0) return false;
			if (list[i] == v) return true;
		}
		return false;
	}
	int find(int a)
	{
		for (int j=0;j<ncn;j++)
		{
			if (find(chains[j],a)) return j;
		}
		return -1;
	}
	void clearMergeLists()
	{
    for (int i=0;i<ListSize;i++)
			for (int j=0;j<ListSize;j++)
        chains[i][j] = 0;
	}
	void setupMergeLists()
	{
		clearMergeLists();
		for (int i=0;i<nc;i++)
		{
			int a = mergeList[i][0];
			int b = mergeList[i][1];
			int la = find(a);
			int lb = find(b);
			if (la==lb) // either on same list or not
			{
				if (la>=0) continue;
				insert(chains[ncn],a);
				insert(chains[ncn],b);
				ncn++;
				continue;
			}
			else if (la<0)
			{
				insert(chains[lb],a);
			}
			else if (lb<0)
			{
				insert(chains[la],b);
			}
			else 
				mergechains(la,lb);
		}
	}
  void findAndRemove(short *s, short *s1, short *s2, int cx, int cy)
	{
    clearMergeLists();
		nc = 0;
		ncn= 0;
		for (int y=0;y<cy-1;y++)
		{
			int idx = y*cx;
			for (int x=0;x<cx-1;x++,idx++)
			{
				int ul = idx;
				int ur = idx+1;
				int ll = idx+cx;
				int lr = idx+cx+1;
				if ((s[ul]==0)&&(s[ur]!=0))
				{
					if ((s[ll]!=0)&&(s[lr]==0))
					{
						if (s[ur]!=s[ll])
						{
							if (((s1[ul]!=0)&&(s2[lr]!=0))
								||((s2[ul]!=0)&&(s1[lr]!=0)))
							{
								mergeList[nc][0] = s[ur];
								mergeList[nc][1] = s[ll];
								++nc;
							}
						}
					}
				}
				else
					if ((s[ul]!=0)&&(s[ur]==0))
				{
					if ((s[ll]==0)&&(s[lr]!=0))
					{
						if (s[ul]!=s[lr])
						{
							if (((s1[ur]!=0)&&(s2[ll]!=0))
								||((s2[ur]!=0)&&(s1[ll]!=0)))
							{
								mergeList[nc][0] = s[ul];
								mergeList[nc][1] = s[lr];
								++nc;
							}
						}
					}
				}
			}
		}
		if (nc>0)
		{
			setupMergeLists();
		}
	}
	void relabelChains(sint16 *s, int n)
	{
		if (nc<1) return;
		for (int a=0;a<ncn;a++)
		{
			int *chn = chains[a];
			int id = chn[0];
			for (int i=1;i<10;i++)
			{
				int id2 = chn[i];
				if (id2==0) break;
				for (int j=0;j<n;j++)
				{
					if (s[j]==id2)
					{
						s[j] = id;						
					}
				}
			}
		}
	}
};

#endif
