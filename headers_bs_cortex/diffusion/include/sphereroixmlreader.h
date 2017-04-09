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

#ifndef SphereROIXMLReader_H
#define SphereROIXMLReader_H

#include <vector>
#include <rapidxml.hpp>
#include <sphereroi.h>
#include <DS/getfilesize.h>
#include <DS/timer.h>

class SphereROIXMLReader {
public:
  static bool readFlag(bool &flag, rapidxml::xml_node<>* node, std::string elementName)
  {
    rapidxml::xml_attribute<char> *attr = node->first_attribute(elementName.c_str());
    if (attr)
    {
      int value=0;
      std::string s=attr->value();
      std::istringstream istr(s);
      istr>>value;
      flag=(value!=0);
      return true;
    }
    else
      return false;
  }
  template <class T>
  static bool readValue(T &element, rapidxml::xml_node<>* node, std::string elementName)
  {
    rapidxml::xml_attribute<char> *attr = node->first_attribute(elementName.c_str());
    if (attr)
    {
      std::string s=attr->value();
      std::istringstream istr(s);
      istr>>element;
      return true;
    }
    else
      return false;
  }
  static bool readROIXML(std::vector<SphereROI> &spheres, std::string ifname)
  {
    int fs = getFileSize(ifname);
    if (fs<=0)
    {
      std::cerr<<"unable to open "<<ifname<<std::endl;
      return false;
    }
    std::ifstream ifile(ifname.c_str(),std::ios::binary);
    if (!ifile)
    {
      std::cerr<<"unable to open "<<ifname<<std::endl;
      return false;
    }
    std::vector<char> buffer(fs+1);
    ifile.read(&buffer[0],fs);
    buffer[fs] = 0;
    Timer parseTimer;
    parseTimer.start();
    try
    {
      rapidxml::xml_document<> doc;    // character type defaults to char
      doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&buffer[0]);    // 0 means default parse flags
      rapidxml::xml_node<>* cur_node = doc.first_node("BrainSuiteROIs");
      if (cur_node)
      {
        rapidxml::xml_node<>*child = cur_node->first_node("ROI");
        while (child != 0)
        {
          SphereROI sphere;
          rapidxml::xml_attribute<char> *position = child->first_attribute("voxelposition");
          if (position)
          {
            std::istringstream istr(position->value());
            istr>>sphere.voxelPosition;
          }
          readValue(sphere.color,child,"color");
          readValue(sphere.radius,child,"radius_mm");
          readFlag(sphere.active,child,"active");
          readFlag(sphere.include,child,"include");
          readFlag(sphere.andop,child,"and");
          spheres.push_back(sphere);
          child = child->next_sibling("ROI");
        }
      }
      else
      {
      }
    }
    catch(rapidxml::parse_error &error)
    {
      std::cerr<<"RapidXML exception when parsing "<<ifname<<" : "<<error.what()<<std::endl;
      return false;
    }
    return true;
  }
};

#endif
