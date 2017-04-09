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

#ifndef GetFileSize_H
#define GetFileSize_H

#include <sys/stat.h>
#ifndef _WIN32
#include <unistd.h>
#define STATFUNC	stat
#define STATSTRUC stat
#else
#define STATFUNC	_stati64
#define STATSTRUC _stati64
#endif
#include <string>
#include <fstream>

inline size_t getFileSize(const char *s)
{
  struct STATSTRUC buf;
  if (STATFUNC(s,&buf)!=-1)
    return buf.st_size;
  else
    return 0;
}

inline size_t getFileSize(const std::string s)
{
  return getFileSize(s.c_str());
}

inline bool fileExists(std::string str)
{
  struct STATSTRUC buf;
  int result = STATFUNC(str.c_str(),&buf);
  if (result==-1) return false;
  return true;
}

inline bool isFile(const char *v)
{
  struct STATSTRUC buf;
  int result = STATFUNC(v,&buf);
  if (result==-1) return false;
  return ((buf.st_mode&S_IFREG)!=0);
}

inline bool isFile(std::string ifname)
{
  struct STATSTRUC buf;
  int result = STATFUNC(ifname.c_str(),&buf);
  if (result==-1) return false;
  return ((buf.st_mode&S_IFREG)!=0);
}

inline bool isDir(std::string s)
{
  struct STATSTRUC buf;
  int result = STATFUNC(s.c_str(),&buf);
  if (result==-1) return false;
  return ((buf.st_mode&S_IFDIR)!=0);
}

inline unsigned int getGZfilesize(std::string s)
{
  std::ifstream ifile(s.c_str(),std::ios::binary);
  unsigned char buf[4];
  ifile.seekg( -4,std::ios::end);
  ifile.read((char*)buf,4);
  return
      ((buf[1]<<8) + buf[0])
      +(((buf[3]<<8) + buf[2])<<16);
}

#endif
