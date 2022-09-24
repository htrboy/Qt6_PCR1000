cmake_minimum_required(VERSION 3.14)

project(qt6_pcr1000 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Widgets Gui Core5Compat REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Widgets Gui Core5Compat REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        
        aliasdisplay.cpp
        aliasdisplay.h
        bargraph.cpp
        bargraph.h
        bmdata.cpp
        bmdata.h
        bmtree.cpp
        bmtree.h
        dial.cpp
        dial.h
        filterctrl.cpp
        filterctrl.h
        filterdisplay.cpp
        filterdisplay.h
        freqdisplay.cpp
        freqdisplay.h
        keypad.cpp
        keypad.h
        meter.cpp
        meter.h
        modectrl.cpp
        modectrl.h
        modedisplay.cpp
        modedisplay.h
        monitor.cpp
        monitor.h
        pcrio.cpp
        pcrio.h
        pcrproto.h
        pcrproxy.cpp
        pcrproxy.h
        qtpcr.cpp
        qtpcr.h
        scan.cpp
        scan.h
        scandialog.cpp
        scandialog.h
        squctrl.cpp
        squctrl.h
        tips.h
        volctrl.cpp
        volctrl.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qt6_pcr1000
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET qt6_pcr1000 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(qt6_pcr1000 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(qt6_pcr1000
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(qt6_pcr1000
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(qt6_pcr1000
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui
                Qt${QT_VERSION_MAJOR}::Core5Compat)

set_target_properties(qt6_pcr1000 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

#add_subdirectory(icons)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(qt6_pcr1000)
    qt_finalize_executable(qt6_pcr1000)
endif()

