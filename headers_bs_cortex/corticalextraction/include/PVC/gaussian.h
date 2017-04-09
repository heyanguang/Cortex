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

#ifndef Gaussian_H
#define Gaussian_H
#include <math.h>
// Algorithm AS 66  Appl. Stat. (1973) Vol. 22, No.3
// could possibly be replaced now that erf is in std for C++11.
class Gaussian {
public:
	static double G(double z, int up=0);
	static double erf(double z);
	static double integral(double a, double b);
	static const double a1;
	static const double a2;
	static const double a3;
	static const double b1;
	static const double b2;
	static const double c1;
	static const double c2;
	static const double c3;
	static const double c4;
	static const double c5;
	static const double c6;
	static const double d1;
	static const double d2;
	static const double d3;
	static const double d4;
	static const double d5;
	static const double p;
	static const double q;
	static const double r;
	static const double ltone;
	static const double utzero;
	static const double con;
};

inline double Gaussian::integral(double a, double b)
{
  return (G(b) - G(a));
}

inline double Gaussian::G(double z, int up)
{
	double ret;
	if (z<0)
	{
		up = (!up);
		z = -z;
	}
  if (!(z<ltone||(up&&z<=utzero)))
	{
		ret = 0.0;
	}
	else
	{
		double y = 0.5 * z * z;
		if (z<=con)
			ret=0.5-z*(p-q*y/(y+a1+b1/(y+a2+b2/(y+a3))));
		else
			ret=r*exp(-y)/(z+c1+d1/(z+c2+d2/(z+c3+d3/(z+c4+d4/(z+c5+d5/(z+c6))))));       
	}
	if (!up) ret = 1.0 - ret;
	return ret;
	
}

inline double Gaussian::erf(double x)
{
	return Gaussian::G(x,0) - 0.5;
}

#endif
