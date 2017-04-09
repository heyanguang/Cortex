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

#ifndef SILT_Surface_H
#define SILT_Surface_H

#include <dspoint.h>
#include <dfsheader.h>
#include <fstream>
#include <connectionlist.h>
#include <strutil.h>
#include <xmlbuffer.h>
#include <uvpoint.h>
#include <include/triangle.h>
#include <DS/connection.h>
#include <endianswap.h>

namespace SILT {

class ByteSwap {
public:
  static void byteSwap(Triangle &t)
  {
    SILT::endian_swap(t.a);
    SILT::endian_swap(t.b);
    SILT::endian_swap(t.c);
  }
  static void byteSwap(DSPoint &p)
  {
    SILT::endian_swap(p.x);
    SILT::endian_swap(p.y);
    SILT::endian_swap(p.z);
  }
  static void byteSwap(UVPoint &p)
  {
    SILT::endian_swap(p.u);
    SILT::endian_swap(p.v);
  }
  static void byteSwap(float &f)
  {
    SILT::endian_swap(f);
  }
};

class Surface {
public:
  typedef ConnectionList VertexConnection;
  Surface() {}
  size_t nt() const { return triangles.size(); }
  size_t nv() const { return vertices.size(); }
  void computeConnectivity();
  template <class VectorType>void byteswap(VectorType &v)
  {
    for (size_t i=0;i<v.size();i++) // replace with iterator to generalize
      ByteSwap::byteSwap(v[i]);
  }
  bool readOBJ(std::string s);
  bool readOBJbin(std::string s);
  bool readDFS(std::string s);
  bool read(std::string s);
  void computeCenter();
  void computeNormals();
  template <class T> bool outputDFS(T &outputStream);
  template <class T> bool outputDSGL(T &outputStream);
  bool write(std::string s);
  bool writeOBJ(std::string s);
  bool writeOFF(std::string s);
  bool writeWFO(std::string s); // wavefront object
  bool writeDFS(std::string s);
  bool writeSTL(std::string s);
  std::string filename;
  std::vector<Triangle> triangles;
  std::vector<DSPoint> vertices;
  std::vector<DSPoint> vertexNormals;
  std::vector<DSPoint> vertexColor;
  std::vector<UVPoint> vertexUV;
  std::vector<uint16> vertexLabels;
  std::vector<VertexConnection> connectivity;
  std::vector<float> meanCurvature;
  std::vector<float> vertexAttributes;
  DSPoint center;
};

} // end of SILT namespace

#endif

