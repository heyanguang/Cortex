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

#ifndef Vol3D_T_H
#define Vol3D_T_H 

#include <cmath>
#include <vol3d.h>
#include <vol3dquery.h>
#include <zstream.h>
#include <endianswap.h>
#include <dsnifti.h>
#include <siltbyteswap.h>
#include <vol3dreorder.h>

template <class T>
size_t Vol3D<T>::readDataStream(SILT::izstream &ifile)
{
  size_t bytesReadTotal = 0;
  size_t bytesInImage=size()*sizeof(T);
  size_t chunkSize = 1024*1024*1024;
  size_t bytesRemaining=bytesInImage;
  char *dest=(char*)data;
  while (bytesRemaining>0)
  {
    size_t bytesToRead=chunkSize<bytesRemaining ? chunkSize : bytesRemaining;
    size_t bytesRead=ifile.read(dest,bytesToRead);
    dest += bytesRead;
    bytesReadTotal += bytesRead;
    bytesRemaining -= bytesRead;
    if (bytesRead != bytesToRead) { std::cerr<<"read incorrect number of bytes "<<std::endl; break; }
  }
  if (bytesReadTotal != size()*sizeof(T))
  {
    std::cerr<<"warning: expected to read "<<size()*sizeof(T)<<", read "<<bytesReadTotal<<" bytes."<<std::endl;
  }
  return bytesReadTotal;
}

template <class T>
bool Vol3D<T>::readNifti(std::string ifname, Vol3DBase::AutoRotateCode autoRotate)
{
  SILT::izstream ifile(ifname);
  if (!ifile) return false;
  nifti_1_header header;
  ifile.read((char *)&header,sizeof(header));
  bool swapped=false;
  if ((header.dim[0]<0) || (header.dim[0]>7))
  {
    swapped=true;
    Vol3DQuery::swapNIFTIHeader(header);
  }
  if (!setsize(header.dim[1],header.dim[2],header.dim[3]))
  {
    std::cerr<<"Unable to allocate memory for new image.\n"<<std::endl;
    return false;
  }
  ifile.seekg(header.vox_offset,std::ios::beg);
  readDataStream(ifile);
  if (swapped)
  {
    SILT::byteswap(data,size());
  }
  if (scanQForm(header))
  {
// read image dimensions/coordinates from q-form -- no need to read from s-form
  }
  else
  {
    if (scanSForm(header))
    {
    }
    else
      std::cerr<<"couldn't read coordinate system -- assuming analyze"<<std::endl;
  }
  if ((autoRotate==Vol3DBase::RotateToRAS)&&!Vol3DBase::noRotate)
  {
    if (Vol3DReorder::isCanonical(*this)==false)
    {
      Vol3DReorder::transformNIItoRAS(*this);
    }
  }
  return true;
}

template <class T>
bool Vol3D<T>::read(const Vol3DQuery &vq, Vol3DBase::AutoRotateCode autoRotate)
{
  filename = vq.filename;
  switch (vq.headerType)
  {
    case HeaderType::Analyze:
    {
      filename = vq.filename;
      SILT::izstream ifile(vq.filename.c_str());
      if (!ifile)
      {
        std::cerr<<"unable to read "<<vq.filename<<std::endl;
        return false;
      }
      if (!setsize(vq.cx,vq.cy,vq.cz))
      {
        std::cerr<<"Unable to allocate memory "<<std::endl;
        return false;
      }
      rx = vq.rx;
      ry = vq.ry;
      rz = vq.rz;
      ifile.read((char *)data, size()*sizeof(T));	// need to check read size
      if (vq.swapped) SILT::byteswap(data,size());
      if (rx<0) { Vol3DReorder::flipX(*this); rx=-rx; }
      if (ry<0) { Vol3DReorder::flipY(*this); ry=-ry; }
      if (rz<0) { Vol3DReorder::flipZ(*this); rz=-rz; }
      return true;
      break;
    }
    case HeaderType::NIFTI_TWO_FILE:
      {
        SILT::izstream headerFile(vq.headerFilename);
        nifti_1_header header;
        headerFile.read((char *)&header,sizeof(header));
        bool swapped=false;
        if ((header.dim[0]<0) || (header.dim[0]>7))
        {
          swapped=true;
          Vol3DQuery::swapNIFTIHeader(header);
        }
        if (!setsize(header.dim[1],header.dim[2],header.dim[3]))
        {
          std::cerr<<"Unable to allocate memory for new image.\n"<<std::endl;
          return false;
        }
        filename = vq.filename;
        SILT::izstream ifile(vq.filename);
        if (!setsize(vq.cx,vq.cy,vq.cz))
        {
          std::cerr<<"Unable to allocate memory "<<std::endl;
          return false;
        }
        rx = vq.rx;
        ry = vq.ry;
        rz = vq.rz;
        readDataStream(ifile);
        if (swapped)
        {
          SILT::byteswap(data,size());
        }
        if (scanQForm(header))
        {
      //read image dimensions/coordinates from q-form -- no need to read from s-form
        }
        else
        {
          if (scanSForm(header))
          {
          }
          else
            std::cerr<<"couldn't read coordinate system -- assuming analyze"<<std::endl;
        }
        if ((autoRotate==Vol3DBase::RotateToRAS)&&!Vol3DBase::noRotate)
        {
          if (Vol3DReorder::isCanonical(*this)==false)
          {
            Vol3DReorder::transformNIItoRAS(*this);
          }
        }
      }
      break;
    case HeaderType::NIFTI:
      return readNifti(filename,autoRotate);
      break;
    default:
      std::cerr<<"Unknown format for "<<filename<<std::endl;
      return false;
      break;
  }
  return true;
}

template <class T>
bool Vol3D<T>::read(std::string ifname, Vol3DBase::AutoRotateCode autoRotate)
{
  filename = ifname;
  Vol3DQuery vq;
  if (!vq.query(ifname))
  {
    return false;
  }
  return read(vq,autoRotate);
}

template <class T>
bool Vol3D<T>::write(std::string ofname)
{

  bool compress = StrUtil::isGZ(ofname);
  bool isNIFTI = StrUtil::hasExtension(StrUtil::gzStrip(ofname),".nii");
  if (isNIFTI)
  {
    DSNifti hdr;
    setHeader(hdr);
    if (compress)
    {
      SILT::ozstream ofile(ofname.c_str());
      if (!ofile) return false;
      ofile.write((char *)&hdr, sizeof(hdr));
      char buf[4]={0,0,0,0};
      ofile.write(buf,4);
      {
        size_t bytesWrittenTotal=0;
        size_t bytesInImage=cx*cy*cz*sizeof(T);
        size_t chunkSize = 1024*1024*1024;
        size_t bytesRemaining=bytesInImage;
        char *src=(char*)data;
        while (bytesRemaining>0)
        {
          size_t bytesToWrite=chunkSize<bytesRemaining ? chunkSize : bytesRemaining;
          size_t bytesWritten=ofile.write(src, bytesToWrite);// need to check read size. if it's <0, there's an error
          src += bytesWritten;
          bytesWrittenTotal += bytesWritten;
          bytesRemaining -= bytesWritten;
          if (bytesWritten != bytesToWrite) { std::cerr<<"wrote incorrect number of bytes "<<std::endl; break; }
        }
      }
    }
    else
    {
      std::ofstream ofile(ofname.c_str(),std::ios::binary);
      if (!ofile) return false;
      ofile.write((char *)&hdr, sizeof(hdr));
      char buf[4]={0,0,0,0};
      ofile.write(buf,4);
      ofile.write((char *)data, cx*cy*cz*sizeof(T));
    }
  }
  else
  {
    std::string headerFilename;
    if (StrUtil::hasExtension(ofname,".hdr"))
    {
      headerFilename=ofname;
      std::string::reverse_iterator r = ofname.rbegin();
      *r++='g';
      *r++='m';
      *r++='i';
    }
    else
    {
      if (!(StrUtil::hasExtension(ofname,".img")||StrUtil::hasEnding(ofname,".img.gz"))) ofname += ".img";
      headerFilename = StrUtil::extStrip(StrUtil::gzStrip(ofname),"img") + ".hdr";
    }
#if 1
    DSNifti niftiHeader;
    setHeader(niftiHeader);
    niftiHeader.magic[0]='n';
    niftiHeader.magic[1]='i';
    niftiHeader.magic[2]='i';
    niftiHeader.magic[3]='\0';
#else
    AnalyzeHeader hdr;
    hdr.dims = 4;
    hdr.glmin = 0;
    hdr.glmax = maxVal();
    hdr.datatype = analyzeTypeID();
    size_t n = description.size();
    if (n<79)
    {
      std::copy(description.begin(),description.end(),hdr.descrip);
      hdr.descrip[description.length()] = 0;
    }
    else
    {
      for (int i=0;i<79;i++) hdr.descrip[i] = description.at(i);
      hdr.descrip[79]=0;
    }
    hdr.x_dim = cx;
    hdr.y_dim = cy;
    hdr.z_dim = cz;
    hdr.t_dim = 1;
    hdr.x_size = rx;
    hdr.y_size = ry;
    hdr.z_size = rz;
    hdr.bits = databits();
    hdr.glmin = minVal();
    hdr.glmax = maxVal();
#endif

    if (compress)
    {
      SILT::ozstream ofile(ofname.c_str());
      if (!ofile) return false;
      ofile.write((char *)data, cx*cy*cz*sizeof(T));
    }
    else
    {
      std::ofstream ofile(ofname.c_str(),std::ios::binary);
      if (!ofile) return false;
      ofile.write((char *)data, cx*cy*cz*sizeof(T));
    }
//    writeHeader(StrUtil::gzStrip(ofname).c_str(),hdr);
    std::ofstream hfile(headerFilename.c_str(),std::ios::binary);
    if (!hfile) return false;
    hfile.write((char *)&niftiHeader,sizeof(DSNifti));
//    hfile.write((char *)&header,sizeof(AnalyzeHeader));
  }
  return true;
}

template <class T>
bool Vol3D<T>::maskWith(const Vol3D<uint8> &vMask)
{
  if (isCompatible(vMask)==false) return false;
  const int ds = size();
  T *dst = start();
  uint8 *m = vMask.start();
  for (int i=0;i<ds;i++) if (!m[i]) dst[i] = 0;
  return true;
}

#define Vol3DInstance(T)\
  template bool Vol3D<T>::read(std::string, Vol3DBase::AutoRotateCode);\
  template bool Vol3D<T>::read(const Vol3DQuery &, Vol3DBase::AutoRotateCode);\
  template bool Vol3D<T>::write(std::string);\
  template bool Vol3D<T>::copyCast(Vol3DBase *&) const; \
  template bool Vol3D<T>::maskWith(const Vol3D<uint8> &);\
  template bool Vol3D<T>::readNifti(std::string, Vol3DBase::AutoRotateCode);

template <class T>
bool Vol3D<T>::copyCast(Vol3DBase *&dest) const
{
  if (!dest||this->typeID()!=dest->typeID())
  {
    Vol3D<T> *newVol = new Vol3D<T>;
    if (!newVol) return false;
    newVol->copy(*this);
    delete dest;
    dest = newVol;
  }
  else
  {
    static_cast<Vol3D<T> *>(dest)->copy(*this);
  }
  return true;
}

#endif
