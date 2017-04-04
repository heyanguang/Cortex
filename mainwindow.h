#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>

#include <iostream>
#include <memory>
#include <cstdlib>

#ifdef VTK_OPENGL2
#include <vtk_glew.h>
#include <QVTKWidget2.h>
#else
//#include <vtkgl.h>
#include <QVTKWidget.h>
#endif

#include "ui_mainwindow.h"

#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkKWImageIO.h>
#include <vtkKWImage.h>

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private:
	Ui::MainWindow                                          *ui;
	vtkImageViewer2                                         *imageviewer;
	vtkKWImageIO                                            *reader;
	vtkKWImage                                              *localVTKImage;
	QString                                                 filename;
	vtkSmartPointer<vtkRenderWindowInteractor>              interactor;
	QVTKWidget                                              *renderPreview;
	QVTKWidget                                              *widgetCortex;
	QSlider                                                 *horizontalSlider;

private slots:
	void loadFile();
	bool onSliderChange(int);
	bool on_action_ContourSurface_triggered();
	bool on_action_MarchingCubes_triggered();

private:
	void createActions();
};

#endif // MAINWINDOW_H
