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

#ifndef PialSurfaceDialog_H
#define PialSurfaceDialog_H

#include <QDialog>
#include <surflib.h>

class BrainSuiteWindow;
class SurfaceAlpha;

namespace Ui {
class PialSurfaceDialog;
}

class PialSurfaceDialog : public QDialog
{
    Q_OBJECT
    
public:
    enum ReturnState { NotRun=-1, Success=0, Error=1, CanceledByUser=2 };
    explicit PialSurfaceDialog(BrainSuiteWindow *parent = 0);
    ~PialSurfaceDialog();
    void updateDialogFromCES();
    void updateCESfromDialog();
    void setStatusText(std::string status);
    void updateStatusText();
    void updateStepText(std::string stepName);
    void setProgress(const int value, const int maxValue);
    bool checkStageInputs();
    bool step();
    std::string runningStepName();
    bool isFinished();
    void updateAutosaveInfo(bool valid);
private slots:
    void on_applyButton_clicked();

    void on_runStepButton_clicked();

    void on_previousStepButton_clicked();

    void on_nextTool_clicked();

    void on_restoreFromPreviousSessionButton_clicked();

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

    void on_pialLoadCustomMaskButton_clicked();

private:
    Ui::PialSurfaceDialog *ui;
    BrainSuiteWindow *brainSuiteWindow;
    std::ostringstream outputStream;
};

#endif // PialSurfaceDialog_H
