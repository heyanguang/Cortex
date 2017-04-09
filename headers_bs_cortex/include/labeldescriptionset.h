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

#ifndef LabelDescriptionSet_H
#define LabelDescriptionSet_H

#include <rapidxml.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <labeldetails.h>
#include <strutil.h>
#include <iostream>

class LabelDescriptionSet {
public:
  LabelDescriptionSet();
  bool read(std::string labelFilename);
  bool readLBL(std::string labelFilename);
  bool write(std::string labelFilename);
  bool writestream(std::ostream &ostr);
  void loadDefaults();
  std::vector<LabelDetails> labelDetails;
};

inline LabelDescriptionSet::LabelDescriptionSet() : labelDetails(65536)
{
}

inline bool LabelDescriptionSet::write(std::string labelFilename)
{
  std::ofstream ofile(labelFilename.c_str());
  if (!ofile) { return false; }
  ofile<<"<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n"
      <<"<labelset>\n";
  for (size_t i=0;i<labelDetails.size();i++)
  {
    if (labelDetails[i].descriptor.empty()&&labelDetails[i].tag.empty()) continue; //&&(labelDetails[i].color)==0) continue;
    ofile<<"<label id=\""<<(int)i<<"\""
        <<" tag=\""<<labelDetails[i].tag<<"\""
       <<" color=\"0x"<<std::hex<<labelDetails[i].color<<std::dec<<"\""
      <<" fullname=\""<<labelDetails[i].descriptor<<"\""
     <<"/>\n";
  }
  ofile<<"</labelset>"<<std::endl;
  return true;
}

inline bool LabelDescriptionSet::readLBL(std::string labelFilename)
{
  std::ifstream ifile(labelFilename.c_str());
  if (!ifile) return false;
  char buffer[512];
  const size_t maxID = labelDetails.size();
  for (;;)
  {
    if (ifile.eof()) break;
    unsigned int id;
    ifile>>id>>std::ws;
    if (/*(id<0)||*/(id>=maxID))
    {
      std::cerr<<"ID "<<id<<" is out of range... ignoring.\n";
      ifile.getline(buffer,512);
      if (ifile.gcount()==0) if (ifile.eof()) break;
    }
    else
    {
      char ch = ifile.peek();
      if (ch=='0')
      {
        ifile.get();
        char ch2 = ifile.peek();
        ifile.putback(ch);
        if (ch2=='x')
        {
          std::string str;
          //					ifile>>str;
          int hexcolor = 0;
          ifile>>std::hex>>hexcolor;
          //					sscanf(str.c_str(),"%x",&hex);
          labelDetails[id].color = hexcolor;
        }
      }
      ifile>>labelDetails[id].tag>>std::ws;
      ifile.getline(buffer,512);
      if (ifile.gcount()==0) if (ifile.eof()) break;
      labelDetails[id].descriptor = buffer;
    }
  }
  return true;
}

inline bool LabelDescriptionSet::read(std::string labelFilename)
{
  try
  {
    std::ifstream ifile(labelFilename.c_str());
    if (!ifile) return false;
    rapidxml::xml_document<> doc;
    std::vector<char> buffer((std::istreambuf_iterator<char>(ifile)), std::istreambuf_iterator<char>());
    buffer.push_back('\0');
    doc.parse<0>(&buffer[0]);
    rapidxml::xml_node<>* cur_node = doc.first_node("labelset");
    if (cur_node)
    {
      cur_node = cur_node->first_node("label");
      while (cur_node)
      {
        rapidxml::xml_attribute<char> *idNode = cur_node->first_attribute("id");
        rapidxml::xml_attribute<char> *nameNode = cur_node->first_attribute("fullname");
        rapidxml::xml_attribute<char> *tagNode = cur_node->first_attribute("tag");
        rapidxml::xml_attribute<char> *colorNode = cur_node->first_attribute("color");
        if (idNode)
        {
          int id=0;
          std::istringstream(idNode->value())>>id;
          if (id>=0)
          {

            if (nameNode) labelDetails[id].descriptor = nameNode->value();
            if (tagNode) labelDetails[id].tag = tagNode->value();
            if (colorNode)
            {
              std::istringstream istr(colorNode->value());
              uint32 colorcode=0;
              istr>>std::hex>>colorcode;
              labelDetails[id].color = colorcode & 0x00FFFFFF;
            }

          }
        }
        cur_node = cur_node->next_sibling("label");
      }
    }
  }
  catch(rapidxml::parse_error &e)
  {
    std::cerr<<"RapidXML exception when parsing "<<labelFilename<<" : "<<e.what()<<std::endl;
    return false;
  }
  return true;
}

#endif
