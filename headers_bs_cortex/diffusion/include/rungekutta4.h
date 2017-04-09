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

#ifndef RungeKutta4_H
#define RungeKutta4_H

class RungeKutta4 {
public:
  template <class Interpolator>
  static DSPoint eval(const DSPoint &pos, const DSPoint &prev, const Vol3D<EigenSystem3x3f> &vEig, const float stepsize)
  {
    DSPoint k1=Interpolator::samplePoint(pos,prev,vEig);
    if (k1.x==0&&k1.y==0&&k1.z==0) return DSPoint();
    DSPoint k2=Interpolator::samplePoint(pos+0.5f*stepsize*k1,prev,vEig);
    DSPoint k3=Interpolator::samplePoint(pos+0.5f*stepsize*k2,prev,vEig);
    DSPoint k4=Interpolator::samplePoint(pos+     stepsize*k3,prev,vEig);
    return (k1+2*k2+2*k3+k4).unit();
  }
};

#endif
