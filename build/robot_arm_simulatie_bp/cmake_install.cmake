# Install script for directory: /home/agit/Documents/github/bp_simulatie/WoR_lynxmotion_arm_Simulatie/src/robot_arm_simulatie_bp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/agit/Documents/github/bp_simulatie/WoR_lynxmotion_arm_Simulatie/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/agit/Documents/github/bp_simulatie/WoR_lynxmotion_arm_Simulatie/build/robot_arm_simulatie_bp/catkin_generated/installspace/robot_arm_simulatie_bp.pc")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robot_arm_simulatie_bp/cmake" TYPE FILE FILES
    "/home/agit/Documents/github/bp_simulatie/WoR_lynxmotion_arm_Simulatie/build/robot_arm_simulatie_bp/catkin_generated/installspace/robot_arm_simulatie_bpConfig.cmake"
    "/home/agit/Documents/github/bp_simulatie/WoR_lynxmotion_arm_Simulatie/build/robot_arm_simulatie_bp/catkin_generated/installspace/robot_arm_simulatie_bpConfig-version.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/robot_arm_simulatie_bp" TYPE FILE FILES "/home/agit/Documents/github/bp_simulatie/WoR_lynxmotion_arm_Simulatie/src/robot_arm_simulatie_bp/package.xml")
endif()

