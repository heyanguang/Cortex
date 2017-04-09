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

#ifndef WELCOMESPLASHPAGE_H
#define WELCOMESPLASHPAGE_H

#include <QWidget>

namespace Ui {
class WelcomeSplashPage;
}

class BrainSuiteWindow;
class DSFilePathButton;
class FileDownloader;

class WelcomeSplashPage : public QWidget
{
  Q_OBJECT

public:
  explicit WelcomeSplashPage(QWidget *parent = 0);
  ~WelcomeSplashPage();
  QRect defaultSize;
  void updateRecentlyUsedFiles();
  void attachAndInitialize(BrainSuiteWindow *);
  void checkForUpdates();
private slots:
  void readVersionFromWeb();
  void on_visitBrainSuiteWebsiteCommandLinkButton_clicked();

  void on_visitBrainSuiteUserForumCommandLinkButton_clicked();

  void on_openTractographyCommandLinkButton_clicked();

  void on_openBSTCommandLinkButton_clicked();

  void on_openImageCommandLinkButton_clicked();

  void on_openSurfaceCommandLinkButton_clicked();

  void on_recentFilePushButton_clicked();

  void on_recentFilePushButton2_clicked();

  void on_recentFilePushButton3_clicked();

  void on_recentFilePushButton4_clicked();

  void on_recentFilePushButton5_clicked();

  void on_recentFilePushButton6_clicked();

  void on_recentFilePushButton7_clicked();

  void on_recentFilePushButton8_clicked();

  void on_openProtocolCurveLinkButton_clicked();

  void on_clearListPushButton_clicked();

  void on_newVersionLabel_clicked();

private:
  void loadRecentFile(size_t index);
  Ui::WelcomeSplashPage *ui;
  BrainSuiteWindow *brainSuiteWindow;
  std::vector<DSFilePathButton *> fileButtons;
  std::vector<std::string> filenames;
  FileDownloader *downloader;
};

#endif // WELCOMESPLASHPAGE_H
