#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <QFileDialog>
#include <QPlainTextEdit>

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

protected:
	void closeEvent(QCloseEvent *event);

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
	QString													curFile;
	QPlainTextEdit                                          *textEdit;

private slots:
    void open();
	bool save();
	bool saveAs();
	void about();
	bool onSliderChange(int);
	bool contourSurface();
	bool marchingCubes();

private:
	void readSettings();
	void writeSettings();
	void createActions();
	void loadFile(const QString& filename);
	bool saveFile(const QString& filename);
	void setCurrentFile(const QString &filename);
};

#endif // MAINWINDOW_H
