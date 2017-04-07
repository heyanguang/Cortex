#include <QGridLayout>
#include <QTextStream>
#include <QErrorMessage>
#include <QSettings>
#include "mainwindow.h"

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRendererCollection.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkGenericDataObjectReader.h>

#include <vtkCamera.h>
#include <vtkImageMapToWindowLevelColors.h>
#include <vtkImageData.h>
#include <vtkLookupTable.h>
#include <itkImage.h>
#include <itkExceptionObject.h>

#include "generatedsurface.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	reader = vtkKWImageIO::New();
	imageviewer = vtkImageViewer2::New();
	localVTKImage = vtkKWImage::New();
	renderPreview = new QVTKWidget();
	widgetCortex = new QVTKWidget();
	horizontalSlider = new QSlider();
	ui = new Ui::MainWindow;
	ui->setupUi(this);

	// add VTK widgets
	//ui->verticalLayoutL->addWidget(widget);
	ui->verticalLayoutR->addWidget(widgetCortex);
	//QGridLayout *layout = new QGridLayout();
	horizontalSlider->setEnabled(false);
	horizontalSlider->setRange(0, 0);
	horizontalSlider->setOrientation(Qt::Horizontal);
	ui->verticalLayoutL->addWidget(renderPreview, 0, 0);
	ui->verticalLayoutL->addWidget(horizontalSlider, 1, 0);
	//widgetCortex->setPalette(QPalette(QColor(Qt::green)));
	//renderPreview->setPalette(QPalette(QColor(Qt::green)));

	// Ugly hack to remove the garbage in the widget before that the
	// image is opened. Create an empty image and set it as imput data.
	// Without the image, it will cause an error.
	vtkImageData *emptyImage = vtkImageData::New();
	emptyImage->SetExtent(0, 0, 0, 0, 0, 0);
#if (VTK_MAJOR_VERSION < 6)
	emptyImage->SetScalarType(VTK_INT);
	emptyImage->SetNumberOfScalarComponents(1);
	emptyImage->AllocateScalars();
	m_imageviewer->GetWindowLevel()->SetInput(emptyImage);
#else
	emptyImage->AllocateScalars(VTK_INT, 1);
	imageviewer->GetWindowLevel()->SetInputData(emptyImage);
#endif
	emptyImage->Delete();

	renderPreview->SetRenderWindow(imageviewer->GetRenderWindow());
	imageviewer->SetSliceOrientationToXY();
	imageviewer->SetSlice(0);
	imageviewer->GetRenderer()->SetBackground(1, 1, 1);
	imageviewer->GetRenderer()->GetActiveCamera()->ParallelProjectionOn();
	imageviewer->GetRenderWindow()->GetInteractor()->SetInteractorStyle(0);
	renderPreview->update();

	// set up interactor
	interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	interactor->SetRenderWindow(widgetCortex->GetRenderWindow());

	// allow the user to interactively manipulate (rotate, pan, etc.) the camera, the viewpoint of the scene.
	auto style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	interactor->SetInteractorStyle(style);

	// set default data set
	filename = "../../../data/nucleon.mhd";
	readSettings();
	createActions();
}

MainWindow::~MainWindow()
{
	delete ui;
	delete renderPreview;
	delete widgetCortex;
	delete horizontalSlider;
	localVTKImage->Delete();
	reader->Delete();
	imageviewer->Delete();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	writeSettings();
	event->accept();
}

void MainWindow::open()
{
	// show file dialog. change filename only when the new filename is not empty.
	QString filter("Available Filetypes (*.nii.gz *.nii *.vtk)\n");
	QString filename_backup = filename;
	filename_backup = QFileDialog::getOpenFileName(this, QString(tr("Open a file")), filename_backup, filter);
	if (!filename_backup.isEmpty()) loadFile(filename_backup);
}

bool MainWindow::save()
{
	if (curFile.isEmpty()) return saveAs();
	else                   return saveFile(curFile);
}

bool MainWindow::saveAs()
{
	QFileDialog dialog(this);
	dialog.setWindowModality(Qt::WindowModal);
	dialog.setAcceptMode(QFileDialog::AcceptSave);
	dialog.exec();
	QStringList files = dialog.selectedFiles();

	if (files.isEmpty()) return false;

	return saveFile(files.at(0));
}

void MainWindow::about()
{
	QMessageBox::about(this, tr("About Cortex"),
		                     tr("The <b>Cortex</b> is a framework about the segmentation and"
		                     " analysis of MRI human brain images."));
}

bool MainWindow::onSliderChange(int z)
{
	imageviewer->SetSlice(z);
	renderPreview->update();
	return true;
}

void MainWindow::readSettings()
{
	QSettings settings("QtProject", "Cortex");
	QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
	QSize size = settings.value("size", QSize(400, 400)).toSize();
	resize(size);
	move(pos);
}

void MainWindow::writeSettings()
{
	QSettings settings("QtProject", "Cortex");
	settings.setValue("pos", pos());
	settings.setValue("size", size());
}

void MainWindow::createActions()
{
	this->setWindowIcon(QIcon(":/images/main.ico"));

	ui->action_Open->setIcon(QIcon(":/images/open.png"));
	ui->action_Open->setShortcuts(QKeySequence::Open);
	ui->action_Open->setStatusTip(tr("Open an existing file"));
	connect(ui->action_Open, SIGNAL(triggered()), this, SLOT(open()));

	ui->action_Save->setIcon(QIcon(":/images/save.png"));
	ui->action_Save->setShortcuts(QKeySequence::Save);
	ui->action_Save->setStatusTip("Save the document to disk");
	connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(save()));

	ui->action_SaveAs->setShortcuts(QKeySequence::SaveAs);
	ui->action_SaveAs->setStatusTip(tr("Save the document under a new name"));
	connect(ui->action_SaveAs, SIGNAL(triggered()), this, SLOT(saveAs()));

	connect(ui->action_About, SIGNAL(triggered()), this, SLOT(about()));

	connect(ui->action_AboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

	connect(ui->action_Exit, SIGNAL(triggered()), this, SLOT(close()));

	connect(horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(onSliderChange(int)));

	connect(ui->action_ContourSurface, SIGNAL(triggered()), this, SLOT(contourSurface()));

	connect(ui->action_MarchingCubes, SIGNAL(triggered()), this, SLOT(marchingCubes()));

	
}

void MainWindow::loadFile(const QString& filename)
{
	// show filename on window title
	this->setWindowTitle(filename);

	if (filename.endsWith("nii") || filename.endsWith("nii.gz"))
	{
		reader->SetFileName(filename.toStdString());
		try
		{
			reader->ReadImage();
		}
		catch (itk::ExceptionObject excp)
		{
			std::cerr << "Error while opening image" << excp.GetDescription() << std::endl;

			QErrorMessage error_message;
			error_message.showMessage(excp.GetDescription());
			error_message.exec();
			return;
		}

		double range[2];
		localVTKImage = reader->HarvestReadImage();
		localVTKImage->GetVTKImage()->GetScalarRange(range);
		vtkLookupTable *lookupTable = vtkLookupTable::New();
		lookupTable->SetValueRange(0.0, 1.0);
		lookupTable->SetSaturationRange(0.0, 0.0);
		lookupTable->SetRampToLinear();
		lookupTable->SetRange(range);
		lookupTable->Build();
		imageviewer->GetWindowLevel()->SetLookupTable(lookupTable);
		lookupTable->Delete();

#if (VTK_MAJOR_VERSION < 6)
		m_imageviewer->GetWindowLevel()->SetInput(m_localVTKImage->GetVTKImage());
#else
		imageviewer->GetWindowLevel()->SetInputData(localVTKImage->GetVTKImage());
#endif

		int *dimensions = localVTKImage->GetVTKImage()->GetDimensions();
		//imageviewer->GetRenderWindow()->SetSize(200, 200);
		imageviewer->Render();
		imageviewer->GetRenderer()->ResetCamera();
		imageviewer->GetRenderer()->GetActiveCamera()->SetParallelScale(dimensions[1]);
		renderPreview->update();

		horizontalSlider->setValue(0);
		horizontalSlider->setEnabled(true);
		horizontalSlider->setRange(0, dimensions[2]);

		std::ostringstream str_dimensions;
		str_dimensions << "[" << dimensions[0] << "," << dimensions[1] << "," << dimensions[2] << "]";
	}
	else if (filename.endsWith("vtk"))
	{
		// get local 8-bit representation of the string in locale encoding (in case the filename contains non-ASCII characters) 
		QByteArray ba = filename.toLocal8Bit();
		const char *filename_str = ba.data();

		// Read the file
		vtkSmartPointer<vtkGenericDataObjectReader> reader =
			vtkSmartPointer<vtkGenericDataObjectReader>::New();
		reader->SetFileName(filename_str);
		reader->Update();

		// Visualize
		vtkSmartPointer<vtkPolyDataMapper> mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputConnection(reader->GetOutputPort());
		mapper->ScalarVisibilityOff();

		vtkSmartPointer<vtkActor> actor =
			vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);
		actor->GetProperty()->SetDiffuseColor(1, 1, 1);

		vtkSmartPointer<vtkRenderer> renderer =
			vtkSmartPointer<vtkRenderer>::New();
		renderer->AddActor(actor);
		renderer->SetBackground(.2, .3, .4);

		// clean previous renderers and then add the current renderer
		auto window = widgetCortex->GetRenderWindow();
		auto collection = window->GetRenderers();
		auto item = collection->GetNumberOfItems();
		while (item)
		{
			window->RemoveRenderer(collection->GetFirstRenderer());
			item = collection->GetNumberOfItems();
		}
		window->AddRenderer(renderer);
		window->Render();

		// initialize the interactor
		interactor->Initialize();
		interactor->Start();
	}
}

bool MainWindow::saveFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		QMessageBox::warning(this, tr("Application"),
								   tr("Cannot write file %1:\n%2.")
								   .arg(fileName)
								   .arg(file.errorString()));
		return false;
	}

	QTextStream out(&file);
#ifndef QT_NO_CURSOR
	QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
	out << textEdit->toPlainText();
#ifndef QT_NO_CURSOR
	QApplication::restoreOverrideCursor();
#endif

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File saved"), 2000);
	return true;
}

void MainWindow::setCurrentFile(const QString &filename)
{
	curFile = filename;
	textEdit->document()->setModified(false);
	setWindowModified(false);

	QString shownName = curFile;
	if (curFile.isEmpty()) shownName = "untitled.txt";

	setWindowFilePath(shownName);
}

