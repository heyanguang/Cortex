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

#ifndef BrainSuiteQTSettings_H
#define BrainSuiteQTSettings_H

#include <string>
#include <QString>
#include <qsettings.h>

class BrainSuiteQtSettings
{
public:
    static void initialize();
    static std::string titleString;
		static std::string programCredits;
		static std::string programCreditsLibs;
    static std::string website;
    static std::string websiteForum;
    static std::string websiteDownload;
    static std::string qtinstalldir;
    static std::string qtinstallkey;
    static std::string qtsvregdir;
    static std::string qtsvregkey;
    static std::string qtcheckforupdateskey;
		static std::string qtuseNativeFileDialogsKey;
    static std::string latestVersionServer;
		static std::string qtMostRecentDirectoryKey;
    static bool enableCheckForUpdates;
		static void setInstallDir(std::string installDir);
    static bool setEnableCheckForUpdates(const bool state);
		static bool setUseNativeFileDialogs(const bool state);
		static bool getUseNativeFileDialogs() { return useNativeFileDialogs; }
    static std::string svregVersion;
    static std::string platform;
		static QString brainSuiteQtKey;
		static std::string getCurrentDirectory() { return currentDirectory; }
		static void setCurrentDirectory(std::string directoryName);
		static void disableSavingDirectory() { startingUp=true; }
		static void enableSavingDirectory() { startingUp=false; }
private:
		static void setKeyValue(std::string key, bool value);
		static void setKeyValue(std::string key, std::string value);
		static std::string currentDirectory;
		static bool useNativeFileDialogs;
		static bool startingUp;
};

#endif // BrainSuiteQTSettings_H
