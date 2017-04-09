// Copyright (C) 2016 The Regents of the University of California and
// the University of Southern California
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

#ifndef SliceSegmentor_H
#define SliceSegmentor_H
#include <DS/runlength.h>
#include <vol3ddatatypes.h>

class SliceRegionInfo {
public:
    SliceRegionInfo() : count(0), idx(-1) {}
    int	count;
    int idx;
};

class SliceSegmenter {
public:
    typedef sint16 LabelType;
    SliceSegmenter(int x, int y);
    ~SliceSegmenter();
    void population();
		void segmentBG(uint8 *imageIn, LabelType *imageOut)
    {
        // assumes zero is region to be segmented
			  segment(imageIn, imageOut, 255, 0);
    }
		void segment(uint8 *imageIn, LabelType *imageOut, uint8 zero, uint8 one);
    int nSymbols() const { return nsymbols; }
    enum mode { D4 = 0, D8 = 1 };
    bool mode;
    SliceRegionInfo getInfo(const int n) { return info[n]; }
protected:
		void makeGraph();
    void makeGraph2();
    int label(LabelType *imageOut, const uint8 bg);
    void encode(const uint8 *imageIn, const uint8 fg);
    const int cx;
    const int cy;
    const int slicesize;
    int nsymbols;
    int runcount;
    SliceRegionInfo *info;
    LabelType *map;
    RunLength *runs;
    int *linestart; // start of an x scan-line
};

#endif
