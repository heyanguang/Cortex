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

#ifndef STRUTIL_H
#define STRUTIL_H

#include <string>
#include <sstream>
#include <cstring>

namespace StrUtil {
inline bool eqnocase(const std::string s, const std::string s2)
{
  std::string::const_iterator p=s.begin();
  std::string::const_iterator p2=s2.begin();
  while (p!=s.end() && p2!=s2.end())
  {
    if (toupper(*p++)!=toupper(*p2++)) return false;
  }
  return (s2.size()==s.size());
}

inline bool hasEnding(std::string str, std::string suffix)
{
  std::string::reverse_iterator iStr = str.rbegin();
  std::string::reverse_iterator iSuffix = suffix.rbegin();
  while (iSuffix != suffix.rend())
  {
    if (iStr==str.rend()) return false;
    if (toupper(*iStr++)!=toupper(*iSuffix++)) return false;
  }
  return true;
}

inline std::string extStrip(std::string s)
{
  size_t n = s.rfind('.');
  if (n!=s.npos)
  {
    s = s.substr(0,n);
  }
  return s;
}

inline std::string extStrip(std::string s, const std::string key)
{
  size_t n = s.rfind('.');
  if (n!=s.npos)
  {
    if (eqnocase(s.substr(n+1),key)) s = s.substr(0,n);
  }
  return s;
}

inline std::string gzStrip(std::string s)
{
  size_t n = s.rfind('.');
  if (n!=s.npos)
  {
    if (eqnocase(s.substr(n+1),"gz")) s = s.substr(0,n);
  }
  return s;
}

inline std::string gzAppend(std::string s)
{
  size_t n = s.rfind('.');
  if (n!=s.npos)
  {
    if (!eqnocase(s.substr(n+1),"gz")) return s+".gz";
  }
  return s;
}

inline std::string extAppend(std::string s, std::string ext)
{
  size_t n = s.rfind('.');
  if (n!=s.npos)
  {
    if (!eqnocase(s.substr(n+1),ext)) return s+ext;
  }
  return s;
}


inline std::string getExt(const std::string ifname)
{
  size_t n=ifname.rfind('.');
  return (n!=ifname.npos) ? ifname.substr(n+1) : "";
}

inline bool isGZ(std::string ifname)
{
  const char *r=strrchr(ifname.c_str(),'.'); // TODO:use rfind instead
  if (r)
  {
    if (eqnocase(r,".gz")) return true;
  }
  return false;
}

inline bool hasExtension(const std::string ifname, const std::string extension)
{
  const char *r=strrchr(ifname.c_str(),'.'); // TODO:use rfind instead
  if (r)
  {
    if (eqnocase(r,extension)) return true;
  }
  return false;
}

inline bool endsWith(const std::string str, const std::string suffix)
{
  if (str.length() >= suffix.length())
  {
    return (0 == str.compare(str.length()-suffix.length(),suffix.length(),suffix));
  }
  return false;
}

inline std::string ftos(const float f)
{
  std::ostringstream ostr;
  ostr<<f;
  return ostr.str();
}

inline std::string itos(const int f)
{
  std::ostringstream ostr;
  ostr<<f;
  return ostr.str();
}

inline void trailingSlash(std::string &s)
{
  if (s.length()==0) return;
  char end = s[s.length()-1];
  if (end == '/') return;
  if (end == '\\') return;
  s += "/";
}

inline std::string getBasename(std::string filename)
{
  std::string basename=extStrip(filename,"gz");
  if (hasExtension(basename,".hdr")) basename=extStrip(basename,"hdr");
  else if (hasExtension(basename,".img")) basename=extStrip(basename,"img");
  else if (hasExtension(basename,".nii")) basename=extStrip(basename,"nii");
  return basename;
}

inline std::string getFilename(const std::string ifname)
{
  size_t n=ifname.rfind('.');
  std::string rfname=(n!=ifname.npos) ? ifname.substr(0,n) : ifname;
  auto p=rfname.find_last_of("/\\");
  if (p!=rfname.npos)
  {
    rfname=rfname.substr(p+1);
  }
  return rfname;
}

inline std::string shortName(const std::string s)
{
  static const std::string::size_type npos = -1;
  std::string::size_type i = s.rfind('/');
  if (i==npos) i = s.rfind('\\');
  if (i==npos) return s;
  return s.substr(++i);
}
} // end of namespace StrUtil

#endif
