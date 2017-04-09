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

#include "skullstrippingdialog.h"
#include "ui_skullstrippingdialog.h"
#include <brainsuitewindow.h>
#include <waitcursor.h>
#include <toolmanager.h>
#include <nonuniformitycorrectiondialog.h>
#include <brainsuitesettings.h>
#include <qdir.h>
#include <toolmanager.h>
#include <corticalextractionsequencedialog.h>
#include <corticalextractionsettings.h>
#include <quietset.h>
#include <bseguitool.h>
#include <skullandscalpdialog.h>
#include <brainsuitewindow_t.h>

BSEGUITool bseGUITool;

SkullStrippingDialog::SkullStrippingDialog(BrainSuiteWindow *brainSuiteWindow) :
  QDialog(brainSuiteWindow), brainSuiteWindow(brainSuiteWindow),
  ui(new Ui::SkullStrippingDialog)
{
  ui->setupUi(this);
  ui->erosionSizeSpinbox->blockSignals(true);
  ui->erosionSizeSpinbox->setRange(1,4);
  ui->progressBar->setRange(BSETool::ADFilter,bseGUITool.nSteps());
  ui->stepNameText->setText(("next step: " + bseGUITool.stepName()).c_str());
  ui->progressBar->setValue(bseGUITool.currentStep());
  checkStageInputs();
  updateStepText();
  updateDialogFromCES();
  ui->erosionSizeSpinbox->blockSignals(false);
}

void SkullStrippingDialog::updateDialogFromCES()
{
  ui->diffusionConstantEditBox->setText(QString::number(brainSuiteWindow->ces.bse.diffusionConstant));
  ui->diffusionIterationsEditBox->setText(QString::number(brainSuiteWindow->ces.bse.diffusionIterations));
  ui->edgeConstantEditBox->setText(QString::number(brainSuiteWindow->ces.bse.edgeConstant));
  ::setValueQuiet(ui->erosionSizeSpinbox,brainSuiteWindow->ces.bse.erosionSize);
  ui->trimSpinalCordCheckBox->setChecked(brainSuiteWindow->ces.bse.trimSpinalCord);
  ui->dilateFinalMaskCheckBox->setChecked(brainSuiteWindow->ces.bse.dilateFinalMask);
}

void SkullStrippingDialog::updateAutosaveInfo(bool valid)
{
  if (valid && BrainSuiteSettings::autosaveCorticalExtraction && !BrainSuiteSettings::autosavePrefix.empty())
  {
    std::string output = BrainSuiteSettings::autosavePrefix + ".bse.nii.gz";
    ui->autosaveLabel->setText(QString("skull stripped image will be saved to\n") + QDir::toNativeSeparators(QDir::cleanPath(output.c_str())));
  }
  else
  {
    ui->autosaveLabel->setText("autosave results is not enabled.");
  }
}

SkullStrippingDialog::~SkullStrippingDialog()
{
  delete ui;
}

void SkullStrippingDialog::setProgress(const int value, const int maxValue)
{
  ui->progressBar->setRange(0,maxValue);
  ui->progressBar->setValue(value);
  ui->progressBar->repaint();
}

void SkullStrippingDialog::updateStepText(std::string stepname)
{
  ui->stepNameText->setText(stepname.c_str());
  ui->stepNameText->repaint();
}

void SkullStrippingDialog::updateStepText()
{
  if (bseGUITool.isFinished())
  {
    updateStepText(bseGUITool.stepName());
  }
  else
  {
    updateStepText(std::string("Next Step: ") + bseGUITool.stepName());
  }
}

std::string SkullStrippingDialog::runningStepName()
{
  return bseGUITool.stepName();
}

bool SkullStrippingDialog::checkStageInputs()
{
  if (!brainSuiteWindow)
  {
    std::cerr<<"dialog is disconnected."<<std::endl;
    return false;
  }
  bool status=true;
  if (!brainSuiteWindow->brainSuiteDataManager.volume)
  {
    status = false;
  }
  return status;
}

void SkullStrippingDialog::updateToolSettings()
{
  updateCESfromDialog();
}

bool SkullStrippingDialog::autosaveOutputs()
{
  if (!brainSuiteWindow) return false;
  if (!brainSuiteWindow->toolManager.autosaveValid()) return false;
  if (!BrainSuiteSettings::autosaveCorticalExtraction) return false;
  std::string prefix = BrainSuiteSettings::autosavePrefix;
  if (!prefix.empty())
  {
    std::string ofname = prefix + ".mask.nii.gz";
    if (brainSuiteWindow->brainSuiteDataManager.vMask.write(ofname))
      std::cout<<"saved "<<ofname<<std::endl;
    else
      std::cerr<<"error writing "<<ofname<<std::endl;
    Vol3DBase *v = brainSuiteWindow->brainSuiteDataManager.volume->duplicate();
    if (v)
    {
      v->maskWith(brainSuiteWindow->brainSuiteDataManager.vMask);
      std::string ofname = prefix + ".bse.nii.gz";
      if (v->write(ofname))
        std::cout<<"saved "<<ofname<<std::endl;
      else
        std::cerr<<"error writing "<<ofname<<std::endl;
      delete v;
    }
    return true;
  }
  return false;
}

bool SkullStrippingDialog::isFinished()
{
  return bseGUITool.isFinished();
}

void SkullStrippingDialog::updateProgress()
{
  ui->progressBar->setValue(bseGUITool.currentStep());
  ui->progressBar->repaint();
  updateStepText();
}

bool SkullStrippingDialog::step()
{
  if (brainSuiteWindow)
  {
    bool state=bseGUITool.runStep(brainSuiteWindow);
    return state;
  }
  else
    return false;
}

void SkullStrippingDialog::on_applyButton_clicked()
{
  WaitCursor wc(this);
  updateToolSettings();
  while (step());
}

void SkullStrippingDialog::on_runStepButton_clicked()
{
  WaitCursor wc(this);
  updateToolSettings();
  step();
}

void SkullStrippingDialog::on_previousStepButton_clicked()
{
  bseGUITool.stepBack(brainSuiteWindow);
}

void SkullStrippingDialog::on_bfcButton_clicked()
{
  brainSuiteWindow->swapDialogs(this,brainSuiteWindow->toolManager.nonuniformityCorrectionDialog);
}

void SkullStrippingDialog::on_skullAndScalpButton_clicked()
{
  brainSuiteWindow->swapDialogs(this,brainSuiteWindow->toolManager.skullfinderDialog);
}

void SkullStrippingDialog::updateCESfromDialog()
{
  brainSuiteWindow->ces.bse.diffusionIterations = ui->diffusionIterationsEditBox->text().toInt();
  brainSuiteWindow->ces.bse.diffusionConstant = ui->diffusionConstantEditBox->text().toFloat();
  brainSuiteWindow->ces.bse.edgeConstant = ui->edgeConstantEditBox->text().toFloat();
  brainSuiteWindow->ces.bse.erosionSize = ui->erosionSizeSpinbox->value();
  brainSuiteWindow->ces.bse.trimSpinalCord = ui->trimSpinalCordCheckBox->isChecked();
  brainSuiteWindow->ces.bse.dilateFinalMask = ui->dilateFinalMaskCheckBox->isChecked();
  if (brainSuiteWindow->toolManager.corticalExtractionSequenceDialog)
    brainSuiteWindow->toolManager.corticalExtractionSequenceDialog->updateBSEParameters();
}

void SkullStrippingDialog::on_diffusionIterationsEditBox_textEdited(const QString & /* arg1 */)
{
  updateCESfromDialog();
}

void SkullStrippingDialog::on_diffusionConstantEditBox_textEdited(const QString & /* arg1 */)
{
  updateCESfromDialog();
}

void SkullStrippingDialog::on_edgeConstantEditBox_textEdited(const QString & /* arg1 */)
{
  updateCESfromDialog();
}

void SkullStrippingDialog::on_trimSpinalCordCheckBox_clicked()
{
  updateCESfromDialog();
}

void SkullStrippingDialog::on_erosionSizeSpinbox_valueChanged(int /* arg1 */)
{
  updateCESfromDialog();
}

void SkullStrippingDialog::on_dilateFinalMaskCheckBox_clicked()
{
  updateCESfromDialog();
}
