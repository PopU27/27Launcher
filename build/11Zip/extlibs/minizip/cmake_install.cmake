# Install script for directory: E:/rodgo/CodeProjects/27Launcher/11Zip/extlibs/minizip

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/27Launcher")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "E:/msys64/ucrt64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "E:/rodgo/CodeProjects/27Launcher/build/11Zip/extlibs/minizip/libminizip.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip/minizip.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip/minizip.cmake"
         "E:/rodgo/CodeProjects/27Launcher/build/11Zip/extlibs/minizip/CMakeFiles/Export/4fe77da0f4d2c94dd906efce3aa1c0aa/minizip.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip/minizip-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip/minizip.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip" TYPE FILE FILES "E:/rodgo/CodeProjects/27Launcher/build/11Zip/extlibs/minizip/CMakeFiles/Export/4fe77da0f4d2c94dd906efce3aa1c0aa/minizip.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip" TYPE FILE FILES "E:/rodgo/CodeProjects/27Launcher/build/11Zip/extlibs/minizip/CMakeFiles/Export/4fe77da0f4d2c94dd906efce3aa1c0aa/minizip-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/minizip" TYPE FILE FILES
    "E:/rodgo/CodeProjects/27Launcher/build/11Zip/extlibs/minizip/minizip-config-version.cmake"
    "E:/rodgo/CodeProjects/27Launcher/build/11Zip/extlibs/minizip/minizip-config.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "E:/rodgo/CodeProjects/27Launcher/11Zip/extlibs/minizip/mz.h"
    "E:/rodgo/CodeProjects/27Launcher/11Zip/extlibs/minizip/mz_os.h"
    "E:/rodgo/CodeProjects/27Launcher/11Zip/extlibs/minizip/mz_crypt.h"
    "E:/rodgo/CodeProjects/27Launcher/11Zip/extlibs/minizip/mz_strm.h"
    "E:/rodgo/CodeProjects/27Launcher/11Zip/extlibs/minizip/mz_strm_buf.h"
    "E:/rodgo/CodeProjects/27Launcher/11Zip/extlibs/minizip/mz_strm_mem.h"
    "E:/rodgo/CodeProjects/27Launcher/11Zip/extlibs/minizip/mz_strm_split.h"
    "E:/rodgo/CodeProjects/27Launcher/11Zip/extlibs/minizip/mz_strm_os.h"
    "E:/rodgo/CodeProjects/27Launcher/11Zip/extlibs/minizip/mz_zip.h"
    "E:/rodgo/CodeProjects/27Launcher/11Zip/extlibs/minizip/mz_zip_rw.h"
    "E:/rodgo/CodeProjects/27Launcher/11Zip/extlibs/minizip/mz_strm_zlib.h"
    "E:/rodgo/CodeProjects/27Launcher/11Zip/extlibs/minizip/mz_strm_pkcrypt.h"
    "E:/rodgo/CodeProjects/27Launcher/11Zip/extlibs/minizip/mz_strm_wzaes.h"
    "E:/rodgo/CodeProjects/27Launcher/11Zip/extlibs/minizip/mz_compat.h"
    "E:/rodgo/CodeProjects/27Launcher/build/11Zip/extlibs/minizip/zip.h"
    "E:/rodgo/CodeProjects/27Launcher/build/11Zip/extlibs/minizip/unzip.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "E:/rodgo/CodeProjects/27Launcher/build/11Zip/extlibs/minizip/minizip.pc")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "E:/rodgo/CodeProjects/27Launcher/build/11Zip/extlibs/minizip/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
