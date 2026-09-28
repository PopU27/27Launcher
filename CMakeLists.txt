cmake_minimum_required(VERSION 4.4.0)

project(27Launcher LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui OpenGLWidgets)

find_package(CURL REQUIRED)

qt_standard_project_setup()

add_executable(27Launcher src/main.cpp)

target_link_libraries(27Launcher PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Qt6::OpenGLWidgets
    CURL::libcurl
)

if(WIN32)
    target_link_options(27Launcher PRIVATE 
        "$<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>"
        "$<$<CONFIG:Release>:/ENTRY:mainCRTStartup>"
    )
endif()