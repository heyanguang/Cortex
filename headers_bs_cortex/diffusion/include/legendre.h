// Copyright (C) 2016 The Regents of the University of California
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

#ifndef Legendre_H
#define Legendre_H

#include <cstdlib>
#include <dspoint.h>
#include <vol3ddatatypes.h>

template <class Float>
class Legendre {
public:
  static Float factor(const int L, const int M)
  {
    Float A = (std::abs(M) & 1) ? -1.0f : 1.0f; // (-1)^M
    sint64 F2=1;
    for (int i=(L-M+1); i<= (L+M); i++) F2 *= i;
    return A/F2;// * fact1 / fact2;
  }
  static Float eval(const int L, const int M_, const Float X)
  {
    int M = abs(M_);
    Float multiplier = (M_>=0) ? 1 : factor(L,M);
    Float pmm=1;
    if (M>0)
    {
      const Float somx2=sqrt((1-X)*(1+X));
      Float fact=1;
      for (int i=1;i<=M;i++)
      {
        pmm = pmm * (-fact*somx2);
        fact = fact+2.0f;
      }
    }
    if (L==M) return multiplier*pmm;

    Float pmmp1=X*(2*M+1)*pmm;
    if (L==(M+1)) return multiplier*pmmp1;

    Float pll=0;
    for (int ll=M+2; ll<=L; ll++)
    {
      pll=(X*(2*ll-1)*pmmp1-(ll+M-1)*pmm)/(ll-M);
      pmm=pmmp1;
      pmmp1=pll;
    }
    return multiplier*pll;
  }
};

#endif
