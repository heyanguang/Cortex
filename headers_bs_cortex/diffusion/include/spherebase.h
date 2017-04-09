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

#ifndef SphereBase_H
#define SphereBase_H

#include <surflib.h>
#include <cmath>

class SphereBase {
public:
  typedef float Precision;
  std::vector<Triangle> triangles;
  std::vector<DSPoint> vertices;
  std::vector<DSPoint> colors;
  std::vector<Precision> theta;
  std::vector<Precision> phi;
  DSPoint sph2cart(const float theta, const float phi, const float R)
  {
    const float temp=R*sin(theta);
    return DSPoint(temp*cos(phi),temp*sin(phi),R*cos(theta));
  }
  void setPoint(size_t n, Precision t, Precision p, Precision r=1)
  {
    theta[n] = t;
    phi[n] = p;
    vertices[n] = sph2cart((float)t,(float)p,(float)r);
  }
  SphereBase(const int nTheta=10, const int nPhi=10)
  {
    create(nTheta,nPhi);
  }
  void create(const int nTheta_=10, const int nPhi_=10)
  {
    nTheta=nTheta_;
    nPhi=nPhi_;
    const int NX = nTheta;
    const int NY = nPhi;
    vertices.resize((NX-2)*NY+2);
    triangles.resize((NX-2)*NY*2);
    theta.resize(vertices.size());
    phi.resize(vertices.size());
    int tcount = 0;
    size_t vcount = 0;
    setPoint(vcount++,0,0);
    const float M_PIf = (float)M_PI;
    for (int j=1;j<NX-1;j++)
      for (int i=0;i<NY;i++)
      {
        Precision theta = j*M_PIf/(NX-1);
        Precision  phi = (2*M_PIf * i)/NY;
        setPoint(vcount++,theta,phi);
      }
    setPoint(vcount++,M_PIf,0);
    if (vertices.size() != vcount)
      std::cerr<<"VC:\t"<<vertices.size()<<'\t'<<vcount<<std::endl;
    for (int i=0;i<NY-1;i++)
    {
      triangles[tcount++] = Triangle(0,i+2,i+1);
    }
    triangles[tcount++] = Triangle(0,1,NY);
    for (int j=1;j<NX-2;j++)
    {
      for (int i=0;i<NY-1;i++)
      {
        int a = 1+(j-1)*NY + i;
        int b = 1+(j-1)*NY + i + 1;
        int c = 1+(j  )*NY + i;
        int d = 1+(j  )*NY + i + 1;
        triangles[tcount++] = Triangle(a,b,c);
        triangles[tcount++] = Triangle(b,d,c);
      }
      int i = NY-1;
      int a = 1+(j-1)*NY + i;
      int b = 1+(j-1)*NY;
      int c = 1+(j  )*NY + i;
      int d = 1+(j  )*NY;
      triangles[tcount++] = Triangle(a,b,c);
      triangles[tcount++] = Triangle(b,d,c);
    }
    {
      int j = NX-2;
      for (int i=0;i<NY-1;i++)
      {
        int a = 1+(j-1)*NY + i;
        int b = 1+(j-1)*NY + i + 1;
        triangles[tcount++] = Triangle(a,b,(int)vcount-1);
      }
      int i = NY-1;
      int a = 1+(j-1)*NY + i;
      int b = 1+(j-1)*NY;
      triangles[tcount++] = Triangle(a,b,(int)vcount-1);
    }
    const size_t nv=vertices.size();
    colors.resize(nv);
    for (size_t i=0;i<nv;i++) colors[i] = abs(vertices[i]);
  }
  int nPhi;
  int nTheta;
};

#endif
