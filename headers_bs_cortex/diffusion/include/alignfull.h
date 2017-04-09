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

#ifndef AlignFull_H
#define AlignFull_H

#include <eigensystem3x3.h>
#include <cmath>

class AlignFull {
public:
  static inline DSPoint align(const EigenSystem3x3f &targetEigensystem, const DSPoint &targetVec)
  {
    const float d0 = targetVec.dot(targetEigensystem.v0);
    const float d1 = targetVec.dot(targetEigensystem.v1);
    const float d2 = targetVec.dot(targetEigensystem.v2);
    const float m0 = fabsf(d0 * targetEigensystem.l0);
    const float m1 = fabsf(d1 * targetEigensystem.l1);
    const float m2 = fabsf(d2 * targetEigensystem.l2);

    if ((m0>=m1)&&(m0>=m2))
      return (d0>0) ? targetEigensystem.v0 : -targetEigensystem.v0;
    if (m1>=m2)
      return (d1>0) ? targetEigensystem.v1 : -targetEigensystem.v1;
    return (d2>0) ? targetEigensystem.v2 : -targetEigensystem.v2;
  }
};

#endif
