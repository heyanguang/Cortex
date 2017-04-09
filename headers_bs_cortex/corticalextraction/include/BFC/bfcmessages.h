// Copyright (C) 2016 The Regents of the University of California and
// the University of Southern California
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

#ifndef BFCMessages_H
#define BFCMessages_H
#include <iostream>

namespace BFCMessages {
inline void dot() { std::cout<<'.';std::cout.flush(); }
inline void plus() { std::cout<<'+';std::cout.flush(); }
inline void minus() { std::cout<<'-';std::cout.flush(); }
inline void reset() { std::cout<<'\n'; }
inline void status(std::string s) { std::cout<<s<<std::endl; }
inline void describe(std::string s) { std::cout<<s<<std::endl; }
inline void setAction(std::string s) { std::cout<<s<<std::endl; }
}

#endif
