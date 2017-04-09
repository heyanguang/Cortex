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

#ifndef ColorOps_H
#define ColorOps_H

#include <vol3ddatatypes.h>
#include <rgb8.h>
#include <eigensystem3x3.h>

inline uint8 clampFloat32(const float32 v) { return uint8((v<255) ? ((v>=0) ? v : 0) : 255); }
inline uint8 clampFloat32(const float64 v) { return uint8((v<255) ? ((v>=0) ? v : 0) : 255); }
inline uint8 clamp32(const uint32 v) { return (v<255) ? v : 255; }
inline uint8 clamp32s(const sint32 v) { return (v<255) ? ((v>=0) ? v : 0) : 255; }
inline uint8 clamp16(const uint16 v) { return (v<255) ? v : 255; }
inline uint8 clamp16s(const sint16 v) { return (v<255) ? ((v>=0) ? v : 0) : 255; }
inline uint8 clamp(const uint32 v) { return (v<255) ? v : 255; }
inline uint8 clamp(const uint16 v) { return (v<255) ? v : 255; }
inline uint8 clamp(const sint16 v) { return (v<255) ? ((v>=0) ? v : 0) : 255; }

inline uint32 rgb2word(const rgb8 v) { return ((uint32(v.r))<<16) | ((uint32(v.g))<<8) | ((uint32(v.b))<<0); }

class RawOp {
public:
  void operator()(uint32 &dst, const uint8  src) { dst = 0x10101*(uint8)src; }
  void operator()(uint32 &dst, const uint16 src) { dst = 0x10101*clamp(src); }
  void operator()(uint32 &dst, const uint32 src) { dst = 0x10101*clamp(src); }
  void operator()(uint32 &dst, const sint16 src) { dst = 0x10101*clamp(src); }
  void operator()(uint32 &dst, const rgb8   src) { dst = rgb2word(src); }
  void operator()(uint32 &dst, const float32 src){ dst = 0x10101*clampFloat32(src); }
  void operator()(uint32 &dst, const float64 src){ dst = 0x10101*clampFloat32(src); }
  void operator()(uint32 &dst, const EigenSystem3x3f src)
  {
    uint8 *b = (uint8 *)&dst;
    b[0] = abs(int(255*src.v0.z)); // B
    b[1] = abs(int(255*src.v0.y)); // G
    b[2] = abs(int(255*src.v0.x)); // R
  }
};

class RawOpAlpha {
public:
  void operator()(uint32 &dst, const uint8  src) { dst = 0x01010101*(uint8)src; }
  void operator()(uint32 &dst, const uint16 src) { dst = 0x01010101*clamp(src); }
  void operator()(uint32 &dst, const uint32 src) { dst = 0x01010101*clamp(src); }
  void operator()(uint32 &dst, const sint16 src) { dst = 0x01010101*clamp(src); }
  void operator()(uint32 &dst, const rgb8   src) { dst = rgb2word(src); }
  void operator()(uint32 &dst, const float32 src){ dst = 0x01010101*clampFloat32(src); }
  void operator()(uint32 &dst, const float64 src){ dst = 0x01010101*clampFloat32(src); }
  void operator()(uint32 &dst, const EigenSystem3x3f src)
  {
    uint8 *b = (uint8 *)&dst;
    b[0] = abs(int(255*src.v0.z)); // B
    b[1] = abs(int(255*src.v0.y)); // G
    b[2] = abs(int(255*src.v0.x)); // R
  }
};

class LUTOp {
public:
  const uint32 *lut;
  LUTOp(const uint32 *lut_, const float fbright) : lut(lut_), bright((fbright>1) ? (int)fbright : 1), brightF(fbright>0 ? fbright : 1) {}
  void operator()(uint32 &dst, const uint8  src) { dst = lut[clamp16(uint16(src*255)/bright)]; }
  void operator()(uint32 &dst, const uint16 src) { dst = lut[clamp32(uint32(src*255)/bright)]; }
  void operator()(uint32 &dst, const sint16 src) { dst = lut[clamp32s(sint32(src*255)/bright)]; }
  void operator()(uint32 &dst, const uint32 src) { dst = lut[clamp32(uint32(src*255)/bright)]; }
  void operator()(uint32 &dst, const float32 src) { dst =lut[clampFloat32(src*255.0f/brightF)]; }
  void operator()(uint32 &dst, const float64 src) { dst =lut[clampFloat32(src*255.0/brightF)]; }
  void operator()(uint32 &dst, const rgb8   src) {
    uint8 *b = (uint8 *)&dst;
    b[0] = clamp(uint16((255*src.b)/bright));
    b[1] = clamp(uint16((255*src.g)/bright));
    b[2] = clamp(uint16((255*src.r)/bright));
  }
  void operator()(uint32 &dst, const EigenSystem3x3f &src) {
    uint8 *b = (uint8 *)&dst;
    b[0] = clamp(uint16(abs(int(65025*src.v0.z))/bright));
    b[1] = clamp(uint16(abs(int(65025*src.v0.y))/bright));
    b[2] = clamp(uint16(abs(int(65025*src.v0.x))/bright)); // 65025 = 255 * 255
  }
  const int bright;
  const float brightF;
};

class ColorFAOp {
public:
  ColorFAOp(const float fbright) : bright((fbright>1) ? (int)fbright : 1), brightF(fbright>0 ? fbright : 1) {}
  inline float fractionalAnisotropy(const EigenSystem3x3f &e)
  {
    float d=(e.l0*e.l0+e.l1*e.l1+e.l2*e.l2);
    return (d>0) ? sqrtf(0.5f *
                         (square(e.l0-e.l1)+square(e.l1-e.l2)+square(e.l2-e.l0))
                         /d) : 0;
  }
  void operator()(uint32 &dst, const EigenSystem3x3f &src) {
    const float FA=fractionalAnisotropy(src) * 65025.0f/bright;
    uint8 *b = (uint8 *)&dst;
    b[0] = clamp(uint16(abs(int(FA*src.v0.z))));
    b[1] = clamp(uint16(abs(int(FA*src.v0.y))));
    b[2] = clamp(uint16(abs(int(FA*src.v0.x)))); // 65025 = 255 * 255
  }
  void operator()(uint32 &dst, const uint8  /*src*/) { dst =0 ; }
  void operator()(uint32 &dst, const uint16 /*src*/) { dst =0 ; }
  void operator()(uint32 &dst, const sint16 /*src*/) { dst =0 ; }
  void operator()(uint32 &dst, const uint32 /*src*/) { dst = 0; }
  void operator()(uint32 &dst, const float32 /*src*/) { dst =0 ; }
  void operator()(uint32 &dst, const float64 /*src*/) { dst =0 ; }
  void operator()(uint32 &dst, const rgb8   /*src*/)  { dst =0 ; }
  const int bright;
  const float brightF;
};

class RangeLUTOp{
public:
  const uint32 *lut;
  RangeLUTOp(const uint32 *lut_, const float fmin, const float fmax)
    : lut(lut_), minI((int)fmin), maxI((fmax>1) ? (int)fmax : 1), minF(fmin), maxF(fmax>0 ? fmax : 1),
      scaleF(255.0f/(maxF-minF)) {}
  template <class T>
  void operator()(uint32 &dst, const T src) const
  {
    dst =lut[clampFloat32((src-minF)*scaleF)];
  }
  void operator()(uint32 &dst, const rgb8   src)  const
  {
    uint8 *b = (uint8 *)&dst;
    b[0] = clampFloat32((src.b-minF)*scaleF);
    b[1] = clampFloat32((src.g-minF)*scaleF);
    b[2] = clampFloat32((src.r-minF)*scaleF);
  }
  void operator()(uint32 &dst, const EigenSystem3x3f &src)  const
  {
    uint8 *b = (uint8 *)&dst;
    b[0] = clamp(uint16(abs(int(65025*src.v0.z))/maxI));
    b[1] = clamp(uint16(abs(int(65025*src.v0.y))/maxI));
    b[2] = clamp(uint16(abs(int(65025*src.v0.x))/maxI)); // 65025 = 255 * 255
  }
  const int minI;
  const int maxI;
  const float minF;
  const float maxF;
  const float scaleF;
};

class LabelOp {
public:
  static uint32 colorTable[65536];
  void operator()(uint32 &dst, const uint8  src) { dst = colorTable[src]; }
  void operator()(uint32 &dst, const uint16 src) { dst = colorTable[src]; }
  void operator()(uint32 &dst, const sint16 src) { dst = colorTable[(uint16)src]; }
  void operator()(uint32 &dst, const uint32 src) { dst = colorTable[(uint16)src]; }
  void operator()(uint32 &dst, const rgb8   src) { dst = rgb2word(src); }
  void operator()(uint32 &dst, const float32 src) { dst = colorTable[(uint16)src]; }
  void operator()(uint32 &dst, const float64 src) { dst = colorTable[(uint16)src]; }
  void operator()(uint32 &/* dst */, const EigenSystem3x3f /* src */) { } // invalid datatype for labels
};

#endif
