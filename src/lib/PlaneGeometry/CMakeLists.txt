add_library(PlaneGeometry STATIC
    PlaneOperations.cpp
    PlaneOperations.h
)

# Указываем, что наша библиотека для своей работы использует Qt Core (для QPointF).
# PUBLIC означает, что любой, кто подключит PlaneGeometry,
# автоматически получит и доступ к Qt::Core.
target_link_libraries(PlaneGeometry PUBLIC Qt${QT_VERSION_MAJOR}::Core)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Gui REQUIRED)

# Делаем так, чтобы другие части проекта (например, Vizualization)
# могли найти заголовочные файлы нашей библиотеки.
# Мы добавляем в пути поиска директорию `.../src/lib/PlaneGeometry/include`.
# Компилятор, получив этот путь, сможет найти в нем подпапку `PlaneGeometry`
# и далее файл `PlaneOperations.h`.

# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

target_include_directories(PlaneGeometry
    PUBLIC
        # ${CMAKE_CURRENT_SOURCE_DIR} - это текущая папка, т.е. src/lib/PlaneGeometry
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
