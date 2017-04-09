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

#ifndef SVREGMANIFEST_H
#define SVREGMANIFEST_H

#include <brainsuitemanifest.h>
#include <vector>

class SVRegManifest : public BrainSuiteManifest
{
public:
  class Atlas {
  public:
    std::string name;
    std::string basename;
  };
  SVRegManifest();
  bool read(std::string ifname);
  std::string filepath;
  std::string versionstr;
  std::string buildstr;
  std::string date;
  std::string mcrversion;
  std::string platform;
  std::string minimumBrainSuiteVersion;
  std::vector<Atlas> atlases;
  std::string atlasName;
  float buildNumber;
  bool valid;
};

#endif // SVREGMANIFEST_H
