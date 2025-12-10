add_executable(Viewer2d
  main.cpp
  mainwindow.h
  mainwindow.cpp
  mainwindow.ui
  drawwidget.cpp
  drawwidget.h
  longdouble.h longdouble.cpp
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../../lib)
link_directories( ${CMAKE_SOURCE_DIR}/src/lib )

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Gui REQUIRED)

target_link_libraries(Viewer2d PRIVATE
    PlaneGeometry
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
)

