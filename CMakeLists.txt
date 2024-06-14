cmake_minimum_required(VERSION 3.5)

project(tiff_viewer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# Find TIFF and GeoTIFF libraries
# Set CMAKE_PREFIX_PATH to include the path where GeoTIFF is installed


find_package(TIFF REQUIRED)
# find_package(GeoTIFF REQUIRED)

# Укажите пути вручную, если find_package(GeoTIFF REQUIRED) не работает
find_path(GEOTIFF_INCLUDE_DIR geotiff.h
  PATHS /usr/local/include /usr/include /usr/include/geotiff
)

find_library(GEOTIFF_LIBRARY NAMES geotiff
  PATHS /usr/local/lib /usr/lib /usr/lib/x86_64-linux-gnu
)

if(NOT GEOTIFF_INCLUDE_DIR OR NOT GEOTIFF_LIBRARY)
  message(FATAL_ERROR "GeoTIFF not found")
endif()

include_directories(${GEOTIFF_INCLUDE_DIR})


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(tiff_viewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET tiff_viewer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(tiff_viewer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(tiff_viewer
            ${PROJECT_SOURCES}
            header.h
            ConstValues4Tags.h
            form.ui
            tagsviewform.h tagsviewform.cpp tagsviewform.ui


        )
    endif()
endif()

target_link_libraries(tiff_viewer Qt${QT_VERSION_MAJOR}::Widgets ${TIFF_LIBRARY} ${GEOTIFF_LIBRARY})

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.tiff_viewer)
endif()
set_target_properties(tiff_viewer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS tiff_viewer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(tiff_viewer)
endif()
