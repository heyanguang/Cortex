// Copyright (C) 2016 The Regents of the University of California
//
// Created by David W. Shattuck, Ph.D.
//
// This file is part of Cortex.
//
// Cortex is free software; you can redistribute it and/or
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

#ifndef CortexModeler_H
#define CortexModeler_H

#include <vol3d.h>

class CortexModeler {
public:
	enum SurfaceType { Cerebrum, Cerebellum };
	CortexModeler() : thresh(0.5f), verbosity(1) {}
	bool findVentricles(SurfaceType surfaceType, Vol3D<float> &vFractions, Vol3D<uint8> &vMask, Vol3D<uint8> &vLabeledLobes, float ventricleThreshold);
	bool whiteMatterFromFractions(SurfaceType surfaceType, Vol3D<float> &vFractions, Vol3D<uint8> &vMask, Vol3D<uint8> &vLabeledLobes, bool includeAllSubcorticalAreas);
	bool greyMatterFromFractions(SurfaceType surfaceType, Vol3D<float> &vFractions, Vol3D<uint8> &vMask, Vol3D<uint8> &vLabeledLobes);
	void formPHWM(Vol3D<uint8> &vPHWM,Vol3D<uint8> &vLabel, Vol3D<float32> &vFractions);

	std::string errorString;
	float thresh;
	int verbosity;
	Vol3D<uint8> vVentricles;
};

#endif
