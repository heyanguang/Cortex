// Copyright (C) 2016 The Regents of the University of California and
// the University of Southern California
//
// Created by David W. Shattuck, Ph.D.
//
// This file is part of Vol3D.
//
// Vol3D is free software; you can redistribute it and/or
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

#include <marchingcubes.h>
#include <subvol.h>
#include <DS/timer.h>
#include <autocrop.h>
#include <collector.h>

template <class T, class Op>
bool MarchingCubes::cubes(Vol3D<T> &volIn, SILT::Surface &tess, const Op op)
{
  int vertexCount[256];
  SubVol3D<T> sv;
  autocrop(sv,volIn,4);
  DSPoint imageShift((float)sv.lower.x,(float)sv.lower.y,(float)sv.lower.z);
  Vol3D<T> &vol(sv.vol);

  const int yDim=vol.cy;
  const int zDim=vol.cz;
  int maxVertexSize = 8000000;
  int totalTriangles = 0;
  {
    const int cx = vol.cx;
    const int cy = vol.cy;
    const int cz = vol.cz;
    const int slice = vol.cx * yDim;

    for (int i=0;i<256;i++)
    {
      vertexCount[i] = 0;
      for (int j=0;j<16;j++)
        if (triangleTable[i][j]>=0) vertexCount[i]++;
    }
    int count=0;
    T *data = vol.start();
    for (int z=0;z<cz-1;z++)
      for (int y=0;y<cy-1;y++)
      {
        T *line = vol.start() + vol.index(0,y,z);
        for (int x=0;x<cx-1;x++)
        {
          int index = vol.index(x,y,z);
          unsigned char map 					=
            op(data[index             ])
            |op(data[index+1           ])<<1
            |op(data[index+vol.cx+1      ])<<2
            |op(data[index+vol.cx        ])<<3
            |op(data[index+slice       ])<<4
            |op(data[index+slice+1     ])<<5
            |op(data[index+slice+vol.cx+1])<<6
            |op(data[index+slice+vol.cx  ])<<7;
          count += vertexCount[map];
          line++;
        }
      }
    totalTriangles = count/3;
    maxVertexSize = count;
  }
  vertexStack.resize(maxVertexSize);
  tess.triangles.clear();
  tess.triangles.reserve(totalTriangles);

  const int slice = vol.cx * yDim;
  const int slice2 = slice * 4;
  const int xDim2 = vol.cx * 2;
  const int yDim2 = yDim * 2;
  const int datasize7 = slice2 * 7;
  int index = 0;
  int nvert=0;
  int *vmx  = new int[datasize7];
  int *vma  = vmx + slice2 * 4;
  int vindex = 0;
  for (int v=0;v<datasize7;v++) vmx [v] = 0;
  int ta=0,tb=0,tc=0;
  T *data = vol.start();
  const int xStop = vol.cx - 1;
  Collector<DSPoint> vertCollector;

  for (int i=0;i<	zDim-1;i++)
  {
    for (int j=0;j<	yDim-1;j++)
    {
      index = i*slice + j * vol.cx;
      for (int k=0;k<	xStop; k++)
      {
        uint8 map =
           op(data[index             ])
          |op(data[index+1           ])<<1
          |op(data[index+vol.cx+1      ])<<2
          |op(data[index+vol.cx        ])<<3
          |op(data[index+slice       ])<<4
          |op(data[index+slice+1     ])<<5
          |op(data[index+slice+vol.cx+1])<<6
          |op(data[index+slice+vol.cx  ])<<7;
        const int *tri = triangleTable[map];
        if (tri[0]>=0)
        {
          for (int q=0;q<15;q++)
          {
            int nt = tri[q];
            if (nt>=0)
            {
              int x = 2*k+vertexTable[nt][0];
              int y = 2*j+vertexTable[nt][1];
              int z = vertexTable[nt][2];
              int idx = z*slice2 + y*xDim2 + x;
              vma[idx] = 255;
              vertexStack[nvert++]=DSPoint((float)x,(float)y,(float)(z+2*i));
              if (nvert>maxVertexSize)
              {
                std::cerr<<"Out of vertex stack.  Scene geometry is too complex"<<'\t'<<nvert<<'\t'<<maxVertexSize<<std::endl;
                std::cerr<<"z = "<<i<<std::endl;
                return false;
              }
            }
          }
        }
        index++;
      }
    }
    if (i>0)
    {
      int d  = ((i-1)*2)*slice2;
      int d2 = 2*slice2;
      for (int a=0;a<2;a++)
      {
        for (int j=0;j<	yDim2;j++)
        {

          for (int k=0;k<	xDim2;k++,d++,d2++)
          {
            if (vmx[d2])
            {
              if (vertCollector.add(DSPoint(k/2.0f,j/2.0f,((i-1)*2+a)/2.0f))==false)
              {
                std::cerr<<"Out of stack. "<<'\t'<<vertCollector.n()<<std::endl;
                return false;
              }
              vmx[d2] = vindex++;
            }
          }
        }
      }
      const int tstop = tb - 2;
      for (int r=ta;r<tstop;)
      {
        DSPoint v = vertexStack[r++];
        int a = int(v.y*xDim2 + v.x + (v.z - (i-2)*2)*slice2);
        v = vertexStack[r++];
        int b = int(v.y*xDim2 + v.x + (v.z - (i-2)*2)*slice2);
        v = vertexStack[r++];
        int c = int(v.y*xDim2 + v.x + (v.z - (i-2)*2)*slice2);
        tess.triangles.push_back(Triangle(vmx[a],vmx[b],vmx[c]));
      }
    }
    ta = tb;
    tb = tc;
    tc = nvert;
    for (int v=0;v<slice2*5;v++)
      vmx[v] = vmx[v+slice2*2];
    for (int v=slice2;v<slice2*3;v++)
      vma[v] = 0;
  }
  for (int r=ta;r<tb;)
  {
    int i = zDim - 1;
    DSPoint v = vertexStack[r++];
    int a = int(v.y*xDim2 + v.x + (v.z - (i-2)*2)*slice2);
    v = vertexStack[r++];
    int b = int(v.y*xDim2 + v.x + (v.z - (i-2)*2)*slice2);
    v = vertexStack[r++];
    int c = int(v.y*xDim2 + v.x + (v.z - (i-2)*2)*slice2);
    tess.triangles.push_back(Triangle(vmx[a],vmx[b],vmx[c]));
  }
  tess.vertices.resize(vertCollector.n());
  vertCollector.xport(&tess.vertices[0]);
  {
    const size_t nv = tess.nv();
    for (size_t i=0;i<nv;i++)
      tess.vertices[i] += imageShift;
  }
  rescale(tess,vol.rx,vol.ry,vol.rz);
  return true;
}
