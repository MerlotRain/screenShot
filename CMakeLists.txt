cmake_minimum_required(VERSION 3.0..3.20)
project(screenShot)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_FILE drawingoperationstack.cpp
    main.cpp
    qtscreenshot.cpp
    qtscreenshoteditarea.cpp
    qtscreenshottoolbar.cpp
    widget.cpp)
    
set(HEADER_FILE drawingoperationstack.h
    qtscreenshot.h
    qtscreenshoteditarea.h
    qtscreenshottoolbar.h
    widget.h)

find_package(Qt5 COMPONENTS
    Core
    Gui
    Widgets
    REQUIRED)

add_executable(${PROJECT_NAME} WIN32 ${SRC_FILE} ${HEADER_FILE})    

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    )