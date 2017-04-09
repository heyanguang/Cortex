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

#ifndef TOOLMANAGER_H
#define TOOLMANAGER_H

#include <memory>

class ImageDisplayPropertiesForm;
class SkullStrippingDialog;
class ConnectivityViewDialog;
class TissueClassificationDialog;
class NonuniformityCorrectionDialog;
class CerebrumExtractionDialog;
class CortexIdentificationDialog;
class ScrubMaskDialog;
class TopologicalCorrectionDialog;
class DewispDialog;
class InnerCorticalSurfaceDialog;
class PialSurfaceDialog;
class SplitHemispheresDialog;
class CorticalExtractionSequenceDialog;
class DSGLViewDialog;
class SVRegistrationDialog;
class SurfaceDisplayForm;
class DiffusionToolboxForm;
class DelineationToolboxForm;
class CurveToolboxForm;
class SkullAndScalpDialog;

#include <memory>

class ToolManager {
public:
  ToolManager();
  ~ToolManager();
  void updateFromCES();
  SurfaceDisplayForm *surfaceDisplayForm;
  DelineationToolboxForm *delineationToolboxForm;
  ImageDisplayPropertiesForm *imageDisplayPropertiesForm;
  DiffusionToolboxForm *diffusionToolboxForm;
  CurveToolboxForm *curveToolboxForm;

  std::unique_ptr<DSGLViewDialog> dsglViewDialog;
  std::unique_ptr<ConnectivityViewDialog> connectivityViewDialog;
  std::unique_ptr<SkullStrippingDialog> skullStrippingDialog;
  std::unique_ptr<SkullAndScalpDialog> skullfinderDialog;
  std::unique_ptr<NonuniformityCorrectionDialog> nonuniformityCorrectionDialog;
  std::unique_ptr<TissueClassificationDialog> tissueClassificationDialog;
  std::unique_ptr<CerebrumExtractionDialog> cerebrumExtractionDialog;
  std::unique_ptr<CortexIdentificationDialog> cortexIdentificationDialog;
  std::unique_ptr<ScrubMaskDialog> scrubMaskDialog;
  std::unique_ptr<TopologicalCorrectionDialog> topologicalCorrectionDialog;
  std::unique_ptr<DewispDialog> dewispDialog;
  std::unique_ptr<InnerCorticalSurfaceDialog> innerCorticalSurfaceDialog;
  std::unique_ptr<PialSurfaceDialog> pialSurfaceDialog;
  std::unique_ptr<SplitHemispheresDialog> splitHemispheresDialog;
  std::unique_ptr<SVRegistrationDialog> svRegistrationDialog;
  std::unique_ptr<CorticalExtractionSequenceDialog> corticalExtractionSequenceDialog;
  bool autosaveValid();
};

#endif // TOOLMANAGER_H
