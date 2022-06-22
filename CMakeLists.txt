cmake_minimum_required(VERSION 3.14)

set(CMAKE_VERBOSE_MAKEFILE ON)
option(ENABLE_TESTS 0)
if(ENABLE_TESTS)
  set(DOCTEST_CONFIG_DISABLE 0)
else()
  set(DOCTEST_CONFIG_DISABLE 1)
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# set project name and version
project(Tutorial VERSION 0.0.1)

# ---- Include guards ----
if((PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR) OR (${PROJECT_SOURCE_DIR}/build STREQUAL PROJECT_BINARY_DIR))
  message(FATAL_ERROR "builds are not allowed in this folder. Please use one of the following: build/release, build/debug, build/test_release, build/test_debug.")
endif()

# ---- Add dependencies via CPM ----

#set folder for 3rd party libraries
set(ENV{CPM_SOURCE_CACHE} ${PROJECT_SOURCE_DIR}/lib)
include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.8.0")

# add nlohmann json library
CPMAddPackage(
  NAME nlohmann_json
  VERSION 3.10.5
  GITHUB_REPOSITORY ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  OPTIONS "JSON_BuildTests OFF" "JSON_Install ON"
)
list(APPEND EXTRA_LIBS nlohmann_json::nlohmann_json) # link to library

# add doctest library
CPMAddPackage(
  NAME doctest
  VERSION 2.4.9
  GITHUB_REPOSITORY doctest/doctest
)
list(APPEND EXTRA_LIBS doctest::doctest) # link to library

# add Eigen library
CPMAddPackage(
	NAME Eigen
    GITLAB_REPOSITORY libeigen/eigen
    GIT_TAG 3.4
	DOWNLOAD_ONLY YES
)
add_library(Eigen INTERFACE IMPORTED)
target_include_directories(Eigen INTERFACE ${Eigen_SOURCE_DIR})
list(APPEND EXTRA_LIBS Eigen) # link to library

# add matplotlib and dependencies (remember to install python3, numpy and matplotlib)
CPMAddPackage(
	NAME matplotlib_cpp 
	URL https://github.com/lava/matplotlib-cpp/archive/refs/heads/master.zip 
	DOWNLOAD_ONLY YES
)
add_library(matplotlib_cpp INTERFACE IMPORTED)
target_include_directories(matplotlib_cpp INTERFACE ${matplotlib_cpp_SOURCE_DIR})
list(APPEND EXTRA_LIBS matplotlib_cpp) # link to library

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
target_link_libraries(matplotlib_cpp INTERFACE
  Python3::Python
  Python3::Module
)
find_package(Python3 COMPONENTS NumPy)
if(Python3_NumPy_FOUND)
  target_link_libraries(matplotlib_cpp INTERFACE
    Python3::NumPy
  )
else()
  target_compile_definitions(matplotlib_cpp INTERFACE WITHOUT_NUMPY)
endif()

# ---- Add and configure target ----
# Note that the project is exported as OBJECT to allow doctest to see the tests when linking
add_library(${PROJECT_NAME} OBJECT ${PROJECT_SOURCE_DIR}/inc/Tutorial.h ${PROJECT_SOURCE_DIR}/inc/TutorialConfig.h ${PROJECT_SOURCE_DIR}/src/Tutorial.cpp)





set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 11)
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_CXX_FLAGS "-Wall -Wextra")
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_CXX_FLAGS_DEBUG "-g")
set_target_properties(${PROJECT_NAME} PROPERTIES CMAKE_CXX_FLAGS_RELEASE "-O3")

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Link and include
target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LIBS}) # add links to libraries
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc> $<INSTALL_INTERFACE:inc/${PROJECT_NAME}-${PROJECT_VERSION}> ) #add to search path for #include

# add libraries to include path (not used anymore)
#list(APPEND EXTRA_INCLUDES ${CMAKE_SOURCE_DIR}/lib) #add to search path for #include
#target_include_directories(${PROJECT_NAME} PUBLIC ${EXTRA_INCLUDES}) #add to search path for #include

# create configuration header file (must be after any option going into TutorialConfig.h")
configure_file(${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.h.in ${PROJECT_SOURCE_DIR}/inc/TutorialConfig.h)

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.
packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  NAMESPACE ${PROJECT_NAME}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/inc
  INCLUDE_DESTINATION inc/${PROJECT_NAME}-${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)