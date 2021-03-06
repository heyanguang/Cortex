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

#ifndef LabelDetails_H
#define LabelDetails_H
#include <string>
#include <vol3ddatatypes.h>

class LabelDetails {
public:
  LabelDetails(std::string str1, std::string str2, uint32 color) : descriptor(str1), tag(str2), color(color), set(true) {}
    LabelDetails() : descriptor(""), tag(""), color(0x0), set(false) {}
    std::string descriptor;
    std::string tag;
    uint32 color;
    bool set;
};

#endif
