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

#ifndef TopologicalCorrectionDialog_H
#define TopologicalCorrectionDialog_H

#include <QDialog>
class BrainSuiteWindow;

namespace Ui {
class TopologicalCorrectionDialog;
}

class TopologicalCorrectionDialog : public QDialog
{
    Q_OBJECT
    
public:
		enum TCAState { Correction, Finished };
    explicit TopologicalCorrectionDialog(BrainSuiteWindow *parent = 0);
    ~TopologicalCorrectionDialog();
		void updateDialogFromCES();
		void updateCESfromDialog();
	void setStatusText(std::string status);
    void updateStepText(std::string status);
	bool checkStageInputs();
	bool fixTopology();
	bool step();
	std::string runningStepName();
	bool isFinished();
	void updateAutosaveInfo(bool valid);
	void setProgress(const int value, const int maxValue);
private slots:
    void on_applyButton_clicked();

		void on_nextTool_clicked();

		void on_restoreFromPreviousSessionButton_clicked();

		void on_minimumCorrectionEditBox_textEdited(const QString &arg1);

		void on_maximumCorrectionEditBox_textEdited(const QString &arg1);

		void on_fillOffsetEditBox_textEdited(const QString &arg1);

private:
    Ui::TopologicalCorrectionDialog *ui;
    BrainSuiteWindow *brainSuiteWindow;
		TCAState tcaState;
};

#endif // TopologicalCorrectionDialog_H
