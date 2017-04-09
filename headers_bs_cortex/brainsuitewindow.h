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

#ifndef BrainSuiteWindow_H
#define BrainSuiteWindow_H

#include <QMainWindow>
#include <list>
#include <ipoint3d.h>
#include <vol3d.h>
#include <imagestate.h>
#include <brainsuitedatamanager.h>
#include <toolmanager.h>
#include <corticalextractiondata.h>
#include <labeldescriptionset.h>
#include <corticalextractionsettings.h>
#include <qfiledialog.h>
#include <qsplashscreen.h>

namespace Ui {
class BrainSuiteWindow;
}

class DSGLWidget;
class ImageFrame;
class ImageWidget;
class Vol3DBase;
class ImageScale;
class SurfaceAlpha;
class FiberTrackSet;
class ImagePort;
class ImageWidget;
class WelcomeSplashPage;
class QDebugStream;
class QTimer;

class BrainSuiteWindow : public QMainWindow {
  Q_OBJECT
  friend class DSGLViewDialog;
public:
  QPixmap pixmap;
  QSplashScreen splash;
  enum ViewMode { NoView=-1, Ortho3D=0, Axial=1, Coronal=2, Sagittal=3, SurfaceOnly=4 };
  ViewMode viewMode,lastViewMode;
  class ViewSettings {
  public:
    ViewSettings();
    bool singleView;
    bool syncGL;
    bool blockSync;
  };
  BrainSuiteWindow(int argc, char *argv[], QWidget *parent = 0);
  ~BrainSuiteWindow();
  template <class Form>
  bool attachFormToDockWidget(Form *&form, QDockWidget *dockWidget, std::string menu, std::string tooltip);
  std::string getOpenImageFilename();
  std::string getOpenFilenameDS(std::string caption, std::string filter);
  std::string getDirectory(std::string currentPath, std::string queryText);
  QString dsGetSaveFileNameQS(QString title, QString filter, QString defaultName);
  std::string dsGetSaveFileName(std::string title, std::string filter, std::string defaultName);
  void setSinglePort(int portNo);
  void initializeSettings();
  void checkForSVRegUpdate();
  IPoint3D newPosition() const;
  void checkAutosavePath();
  void clearMRUList();
  void setCerebrumAtlasFile();
  void setCerebrumAtlasLabelFile();
  void setCerebrumTempDirectory();
  void resetClippingAndPosition();
  void savePortScreenShot(int portNo);
  bool setSVRegDirectory(std::string directory);

  void updateToolboxChecks();
  void setShowTensors(bool flag);
  void setShowFibers(bool flag);
  void setShowSurfaces(bool flag);
  void setShowODFs(bool flag);
  void setShowLighting(bool flag);
  void showSurfaceDisplayProperties();
  void updateSurfaceDisplayLists();
  void moveToWC(const DSPoint &p, QMouseEvent *event);
  void moveTo(const DSPoint &p);
  void moveTo(const IPoint3D &p);
  void initializeColorTable();
  bool checkInstall();
  bool setCurrentDirectory(std::string directory);
  void updateMenuChecks();
  bool setMaskUndoDescription(std::string description);
  void shiftImageViews(ImageWidget *widget, QPoint delta);
  void initializeSurfaceView();
  void initializeWindows();
  bool updateImageDisplayProperties();
  bool loadExtractionStudy(CorticalExtractionData::Stages state);
  void updateVolumeView(bool autoScale); // for use after a new volume is loaded
  void togglePort(DSGLWidget *widget);
  void togglePort(ImageWidget *widget);
  ViewSettings viewSettings;
  bool newLabelVolume();
  void updateRecentFileActions();
  void createMenus();
  void createActions();
  void createToolbars();
  void status(std::string statusMessage);
  void setZoomLevel(int n);
  void zoomIn();
  void zoomOut();
  void zoomUnity();
  void zoomSmallest();
  void brighter();
  void darker();
  void updateImageDisplaySliders();
  void updateImageNames();
  void updateSurfaceView();
  void markImagesDirty();
  void updateImages();
  void repaintImages();
  void addRecentFile(std::string ifname);
  bool loadFile(std::string ifname);
  IPoint3D newVolumePosition(IPoint3D position);
  void setVolumePosition(IPoint3D newVolumePosition, const bool forcePaint=false);
  IPoint3D currentVolumePosition;
  void autoscalePrimaryVolume();
  void autoscaleOverlay1();
  void autoscaleOverlay2();
  void setVolumeBrightness(const ImageScale &brightness);
  void setOverlay1Brightness(const ImageScale &brightness);
  void setOverlay2Brightness(const ImageScale &brightness);
  bool editingLabels();
  bool editingMask();
  bool alwaysEditMask();
  void autoscaleImages();
  void setOverlay1Alpha(int alpha);
  void setOverlay2Alpha(int alpha);
  void setLabelAlpha(int alpha);
  void mousePressed(ImageWidget *port, const IPoint3D &position, QMouseEvent *event);
  void mouseMoveTo(ImageWidget *port, const IPoint3D &position, QMouseEvent *event, bool alwaysSync3D=false);
  void mouseReleased(ImageWidget *port, const IPoint3D &position, QMouseEvent *event);
  void mouseDoubleClicked(ImageWidget *port, const IPoint3D &position, QMouseEvent *event);
  ImageState imageState;
  BrainSuiteDataManager brainSuiteDataManager;
  CorticalExtractionData corticalExtractionData;
  template <class CurrentDialog, class NextDialog>
  void swapDialogs(CurrentDialog *currentDialog, std::unique_ptr<NextDialog> &nextDialog);
  ToolManager toolManager;
  ImageWidget *activeImageWidget();
  int currentPort() { return activePort; }
  DSPoint getSurfaceBackgroundColor();
  void setSurfaceBackgroundColor(DSPoint backgroundColor);
  void detachDSGLView();
  bool saveConnectivityMatrix(std::string ofname);
  bool saveConnectivityMatrix();
  void setShowVolume(bool state);
  void setShowOverlay1(bool state);
  void setShowOverlay2(bool state);
  void setShowLabels(bool state);
  void setShowMask(bool state);
  void setShowLabelOutline(bool state);
  CorticalExtractionSettings ces;
  bool disablePathChecking; // used when loading many volumes at once, e.g., through a bst or through drag-n-drop
  QFileDialog::Options fileDialogOptions;
  void setActivePort(const int nextPort);
  void moveToFirstVoxelLabeled(int labelID);
  bool saveODFEig(std::string ofname);
  bool loadODFEig(std::string ifname);
  void zoomBestFit();
  void hideAllSurfaces();
  void showSingleSurface(SurfaceAlpha *primarySurface);
  bool addSurface(SurfaceAlpha *surface, bool giveOwnership);
  void updateView(uint32 viewUpdateCode);
  void loadVolume(Vol3DBase *vol, bool autoScale);
  bool loadVolume(std::string labelFilename);
  bool loadVolume();
  bool saveVolume(std::string labelFilename);
  bool saveVolume();
  void closeVolume();
  bool loadCustomCerebrumMask(std::string maskFilename);
  bool loadCustomCerebrumMask();
  bool loadOverlay1Volume(Vol3DBase *volume, bool autoscale);
  bool loadOverlay1Volume(std::string overlayFilename, bool noScale=false);
  bool loadOverlay1Volume();
  bool saveOverlay1Volume(std::string overlayFilename);
  bool saveOverlay1Volume();
  void closeOverlay1Volume();
  bool loadOverlay2Volume(Vol3DBase *volume, bool autoscale);
  bool loadOverlay2Volume(std::string overlayFilename);
  bool loadOverlay2Volume();
  bool saveOverlay2Volume(std::string overlayFilename);
  bool saveOverlay2Volume();
  void closeOverlay2Volume();
  bool loadCurveSet(std::string curvesetFilename);
  bool loadCurveSet();
  bool saveCurveSet(std::string curvesetFilename);
  bool saveCurveSet();
  bool loadCurveProtocol(std::string curveProtocolFilename);
  bool loadCurveProtocol();
  bool loadLabelVolume(std::string labelFilename);
  bool loadLabelVolume();
  bool saveLabelVolume(std::string labelFilename);
  bool saveLabelVolume();
  void closeLabelVolume();
  bool loadMaskVolume(std::string maskFilename);
  bool loadMaskVolume();
  bool saveMaskVolume(std::string maskFilename);
  bool saveMaskVolume();
  void closeMaskVolume();
  bool loadUCF(std::string ifname);
  bool loadProtocolCurveset(std::string ifname);
  bool loadProtocolCurveset();
  bool loadSurface();
  SurfaceAlpha *loadSurface(std::string surfaceFilename);
  bool loadHARDISHC();
  bool loadHARDISHC(std::string hardiFilename);
  bool loadFiberTrackSet();
  bool loadFiberTrackSet(std::string tractFilename);
  bool loadLabelDescriptionFile();
  bool loadLabelDescriptionFile(std::string labelDescriptionFilename);
  bool saveLabelDescriptionFile();
  bool saveLabelDescriptionFile(std::string labelDescriptionFilename);
  bool loadBSTFile();
  bool loadBSTFile(std::string bstFilename);
  template <class DialogType> void showDialog(std::unique_ptr<DialogType> &dialog);
  void makeLUTPopupMenu(QPoint point, uint32 *&lut);
  void showDiffusionToolbox();
  bool loadExtractionSettings(std::string ifname);
  bool saveExtractionSettings(std::string ofname);
protected:
  bool popoutSurfaceView;
  int activePort;
  std::vector<QAction *> recentFileActions;
  virtual void resizeEvent ( QResizeEvent * event );
  virtual void changeEvent(QEvent *e);
  virtual void keyPressEvent ( QKeyEvent * event );
  virtual void keyReleaseEvent ( QKeyEvent * event );
private:
  Ui::BrainSuiteWindow *ui;
  QDebugStream *qDebugStream;
  QDebugStream *qErrorStream;
  std::vector<QDockWidget *> dockWidgets;
public:
  DSGLWidget *dsglWidget;
  WelcomeSplashPage *welcomeSplashPage;
  void dropEvent(QDropEvent *event);
  void dragEnterEvent(QDragEnterEvent *event);
public:
  std::vector<ImageFrame *> ports;
  bool disableRecentFileList;
  uint32 *imageLUT;
  uint32 *imageOverlay1LUT;
  uint32 *imageOverlay2LUT;
private slots:
  void openRecentFile();
  void on_actionImage_Volume_triggered();
  void on_action_Surface_triggered();
  void on_actionSurface_DisplayProperties_triggered();
  void on_actionExit_triggered();
  void on_action_Mask_Volume_triggered();
  void on_action_Label_Volume_triggered();
  void on_action_Image_Display_Properties_triggered();
  void on_action_Visit_the_BrainSuite_website_triggered();
  void on_action_About_BrainSuiteQT_triggered();
  void on_action_Visit_the_BrainSuite_Forum_triggered();
  void on_action_Visit_the_BrainSuite_Download_Page_triggered();
  void on_action_Overlay2_Volume_triggered();
  void on_action_Continuous_sync_with_image_view_toggled(bool arg1);
  void on_action_HARDI_SHC_Data_triggered();
  void on_action_Fiber_Tract_Set_triggered();
  void on_actionFiber_Tract_Tool_triggered();
  void on_actionLabel_Description_File_triggered();
  void on_action_BST_File_triggered();
  void on_action_BSE_triggered();
  void on_action_SaveMaskVolume_triggered();
  void on_action_Connectivity_Viewer_triggered();
  void on_actionTissue_Classification_PVC_triggered();
  void on_actionNonuniformity_Correction_BFC_triggered();
  void on_action_Surface_View_Only_triggered();
  void on_action_Orthogonal_Views_Surface_View_triggered();
  void on_action_Cerebrum_Extraction_triggered();
  void on_action_Inner_Cortex_Boundary_triggered();
  void on_action_Scrub_Mask_triggered();
  void on_action_Topological_Correction_triggered();
  void on_action_Wisp_Filter_triggered();
  void on_action_Inner_Cortical_Surface_triggered();
  void on_action_Pial_Surface_triggered();
  void on_action_Hemisphere_Splitting_triggered();
  void on_action_Skull_and_Scalp_triggered();
  void on_actionZoom_Best_Fit_triggered();
  void on_action_Outline_triggered();
  void on_action_Stencil_triggered();
  void on_action_Mask_Tool_triggered();
  void on_action_Painter_Tool_triggered();
  void on_action_Cortical_Extraction_Sequence_triggered();
  void on_action_Save_Primary_Volume_triggered();
  void on_action_Save_Overlay1_Volume_triggered();
  void on_action_Save_Overlay2_Volume_triggered();
  void on_action_Save_Label_Volume_triggered();
  void on_actionShow_Overlay_1_triggered();
  void on_actionShow_Overlay_2_triggered();
  void on_action_Open_Overlay_Volume_triggered();
  void on_action_OpenCurveset_triggered();
  void on_action_Reset_Surface_View_triggered();
  void on_action_Curve_Tool_triggered();
  void on_actionLoad_Custom_Cerebrum_Mask_triggered();
  void on_action_Undo_mask_edit_triggered();
  void on_actionOpen_connectivity_matrix_triggered();
  void on_action_Popout_Surface_View_triggered();
  void on_actionSurface_Volume_Registration_triggered();
  void on_action_Reinstall_BrainSuite_Atlas_Files_triggered();
  void on_action_HARDI_Tool_triggered();
  void on_action_Diffusion_Display_Properties_triggered();
  void on_actionODF_Eig_triggered();
  void on_actionLoad_ODF_Maxima_triggered();
  void on_actionSave_Full_Set_triggered();
  void on_actionSave_Subset_triggered();
  void on_actionSave_Surface_View_Screenshow_triggered();
  void on_actionSave_Custom_Sized_Rendering_triggered();
  void on_actionSelect_SVReg_Directory_triggered();
  void on_actionSave_Axial_Image_Screenshot_triggered();
  void on_actionSave_Coronal_Image_Screenshot_triggered();
  void on_actionSave_Sagittal_Image_Screenshot_triggered();
  void on_actionDisable_Mask_Undo_System_triggered();
  void on_actionUse_Native_File_Dialogs_triggered();
  void on_actionAllow_BrainSuite_to_Check_for_Updates_triggered();
  void on_actionSingle_Frame_triggered();
  void on_actionAxial_View_triggered();
  void on_actionSagittal_View_triggered();
  void on_actionCoronal_View_triggered();
  void on_actionAutozoom_on_Resize_triggered();
  void on_actionThree_color_mode_triggered();
  void on_actionSave_Surfaceview_Screenshot_triggered();
  void on_actionSave_Connectivity_Matrix_triggered();
  void on_actionVolume_Info_triggered();
  void on_actionAdd_Custom_SVReg_Atlas_Directory_triggered();
  void on_action_Show_Current_Display_Settings_triggered();
  void on_actionShow_Labels_as_Outlines_triggered();
  void on_actionSave_Extraction_Settings_triggered();
  void on_actionExtraction_Settings_triggered();
  void on_actionDisable_Autoscaling_toggled(bool arg1);
  void on_action_Blend_triggered();
  void on_action_Mask_Only_triggered();
  void on_actionColormap_LUT_triggered();
};

#endif // BrainSuiteWindow_H
