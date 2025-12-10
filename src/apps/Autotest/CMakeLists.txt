add_executable(Autotest
  main.cpp
  Autotest.cpp
  Autotest.h
)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../../lib)
link_directories( ${CMAKE_SOURCE_DIR}/src/lib )

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Test REQUIRED)

target_link_libraries(Autotest PRIVATE
    PlaneGeometry
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Test
)

