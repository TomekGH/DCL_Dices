# Install script for directory: /home/tpokorsk/Pulpit/DCL/DCL_Dices/src/Components

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/home/tpokorsk/Pulpit/DCL/DCL_Dices/dist")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/tpokorsk/Pulpit/DCL/DCL_Dices/build/src/Components/DcTest/cmake_install.cmake")
  INCLUDE("/home/tpokorsk/Pulpit/DCL/DCL_Dices/build/src/Components/DcImageProcessing/cmake_install.cmake")
  INCLUDE("/home/tpokorsk/Pulpit/DCL/DCL_Dices/build/src/Components/DcFeatureExtraction/cmake_install.cmake")
  INCLUDE("/home/tpokorsk/Pulpit/DCL/DCL_Dices/build/src/Components/DcObjectRecognition/cmake_install.cmake")
  INCLUDE("/home/tpokorsk/Pulpit/DCL/DCL_Dices/build/src/Components/CvFindContours/cmake_install.cmake")
  INCLUDE("/home/tpokorsk/Pulpit/DCL/DCL_Dices/build/src/Components/DcRecognition/cmake_install.cmake")
  INCLUDE("/home/tpokorsk/Pulpit/DCL/DCL_Dices/build/src/Components/DcPresentation/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

