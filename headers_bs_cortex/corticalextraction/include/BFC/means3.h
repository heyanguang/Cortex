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

#ifndef Means3_H
#define Means3_H
#include <DS/histogram.h>
#include <PVC/tissuelabels.h>
#include <math.h>

class Means3 {
public:
	Means3() : mean0(0), mean1(0), mean2(0),
		var0(0), var1(0), var2(0),std0(0), std1(0), std2(0),
		useModeForCSF(false), useModeForGrey(false),
		useModeForWhite(false) {}
	float mean0;
	float mean1;
	float mean2;
	float var0;
	float var1;
	float var2;
	float var;
	float std;
	float std0,std1,std2;
	float p0;
	float p1;
	float p2;
	bool useModeForCSF;
	bool useModeForGrey;
	bool useModeForWhite;
	void scaleVariance(float f)
	{
		if (f<=0) return;
		float f_2 = (float)sqrt(f);
		std  *= f_2;
		std0 *= f_2;
		std1 *= f_2;
		std2 *= f_2;
		var  *= f;
		var0 *= f;
		var1 *= f;
		var2 *= f;
	}
};

template<class DecisionRule>
class Means3T : public Means3 {
public:
	void compute(Histogram h);
	void computeVariance(Histogram h);
};

int findmode(int *count, uint8 *labels, uint8 seeking);

template <class DecisionRule>
void Means3T<DecisionRule>::compute(Histogram h)
{
	int start = 255; int stop = 0;
	for (int i=0;i<256;i++)
		if (h.count[i]) { start = i; break; }
	for (int i=255;i>=0;i--)
		if (h.count[i]) { stop  = i; break; }
	int range = stop - start;
	float m0 = start + range * 0.25f;
	float m1 = start + range * 0.5f;
	float m2 = start + range * 0.75f;
	mean0 = m0;
	mean1 = m1;
	mean2 = m2;
	var0 = var1 = var2 = 1.0f;
	std0 = std1 = std2 = 1.0f;
	p0 = p1 = p2 = 1.0f/3.0f;
	float v0;
	float v1;
	float v2;
	DecisionRule rule;
	for (int i=0;i<40;i++)
	{
		m0 = m1 = m2 = 0;
		v0 = v1 = v2 = 0;
		int count0 = 0;
		int count1 = 0;
		int count2 = 0;
		p0 = p1 = p2 = 1.0f / 3.0f; //
		var0 = var1 = var2 = 1.0f;  //
		uint8 *map = rule.makeMap(*this);
		for (int j=0;j<256;j++)
		{
			switch (map[j])
			{
				case TissueLabels::CSF :
					count0 +=     h.count[j];
					m0     +=   j*h.count[j];
					v0     += j*j*h.count[j];
					break;
				case TissueLabels::GM :
					count1 +=     h.count[j];
					m1     +=   j*h.count[j];
					v1     += j*j*h.count[j];
					break;
				case TissueLabels::WM :
					count2 +=     h.count[j];
					m2     +=   j*h.count[j];
					v2     += j*j*h.count[j];
					break;
			}
		}
		m0/=count0; var0=v0/count0-square(m0);
		m1/=count1; var1=v1/count1-square(m1);
		m2/=count2; var2=v2/count2-square(m2);
		float error = square(m0-mean0) + square(m1-mean1) + square(m2-mean2);
		mean0 = m0; mean1 = m1; mean2 = m2;
		p0 = count0/float(count0+count1+count2);
		p1 = count1/float(count0+count1+count2);
		p2 = count2/float(count0+count1+count2);
		if (error<0.01) break;
	}
	if (m0>m2) { std::swap(m0,m2); std::swap(var0,var2); std::swap(p0,p2); }
	if (m1>m2) { std::swap(m1,m2); std::swap(var1,var2); std::swap(p1,p2); }
	if (m0>m1) { std::swap(m0,m1); std::swap(var0,var1); std::swap(p0,p1); }
	mean0 = m0;
	mean1 = m1;
	mean2 = m2;
	if (useModeForCSF||useModeForGrey||useModeForWhite)
	{
		uint8 *map = rule.makeMap(*this);
		if (useModeForCSF)
		{
			int m = findmode(h.count,map,TissueLabels::CSF);
			if (m>=0) mean0 = (float)m;
		}
		if (useModeForGrey)
		{
			int m = findmode(h.count,map,TissueLabels::GM);
			if (m>=0) mean1 = (float)m;
		}
		if (useModeForWhite)
		{
			int m = findmode(h.count,map,TissueLabels::WM);
			if (m>=0) mean2 = (float)m;
		}
	}
	uint8 *map = rule.makeMap(*this);
	int count0 = 0;
	int count1 = 0;
	int count2 = 0;
	v0 = 0;
	v1 = 0;
	v2 = 0;
	for (int j=0;j<256;j++)
	{
		switch (map[j])
		{
			case TissueLabels::CSF :
				count0 +=     h.count[j];
				v0     += square(mean0 - j)*h.count[j];
				break;
			case TissueLabels::GM :
				count1 +=     h.count[j];
				v1     += square(mean1 - j)*h.count[j];
				break;
			case TissueLabels::WM :
				count2 +=     h.count[j];
				v2     += square(mean2 - j)*h.count[j];
				break;
		}
	}
	var0 = v0/count0;
	var1 = v1/count1;
	var2 = v2/count2;
	var = (v0+v1+v2)/(count0+count1+count2);
	p0 = count0/float(count0+count1+count2);
	p1 = count1/float(count0+count1+count2);
	p2 = count2/float(count0+count1+count2);
	std0 = (float)sqrt(var0);
	std1 = (float)sqrt(var1);
	std2 = (float)sqrt(var2);
	std = float(sqrt(var));
}

template <class DecisionRule>
void Means3T<DecisionRule>::computeVariance(Histogram h)
{
	p0 = p1 = p2 = 1.0f / 3.0f; //
	var0 = var1 = var2 = 1.0f;  //
	DecisionRule rule;
	uint8 *map = rule.makeMap(*this);
	int count0 = 0;
	int count1 = 0;
	int count2 = 0;
	float v0 = 0;
	float v1 = 0;
	float v2 = 0;
	for (int j=0;j<256;j++)
	{
		switch (map[j])
		{
			case TissueLabels::CSF :
				count0 +=     h.count[j];
				v0     += square(mean0 - j)*h.count[j];
				break;
			case TissueLabels::GM :
				count1 +=     h.count[j];
				v1     += square(mean1 - j)*h.count[j];
				break;
			case TissueLabels::WM :
				count2 +=     h.count[j];
				v2     += square(mean2 - j)*h.count[j];
				break;
		}
	}
	var0 = v0/count0;
	var1 = v1/count1;
	var2 = v2/count2;
	var = (v0+v1+v2)/(count0+count1+count2);
	p0 = count0/float(count0+count1+count2);
	p1 = count1/float(count0+count1+count2);
	p2 = count2/float(count0+count1+count2);
	std0 = (float)sqrt(var0);
	std1 = (float)sqrt(var1);
	std2 = (float)sqrt(var2);
	std = float(sqrt(var));
}

#endif
