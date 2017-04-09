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

#ifndef DSGLSlider_H
#define DSGLSlider_H

#include <dspoint.h>
class QPainter;

class DSGLSlider {
public:
	DSGLSlider();
    void renderQt(QPainter &painter, int x, int y, int width, int height, float thresh);
    void render(int x, int y, int width, int height, float thresh);
	bool inside(const float x, const float y) const;
	int triangleSize;
	int triangleOffset;
	int x0,x1,y0,y1;
	int penumbra;
	DSPoint color0;
	DSPoint color1;
	DSPoint frameColor;
	DSPoint indicatorColor;
};

#endif
