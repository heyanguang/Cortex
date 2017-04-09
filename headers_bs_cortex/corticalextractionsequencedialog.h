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

#ifndef CORTICALEXTRACTIONSEQUENCEDIALOG_H
#define CORTICALEXTRACTIONSEQUENCEDIALOG_H

#include <QDialog>
#include <sstream>
#include <extractionstages.h>

class BrainSuiteWindow;

namespace Ui {
class CorticalExtractionSequenceDialog;
}

class ExtractionGUITool;

class CorticalExtractionSequenceDialog : public QDialog
{
  Q_OBJECT
public:
  explicit CorticalExtractionSequenceDialog(BrainSuiteWindow *parent = 0);
  ~CorticalExtractionSequenceDialog();
  ExtractionStages::Stages nextStage(ExtractionStages::Stages stage);
  ExtractionStages::Stages presentStage(ExtractionStages::Stages stage);
  ExtractionStages::Stages lastCheckedStage();
  ExtractionGUITool *currentExtractionTool();
  ExtractionGUITool *extractionTool(ExtractionStages::Stages stage);
  std::string formAutosavePrefix(std::string filename);
  bool updateStepText(std::string s);
  void setProgress(const int value, const int maxValue);
  void highlightPresentStage();
  void highlightNextStage();
  void highlightStage(ExtractionStages::Stages stage, bool disable);
  template <class Tool>
  bool runToolStep(Tool *tool);
  bool updateCurrentStage(); // returns true if state change?
  bool showNextTool(ExtractionStages::Stages nextStage);
  void updateProgress(bool running=false);
  bool runStep();
  bool runStage();
  bool runAll();
  void showCurrentTool();
  void updateAutosaveText();
  bool autosaveValid();
  void updateBFCwidgets();
  void updateBSEParameters();
  void updateSkullfinderParameters();
  void updateBFCParameters();
  void updatePVCParameters();
  void updateCerebroParameters();
  void updateCortexParameters();
  void updateScrubMaskParameters();
  void updateTCAParameters();
  void updateDewispParameters();
  void updateICSParameters();
  void updatePialParameters();
  void updateSVRegParameters();
  void updateAllfromCES();
  void updateCES_BSEParameters();
  void updateCES_SkullfinderParameters();
  void updateCES_BFCParameters();
  void updateCES_PVCParameters();
  void updateCES_CerebroParameters();
  void updateCES_CortexParameters();
  void updateCES_ScrubMaskParameters();
  void updateCES_TCAParameters();
  void updateCES_DewispParameters();
  void updateCES_ICSParameters();
  void updateCES_PialParameters();
  void updateCES_SVRegParameters();
  void suggestOutputs();
private slots:
  void on_autosaveOutputCheckBox_clicked();

  void on_suggestOutputsPushButton_clicked();

  void on_runStepPushButton_clicked();

  void on_runStagePushButton_clicked();

  void on_runAllPushButton_clicked();

  void on_filenamePrefixLineEdit_textEdited(const QString &arg1);

  void on_workingDirectoryLineEdit_textEdited(const QString &arg1);

  void on_workingDirectoryPushButton_clicked();

  void on_diffusionIterationsEditBox_textEdited(const QString &arg1);

  void on_diffusionConstantEditBox_textEdited(const QString &arg1);

  void on_edgeConstantEditBox_textEdited(const QString &arg1);

  void on_dilateFinalMaskCheckBox_clicked();

  void on_trimSpinalCordCheckBox_clicked();

  void on_erosionSizeSpinbox_valueChanged(int arg1);

  void on_iterativeModeCheckBox_clicked();

  void on_histogramRadiusEditBox_textEdited(const QString &arg1);

  void on_sampleSpacingEditBox_textEdited(const QString &arg1);

  void on_controlPointSpacingEditBox_textEdited(const QString &arg1);

  void on_splineStiffnessEditBox_textEdited(const QString &arg1);

  void on_cuboidRadioButton_clicked();

  void on_ellipsoidRadioButton_clicked();

  void on_biasRangeLowerEditBox_textEdited(const QString &arg1);

  void on_biasRangeUpperEditBox_textEdited(const QString &arg1);

  void on_spatialPriorWeightingEditBox_textEdited(const QString &arg1);

  void on_parameterPageComboBox_currentIndexChanged(int index);

  void on_skullStrippingCheckBox_pressed();

  void on_biasFieldCorrectionCheckBox_pressed();

  void on_tissueClassificationCorrectionCheckBox_pressed();

  void on_cerebrumLabelingCheckBox_pressed();

  void on_innerCortexMaskCheckBox_pressed();

  void on_scrubMaskCheckBox_pressed();

  void on_topologyCorrectionCheckBox_pressed();

  void on_dewispCheckBox_pressed();

  void on_innerCorticalSurfaceCheckBox_pressed();

  void on_pialSurfaceCheckBox_pressed();

  void on_hemisplitCheckBox_pressed();

  void on_registerLabelBrainCheckBox_pressed();

  void on_linearConvergenceEditBox_textEdited(const QString &arg1);

  void on_warpConvergenceEditBox_textEdited(const QString &arg1);

  void on_warpLevelSpinBox_valueChanged(int arg1);

  void on_costFunctionComboBox_currentIndexChanged(int index);

  void on_verboseCheckBox_clicked();

  void on_showAlignedAtlasAsOverlayCheckBox_clicked();

  void on_atlasPushButton_clicked();

  void on_labelsPushButton_clicked();

  void on_tempPathPushButton_clicked();

  void on_tissueThresholdEditBox_textEdited(const QString &arg1);

  void on_foregroundThresholdEditBox_textEdited(const QString &arg1);

  void on_backgroundThresholdEditBox_textEdited(const QString &arg1);

  void on_minimumCorrectionEditBox_textEdited(const QString &arg1);

  void on_maximumCorrectionEditBox_textEdited(const QString &arg1);

  void on_fillOffsetEditBox_textEdited(const QString &arg1);

  void on_smoothingIterationsEditBox_textEdited(const QString &arg1);

  void on_smoothingConstantEditBox_textEdited(const QString &arg1);

  void on_curvatureWeightEditBox_textEdited(const QString &arg1);

  void on_dewispThresholdEditBox_textEdited(const QString &arg1);

  void on_dewispMaximumIterationsEditBox_textEdited(const QString &arg1);

  void on_pialPresmoothIterationsEditBox_textEdited(const QString &arg1);

  void on_pialIterationsEditBox_textEdited(const QString &arg1);

  void on_pialCollisionDetectionRadiusEditBox_textEdited(const QString &arg1);

  void on_pialThicknessLimitEditBox_textEdited(const QString &arg1);

  void on_pialStepSizeEditBox_textEdited(const QString &arg1);

  void on_pialTissueThresholdEditBox_textEdited(const QString &arg1);

  void on_pialSmoothingConstantEditBox_textEdited(const QString &arg1);

  void on_pialRadialConstantEditBox_textEdited(const QString &arg1);

  void on_pialUpdateSurfaceIntervalEditBox_textEdited(const QString &arg1);

  void on_pialConstrainWithCerebrumMaskCheckBox_clicked();

  void on_skullComputeThresholdsCheckBox_clicked();

  void on_skullThresholdEditBox_textEdited(const QString &arg1);

  void on_scalpThresholdEditBox_textEdited(const QString &arg1);

  void on_skullfinderCheckBox_pressed();

  void on_pialLoadCustomMaskButton_clicked();

  void on_surfaceRegistrationOnlyCheckBox_clicked();

  void on_refineSulcalCurvesCheckBox_clicked();

  void on_skullStrippingCheckBox_clicked();

  void on_skullfinderCheckBox_clicked();

  void on_biasFieldCorrectionCheckBox_clicked();

  void on_tissueClassificationCorrectionCheckBox_clicked();

  void on_cerebrumLabelingCheckBox_clicked();

  void on_innerCortexMaskCheckBox_clicked();

  void on_scrubMaskCheckBox_clicked();

  void on_topologyCorrectionCheckBox_clicked();

  void on_dewispCheckBox_clicked();

  void on_innerCorticalSurfaceCheckBox_clicked();

  void on_pialSurfaceCheckBox_clicked();

  void on_hemisplitCheckBox_clicked();

  void on_registerLabelBrainCheckBox_clicked();

  void on_labeledAtlasComboBox_currentIndexChanged(int index);

  void on_useCentroidsCheckBox_clicked();

  void on_extendLabelsCheckBox_clicked();

  void on_includeAllSubcorticalLabelsCheckBox_clicked();

  void on_applyCortexThresholdPushButton_clicked();

private:
  Ui::CorticalExtractionSequenceDialog *ui;
  BrainSuiteWindow *brainSuiteWindow;
  ExtractionStages::Stages currentStage;
};

#endif // CORTICALEXTRACTIONSEQUENCEDIALOG_H
