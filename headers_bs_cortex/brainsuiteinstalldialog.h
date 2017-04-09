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

#ifndef BRAINSUITEINSTALLDIALOG_H
#define BRAINSUITEINSTALLDIALOG_H

#include <QDialog>

namespace Ui {
class BrainSuiteInstallDialog;
}
class BrainSuiteWindow;
class BrainSuiteInstallDialog : public QDialog
{
  Q_OBJECT

public:
  explicit BrainSuiteInstallDialog(BrainSuiteWindow *parent, QString installDir);
  ~BrainSuiteInstallDialog();
  void setInstallDirectory(QString s);
  void setContinueText(QString s);
  bool copyFolder(std::ostream &filelog, QString sourceFolder, QString destFolder, bool recursive=true);
  void setMainText(std::string);
  void setCheckInstallFlag(bool flag);
private slots:
  void on_installCommandLinkButton_clicked();

  void on_proceedCommandLinkButton_clicked();

  void on_selectPushButton_clicked();

  void on_resetToDefaultLocationPushButton_clicked();

private:
  Ui::BrainSuiteInstallDialog *ui;
  BrainSuiteWindow *brainSuiteWindow;
  QString installDir;
  QString defaultInstallDir;
  QString continueText;
};

#endif // BRAINSUITEINSTALLDIALOG_H
