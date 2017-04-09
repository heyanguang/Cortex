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

#ifndef CONNECTIVITYVIEWDIALOG_H
#define CONNECTIVITYVIEWDIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <threaddialogstatus.h>
#include <sstream>

namespace Ui {
class ConnectivityViewDialog;
}

class BrainSuiteWindow;
class ConnectivityGLWidget;
class FiberTrackSet;

class ConnectivityViewDialog : public QDialog
{
  Q_OBJECT

public:
  enum CorticalAreas { AllFibers=0, AllLobes=1, FrontalLobe=2, ParietalLobe=3, TemporalLobe=4, OccipitalLobe=5, SubCortical=6, AllBrainAreas=7, AllLabeledAreas=8 };
  explicit ConnectivityViewDialog(BrainSuiteWindow *parent = 0);
  ~ConnectivityViewDialog();
  bool computeConnectivity(bool mergeCortialROIs);
  void saveMatrix();
  bool pickSubset(CorticalAreas area);
  FiberTrackSet *getSelection();
  FiberTrackSet *applyFilter(FiberTrackSet *tractSet);
  ThreadDialogStatus::StatusCode status() const { return statusCode; }
private:
  void keyReleaseEvent(QKeyEvent *);
  Ui::ConnectivityViewDialog *ui;
  BrainSuiteWindow *brainSuiteWindow;
  ConnectivityGLWidget *connectivityGLWidget;
  QGridLayout *gridLayout;
  std::ostringstream errorStream;
protected:
  ThreadDialogStatus::StatusCode statusCode;
};

#endif // CONNECTIVITYVIEWDIALOG_H
