cmake_minimum_required(VERSION 3.14)

set(PROJECT "DeviceClientExample")

project("${PROJECT}_Project" VERSION 1.2.3 LANGUAGES CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD          17) #20)# hat er irgendwie noch nicht
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

#check which of these is necessary to avoid errors
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

#Options
option(ENABLE_TESTING   "Enable a Unit Testing build."  ON)
option(ENABLE_COVERAGE  "Enable Code Coverage build."   OFF)
option(ENABLE_BENCHMARK "Enable Code Benchmark build."   OFF)

# Cmake modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
#build target to build docu is: make MyCppRestClient_docs 
include(Documentation)
if (ENABLE_TESTING OR ENABLE_COVERAGE)
    include(CTest)
endif()
if (ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        include(CodeCoverage)
    else()
        message("Coverage only for GNU|Clang")
        set(ENABLE_COVERAGE OFF)
    endif()
endif()


# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON) #required for resources file




# Project/Library Names
set(LIBRARY_NAME    "${PROJECT}_DeviceClientLib")
set(MAIN            "${PROJECT}_Executable")
set(TEST_MAIN       "${PROJECT}_unit_tests")
set(COVERAGE_MAIN   "${PROJECT}_coverage")
set(BENCHMARK_MAIN  "${PROJECT}_benchmarks")

#find_package(Boost COMPONENTS system filesystem program_options log regex serialization REQUIRED)
#include_directories(${Boost_INCLUDE_DIR})
#link_directories(${Boost_LIBRARY_DIR})
add_definitions (-DBOOST_ALL_DYN_LINK)

# Find the QtWidgets library
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# boost beast ssl stuff needs openssl
find_package(OpenSSL REQUIRED)

# Add conan libraries
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Add external 3rd party libraries
add_subdirectory("${PROJECT_SOURCE_DIR}/external/")

# Add first-party libraries
add_subdirectory("${PROJECT_SOURCE_DIR}/src/")

# Add executables
add_subdirectory("${PROJECT_SOURCE_DIR}/app/")

if (ENABLE_TESTING OR ENABLE_COVERAGE)
enable_testing() #activates CTest packet
    add_subdirectory("${PROJECT_SOURCE_DIR}/tests/")
endif()


# Add benchmarks
if(ENABLE_BENCHMARK)
    add_subdirectory("${PROJECT_SOURCE_DIR}/benchmarks/")
endif()
