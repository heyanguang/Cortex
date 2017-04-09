cmake_minimum_required(VERSION 2.8.11)
if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW) # CMake 3.0
endif()
if(POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW) # CMake 3.0
endif()
if(POLICY CMP0053)
  cmake_policy(SET CMP0053 NEW) # CMake 3.1
endif()

project(Cortex)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(OpenGL REQUIRED)
message(STATUS "OPENGL_LIBRARIES=" ${OPENGL_LIBRARIES})

# VTK is required
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

if("${VTK_QT_VERSION}" STREQUAL "")
  message(FATAL_ERROR "VTK was not built with Qt")
endif()

# Check ITK Library [Insight ToolKit]
find_package(ITK REQUIRED)
include(${ITK_USE_FILE})

#Check TCLAP Library [Templatized C++ Command Line Parser] (1.2.0)
#find_package(TCLAP 1.2.0 REQUIRED)
#include_directories(${TCLAP_INCLUDE_DIRS})

link_directories("${VTK_DIR}/lib")
message(STATUS "VTK_USE_FILE=" ${VTK_USE_FILE})
message(STATUS "VTK_DEFINITIONS=" ${VTK_DEFINITIONS})
message(STATUS "VTK_INCLUDE_DIRS=" ${VTK_INCLUDE_DIRS})
message(STATUS "VTK_LIBRARIES=" ${VTK_LIBRARIES})
message(STATUS "link_directories: " "${VTK_DIR}/lib")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR=" "${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR=" "${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "vtk-${VTK_VERSION} ${VTK_MAJOR_VERSION} ${VTK_MINOR_VERSION}")

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
## Instruct CMake to run moc automatically when needed.
#set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5OpenGL)
find_package(Qt5Network)

# Use the compile definitions defined in the Qt 5 Widgets module
add_definitions(${Qt5Widgets_DEFINITIONS})

# Add compiler flags for building executables (-fPIE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

# Qt and project source code
file(GLOB Project_source_files
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
)
file(GLOB Project_header_files
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

file(GLOB ContourSurface_source_files
	${CMAKE_CURRENT_SOURCE_DIR}/plugins/ContourSurface/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/plugins/ContourSurface/*.cxx
)
file(GLOB ContourSurface_header_files
	${CMAKE_CURRENT_SOURCE_DIR}/plugins/ContourSurface/*.h
)

file(GLOB Project_ui_files
  ${CMAKE_CURRENT_SOURCE_DIR}/*.ui
)

file(GLOB Sources_bs_cortex
	${CMAKE_CURRENT_SOURCE_DIR}/sources_bs_cortex/*.cpp
)

file(GLOB Headers_bs_cortex
	${CMAKE_CURRENT_SOURCE_DIR}/headers_bs_cortex/*.h
)

file(GLOB Ui_bs_cortex
  ${CMAKE_CURRENT_SOURCE_DIR}/ui_bs_cortex/*.ui
)

QT5_WRAP_CPP(Project_moc_source_files mainwindow.h)
QT5_WRAP_CPP(Moc_headers_bs_cortex ${Headers_bs_cortex})
qt5_add_resources(QRC resources.qrc)

QT5_WRAP_UI(Project_ui_header_files ${Project_ui_files})
QT5_WRAP_UI(Ui_headers_bs_cortex ${Ui_bs_cortex})

source_group(ui FILES ${Project_ui_files} ${Project_ui_header_files})
source_group(ui_bs_cortex FILES ${Ui_bs_cortex})
source_group(ui_headers_bs_cortex FILES ${Ui_headers_bs_cortex})
source_group(moc FILES ${Project_moc_source_files})
source_group(moc_headers_bs_cortex FILES ${Moc_headers_bs_cortex})

# Add the include directories for VTK and Qt 5 Widgets module to the compile lines.
include_directories(${CMAKE_CURRENT_SOURCE_DIR}
					${CMAKE_CURRENT_BINARY_DIR}
					${Qt5Widgets_INCLUDE_DIRS}
					${Qt5Network_INCLUDE_DIRS}
	                ${VTK_INCLUDE_DIRS}
					"${VTK_DIR}/include/vtk-${VTK_MAJOR_VERSION}.${VTK_MINOR_VERSION}"
					${CMAKE_CURRENT_SOURCE_DIR}/plugins/ContourSurface
					${CMAKE_CURRENT_SOURCE_DIR}/headers_bs_cortex
					${CMAKE_CURRENT_SOURCE_DIR}/headers_bs_cortex/include
					${CMAKE_CURRENT_SOURCE_DIR}/headers_bs_cortex/3rdParty/include
					${CMAKE_CURRENT_SOURCE_DIR}/headers_bs_cortex/surflib
					${CMAKE_CURRENT_SOURCE_DIR}/headers_bs_cortex/diffusion/include
					${CMAKE_CURRENT_SOURCE_DIR}/headers_bs_cortex/corticalextraction/include
					${CMAKE_CURRENT_SOURCE_DIR}/headers_bs_cortex/corticalextraction/include/bfc
					${CMAKE_CURRENT_SOURCE_DIR}/headers_bs_cortex/corticalextraction/include/bse
					${CMAKE_CURRENT_SOURCE_DIR}/headers_bs_cortex/corticalextraction/include/pvc
					${CMAKE_CURRENT_SOURCE_DIR}/headers_bs_cortex/corticalextraction/include/tca
)

# nifti2dicom_core target
# add_library(nifti2dicom_core STATIC ${Nifti_core_source_files} ${Nifti_core_header_files})
# target_link_libraries(nifti2dicom_core LINK_PRIVATE ${ITK_LIBRARIES})

add_executable(${PROJECT_NAME}
               ${Project_source_files}
			   ${Project_header_files}
			   ${Project_ui_header_files}
			   ${Project_moc_source_files}
			   ${ContourSurface_source_files}
			   ${ContourSurface_header_files}
			   ${Sources_bs_cortex}
			   ${Headers_bs_cortex}
			   ${Ui_headers_bs_cortex}
			   ${Moc_headers_bs_cortex}
	           ${QRC}
)

# Use the Widgets module from Qt 5.
target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::OpenGL ${VTK_LIBRARIES} ${ITK_LIBRARIES}
                      ${OPENGL_LIBRARIES})

if(WIN32) # Check if we are on Windows
#	add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
#		COMMAND xcopy /d /f /y "\"${Qt5Widgets_DIR}/../../../bin/*.dll\"" "\"$<TARGET_FILE_DIR:${PROJECT_NAME}>\""
#	)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND xcopy /d /f /y "\"${VTK_DIR}/bin/$<CONFIGURATION>/*.dll\"" "\"$<TARGET_FILE_DIR:${PROJECT_NAME}>\""
	)
endif()
