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

#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class FileDownloader : public QObject
{
	Q_OBJECT
public:
	explicit FileDownloader(QUrl imageUrl, QObject *parent = 0);

	virtual ~FileDownloader();

	QByteArray downloadedData() const;
	QNetworkReply::NetworkError error() { return networkError; }
	std::string errorStr() { return errorString.toStdString(); }
signals:
	void downloaded();

private slots:

	void fileDownloaded(QNetworkReply* pReply);

private:

	QNetworkAccessManager m_WebCtrl;
	QString errorString;
	QByteArray m_DownloadedData;
	QNetworkReply::NetworkError networkError;
};

#endif // FILEDOWNLOADER_H
