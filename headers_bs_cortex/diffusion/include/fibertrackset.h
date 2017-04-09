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

#ifndef FiberTrackSet_H
#define FiberTrackSet_H

#include <list>
#include <dspoint.h>
#include <uvpoint.h>
#include <algorithm>
#include <fstream>
#include <vector>
#include <mat3.h>

class FiberTrack {
public:
  FiberTrack() : seedIndex(-1) {}
  class Attributes {
  public:
    Attributes() : color(1,0,0), lineWidth(1), pointWidth(1) {}
    std::string name;
    DSPoint color;
    float lineWidth;
    float pointWidth;
  };
  Attributes attributes;
  std::vector<DSPoint> points;
  int seedIndex;
};

class TrkHeader;

class FiberTrackSet {
public:
  FiberTrackSet();
  DSPoint str2pt(std::string str);
  bool parseXMLFiberAttributes(std::list<FiberTrack::Attributes> &fiberAttributes, std::vector<char> &buffer);
  bool write(std::string ofname);
  bool writeDFT(std::string ofname);
  bool read(std::string ifname);
  bool readDFT(std::string ifname);
  bool readTRK(std::string ifname); // read Trackvis file
  void readNextTrack(std::ifstream &ifile, FiberTrackSet &set, const SILT::Mat3<float> &xform, const DSPoint &shift);
  DSPoint computeTrackOrientation(char code);
  SILT::Mat3<float> getTrackMatrix(TrkHeader &hdr);
  void sortFiberTracks();
  FiberTrack &current() { return curves.back(); }
  void addPoint(DSPoint &p)
  {
    if (curves.size()<=0) newCurve();
    curves.back().points.push_back(p);
  }
  void clearAll() { curves.clear(); }
  void newCurve(const size_t reserve=0);
  void addCurve(std::vector<DSPoint> &points, int seedIndex, DSPoint color);
  size_t nCurves() { return curves.size(); }
  std::vector<FiberTrack> curves;
};

#endif
