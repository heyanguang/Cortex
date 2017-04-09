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

#ifndef SILT_ZStream_H
#define SILT_ZStream_H

#include <sstream>

#ifdef WIN32
#ifndef ZLIB_WINAPI
#define ZLIB_WINAPI
#endif
#endif

#include <zlib.h>

namespace SILT {
//! \brief A simple input stream class for interfacing with gzipped files.
//! \details This class is limited compared to other stream classes and only implements basic read and seek functions.
//! \author david w. shattuck
//! \date 30 April 2010
class izstream {
public:
  izstream() : fp(0) {}
  izstream(std::string ifname) : fp(0) { open(ifname); }
  ~izstream() { close(); }
  z_off_t seekg(z_off_t offset, int whence=SEEK_SET) { return  gzseek (fp, offset, whence); }
  bool open(const char *ifname)
  {
    if (fp) close();
    fp = ::gzopen(ifname, "rb");
    return (fp!=0);
  }
  bool open(const std::string ifname)
  {
    return open(ifname.c_str());
  }
  bool operator!() { return (fp==0); }
  bool close()
  {
    int id = gzclose(fp);
    fp=0;
    return (id!=0);
  }
  int read(void* buf, size_t len)
  {
    return ::gzread(fp, buf, (unsigned int) len);
  }
private:
  gzFile fp;
};

//! \brief A simple output stream class for interfacing with gzipped files.
//! \details This class is limited compared to other stream classes and only implements basic write functionality.
//! \author david w. shattuck
//! \date 30 April 2010
class ozstream {
public:
  ozstream() : fp(0) {}
  ozstream(std::string ofname, int level = Z_DEFAULT_COMPRESSION) : fp(0) { open(ofname,level); }
  ~ozstream() { close(); }
  bool open(const char *ofname, int level = Z_DEFAULT_COMPRESSION)
  {
    if (fp) close();
    std::ostringstream mode;
    mode<<"wb";
    if (level>=0) mode<<level;
    fp = ::gzopen(ofname, mode.str().c_str());
    return (fp!=0);
  }
  bool open(const std::string ifname, int level = Z_DEFAULT_COMPRESSION)
  {
    return open(ifname.c_str(), level);
  }
  bool close()
  {
    int id = gzclose(fp);
    fp=0;
    return (id!=0);
  }
  bool operator!() { return (fp==0); }
  int write(void* buf, size_t len)
  {
    return ::gzwrite(fp, buf, (unsigned int) len);
  }
private:
  gzFile fp;
};

} // end of namespace SILT

#endif
