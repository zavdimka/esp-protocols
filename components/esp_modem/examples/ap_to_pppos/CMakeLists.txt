# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

set(EXTRA_COMPONENT_DIRS "../..")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(ap-to-pppos)

idf_build_set_property(COMPILE_OPTIONS "-Wfatal-errors" APPEND)
idf_build_set_property(COMPILE_OPTIONS "-w" APPEND)
idf_build_set_property(CXX_COMPILE_OPTIONS "-std=gnu++17" APPEND)
idf_build_set_property(C_COMPILE_OPTIONS "-std=gnu17" APPEND)