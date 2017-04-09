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

#ifndef DisplayCode_H
#define DisplayCode_H

class DisplayCode {
public:
  enum Code {
    None          = 0x0000, // Nothing
    Dirty         = 0x0001, // Redraw
    Image1Only    = 0x0002, // Turn off everything but primary volume Image1Only
    ShowOverlay1  = 0x0010, // Turn on first overlay
    HideOverlay1  = 0x0020, // Turn off first overlay
    ShowOverlay2  = 0x0040, // Turn on second overlay
    HideOverlay2  = 0x0080, // Turn off second overlay
    MaskOn        = 0x0100, // Enable masking
    MaskOff       = 0x0200, // Disable masking
    ShowLabels    = 0x0400, // Show volume labels
    HideLabels    = 0x0800, // Hide volume labels
    RedrawView    = 0x1000, // Redraw the image view
    RedrawSurface = 0x2000  // Redraw the surface view
  };
};

#endif // DisplayCode_H

