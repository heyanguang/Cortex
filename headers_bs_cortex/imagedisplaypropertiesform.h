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

#ifndef IMAGEDISPLAYPROPERTIESFORM_H
#define IMAGEDISPLAYPROPERTIESFORM_H

#include <QWidget>
#include <dsimagerangecontrol.h>

class BrainSuiteWindow;
namespace Ui {
class ImageDisplayPropertiesForm;
}

class ImageDisplayPropertiesForm : public QWidget
{
	Q_OBJECT
	
public:
	explicit ImageDisplayPropertiesForm(BrainSuiteWindow *brainSuiteWindow, QWidget *parent = 0);
	~ImageDisplayPropertiesForm();
    QSize sizeHint() const;
	void updateDisplay();
	void setSliderRanges();
    void setImageVolumeSliderRange();
    void setImageOverlay1SliderRange();
    void setImageOverlay2SliderRange();
    void updateNames();
	DSImageRangeControl *imageSlider();
	DSImageRangeControl *imageOverlay1Slider();
	DSImageRangeControl *imageOverlay2Slider();
	bool setLUT1symmetric(bool state);
	bool setLUT2symmetric(bool state);
	bool setLUT3symmetric(bool state);
private slots:
	void on_imageVolumeButton_clicked();
	void on_imageOverlay1Button_clicked();
	void on_imageOverlay2Button_clicked();
	void on_labelVolumeButton_clicked();
	void on_maskVolumeButton_clicked();
	void on_imageOverlay1AlphaSlider_valueChanged(int value);
	void on_imageOverlay2AlphaSlider_valueChanged(int value);
	void on_labelAlphaSlider_valueChanged(int value);
	void on_imageOverlay1Alpha_textEdited(const QString &arg1);
	void on_imageVolumeFilename_fileDropped(const QString &filename);
	void on_imageOverlay1Filename_fileDropped(const QString &filename);
	void on_imageOverlay2Filename_fileDropped(const QString &filename);
	void on_maskVolumeFilename_fileDropped(const QString &filename);
	void on_labelVolumeFilename_fileDropped(const QString &filename);
	void on_imageVolumeMaxText_textEdited(const QString &arg1);
	void on_imageOverlay2BrightnessSlider_rangeChanged();
	void on_imageVolumeBrightnessSlider_rangeChanged();
	void on_imageOverlay1BrightnessSlider_rangeChanged();
	void on_imageVolumeBrightnessSlider_rightClick(const QPoint &);
	void on_imageOverlay1BrightnessSlider_rightClick(const QPoint &);
	void on_imageOverlay2BrightnessSlider_rightClick(const QPoint &);
	void on_imageOverlay1MaxText_textEdited(const QString &arg1);
	void on_imageOverlay2MaxText_textEdited(const QString &arg1);
	void on_imageOverlay2Alpha_textEdited(const QString &arg1);
	void on_imageVolumeMinText_textEdited(const QString &arg1);
	void on_imageOverlay1MinText_textEdited(const QString &arg1);
	void on_imageOverlay2MinText_textEdited(const QString &arg1);
	void on_labelAlphaText_textEdited(const QString &arg1);

	void on_closeOverlay1PushButton_clicked();
	void on_closeOverlay2PushButton_clicked();
	void on_closeLabelVolumePushButton_clicked();
	void on_closeMaskVolumePushButton_clicked();


	void on_showVolumeCheckBox_clicked();
	void on_showOverlay1VolumeCheckBox_clicked();
	void on_showOverlay2VolumeCheckBox_clicked();
	void on_showLabelVolumeCheckBox_clicked();

  void on_lutSymmetricPushButton_clicked(bool checked);
  void on_adjustRange1PushButton_clicked();
  void on_lut2SymmetricPushButton_clicked(bool checked);
  void on_lut3SymmetricPushButton_clicked(bool checked);
  void on_adjustRange2PushButton_clicked();
  void on_adjustRange3PushButton_clicked();

private:
	Ui::ImageDisplayPropertiesForm *ui;
	BrainSuiteWindow *brainSuiteWindow;
};

#endif // IMAGEDISPLAYPROPERTIESFORM_H
