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

#ifndef TrkHeader_H
#define TrkHeader_H

class TrkHeader {
// for spec see: http://www.trackvis.org/docs/?subsect=fileformat
public:
  char id_string[6];
  short int dim[3];
  float voxel_size[3];
  float origin[3];
  short n_scalars;
  char scalar_name[10][20];
  short n_properties;
  char property_name[10][20];
  float vox_to_ras[4][4];
  char reserved[444];
  char voxel_order[4];
  char pad2[4];
  float image_orientation_patient[6];
  char pad1[2];
  unsigned char invert_x;
  unsigned char invert_y;
  unsigned char invert_z;
  unsigned char swap_xy;
  unsigned char swap_yz;
  unsigned char swap_zx;
  int n_count;
  int version;
  int hdr_size;
};

#endif
