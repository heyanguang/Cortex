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

#ifndef ImageState_H
#define ImageState_H

#include <point3d.h>

class ImageScale {
public:
	ImageScale(const float n=255) : minv(0), maxv(n) {}
	ImageScale(const float minv, const float maxv) : minv(minv), maxv(maxv) {}
	float minv;
	float maxv;
};

class ImageState {
public:
	enum MaskMode { Off=0, Stencil=1, Blend=2, Outline=3, MaskOnly=4 };
	ImageState();
	IPoint3D currentPosition;
	ImageScale brightness;
	ImageScale overlay1Brightness;
	ImageScale overlay2Brightness;
	unsigned char overlayAlpha;
	unsigned char overlay2Alpha;
	unsigned char labelAlpha;
	int labelBrightness;
	int zoom;
	float zoomf;
	bool smoothImage;
	bool viewOverlay;
	bool viewOverlay2;
	bool viewMask;
	bool viewLabels;
	bool viewInfo;
	bool viewVolume;
	bool showCursor;
	bool labelAlphaMode;	
	bool showSlider;
	bool viewLabelOutline;
	bool viewFixedOverlay;
	bool viewCurves;
  bool threeChannel;
	MaskMode maskMode;
};

#endif
