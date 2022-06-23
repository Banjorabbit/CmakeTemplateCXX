cmake_minimum_required(VERSION 3.10)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE Release)

project(Tutorial_release)

# ---- Include guards ----
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(FATAL_ERROR "Builds are not allowed in this folder. Please use the directory build/release.")
endif()

# ---- Dependencies ----
set(ENV{CPM_SOURCE_CACHE} ${PROJECT_SOURCE_DIR}/../../lib)

include(../../cmake/CPM.cmake)

# add Tutorial library
CPMAddPackage(
  NAME Tutorial 
  SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/../.."
  OPTIONS "ENABLE_TESTS 0"
)
list(APPEND EXTRA_LIBS_PRIVATE Tutorial::Tutorial) # link to library

# add format library
CPMAddPackage(
  NAME fmt
  GIT_TAG 8.1.1
  GITHUB_REPOSITORY fmtlib/fmt
)
list(APPEND EXTRA_LIBS_PRIVATE fmt::fmt) # link to library


# ---- Create standalone executable ----


add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main_release.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${EXTRA_LIBS_PRIVATE}) # add links to libraries
