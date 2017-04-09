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

#ifndef ModSHC_H
#define ModSHC_H

#include <legendre.h>

template <class T>
class ModSHC {
public:
  class LMPair {
  public:
    const int L,M;
    LMPair(const int L, const int M) : L(L), M(M) {}
  };
  static LMPair findLM(const int j)
  {
    for (int L=0;L<=j;L+=2) // modify for new numbers
      for (int M=-L;M<=L;M++)
        if (j==((L*L+L+2)/2+M))
        {
          return LMPair(L,M);
        }
    std::cerr<<"unable to find L,M pair for J="<<j<<std::endl;
    return LMPair(-1,-1);
  }
  static float factorial(int M)
  {
    float a=1;
    for (int i=2;i<=M;i++)
    {
      a*=i;
    }
    return a;
  }
  static T eval(int j, T theta, T phi)
  {
    const LMPair LM=findLM(j);
    const int L = LM.L;
    const int M = LM.M;
    if (M<0)
    {
      const int N = -M;
      T legendre = Legendre<T>::eval(L,N,cos(theta));
      return std::sqrt(2 * (2*L+1)/float(4*M_PI) * factorial(L-N)/factorial(L+N)) * legendre * cos(N*phi);
    }
    else if (M>0)
    {
      T legendre = Legendre<T>::eval(L,M,cos(theta));
      int sign = (M & 1) ? -1 : 1;
      return sign * std::sqrt(2 * (2*L+1)/float(4*M_PI) * factorial(L-M)/factorial(L+M)) * legendre * std::sin(M*phi);
    }
    else
    {
      return std::sqrt((2*L+1)/float(4*M_PI)) * Legendre<T>::eval(L,0,std::cos(theta)) * std::cos(M*phi);
    }
  }
};

#endif
