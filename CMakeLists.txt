cmake_minimum_required(VERSION 4.4.0)

project(27Launcher LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(CPR_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(CPR_USE_SYSTEM_CURL ON CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(
    cpr
    GIT_REPOSITORY https://github.com/libcpr/cpr
    GIT_TAG        1.14.2
)
FetchContent_MakeAvailable(cpr)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

find_package(CURL REQUIRED)

find_package(nlohmann_json REQUIRED)

qt_standard_project_setup()

add_subdirectory(11Zip)

add_executable(27Launcher #WIN32 - include this before deploying
    resources.rc
    src/main.cpp
    src/downloadLatestZip.cpp
    src/getAppDataPath.cpp
)

target_include_directories(27Launcher PRIVATE
    
)

target_link_libraries(27Launcher PRIVATE
    Qt6::Core
    Qt6::Widgets
    CURL::libcurl
    cpr::cpr
    elzip
)

if(WIN32)
    target_link_options(27Launcher PRIVATE 
        "$<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>"
        "$<$<CONFIG:Release>:/ENTRY:mainCRTStartup>"
    )
endif()