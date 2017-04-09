// Copyright (C) 2016 The Regents of the University of California
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

#ifndef DFSHeader_H
#define DFSHeader_H

#include <string.h>
#include <vol3ddatatypes.h>
#include <endianswap.h>
#include <byteorder.h>

class DFSHeader {
public:
  char headerType[12];     // should be DFS_BE v2.0\0 on big-endian machines, DFS_BEv1.0\0 on little-endian
  uint32 hdrsize;          // Size of complete header (i.e., offset of first data element)
  uint32 mdoffset;         // Start of metadata.
  uint32 pdoffset;         // Start of patient data header.
  uint32 nTriangles;       // Number of triangles
  uint32 nVertices;        // Number of vertices
  uint32 nStrips;          // Number of triangle strips [ deprecated ]
  uint32 stripSize;        // size of strip data [ deprecated ]
  uint32 normals;          // 4	Int32	<normals>	Start of vertex normal data (0 if not in file)
  uint32 uvoffset;         // Start of surface parameterization data (0 if not in file)
  uint32 vcoffset;         // vertex color
  uint32 labelOffset;      // vertex labels
  uint32 vertexAttributes; // vertex attributes (float32 array of length NV)
  uint8 pad2[4 + 15*8];    // formerly 4x4 matrix, affine transformation to world coordinates, now used to add new fields
  DFSHeader()
  {
    if (ByteOrder::bigEndian())
    {
#ifdef _MSC_VER
      ::strncpy_s(headerType,sizeof(headerType),"DFS_BE v2.0\0",sizeof(headerType));
#else
      ::strncpy(headerType,"DFS_BE v2.0\0",sizeof(headerType));
#endif
    }
    else
    {
#ifdef _MSC_VER
      ::strncpy_s(headerType,sizeof(headerType),"DFS_LE v2.0\0",sizeof(headerType));
#else
      ::strncpy(headerType,"DFS_LE v2.0\0",sizeof(headerType));
#endif
    }
    hdrsize = sizeof(DFSHeader);
    mdoffset = 0;
    pdoffset = 0;
    for (size_t i=0;i<sizeof(pad2);i++) pad2[i] = 0;
    nTriangles=0;            // Number of triangles
    nVertices=0;             // Number of vertices
    nStrips=0;               // Number of triangle strips
    stripSize=0;             // size of strip data
    normals=0;               // Int32	<normals>	Start of vertex normal data (0 if not in file)
    uvoffset=0;              // Start of surface parameterization data (0 if not in file)
    vcoffset=0;              // vertex color
    vertexAttributes = 0;
    labelOffset=0;           // label offset
  }
  void swapHeader()
  {
    SILT::endian_swap(hdrsize);
    SILT::endian_swap(mdoffset);
    SILT::endian_swap(pdoffset);
    SILT::endian_swap(nTriangles);
    SILT::endian_swap(nVertices);
    SILT::endian_swap(nStrips);
    SILT::endian_swap(stripSize);
    SILT::endian_swap(normals);
    SILT::endian_swap(uvoffset);
    SILT::endian_swap(vcoffset);
    SILT::endian_swap(labelOffset);
    SILT::endian_swap(vertexAttributes);
  }
};

#endif
