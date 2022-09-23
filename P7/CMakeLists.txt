# CMakeList.txt : CMake project for P7, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("P7")

# Add source to this project's executable.
add_executable (P7 "P7.cpp" "P7.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET P7 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
