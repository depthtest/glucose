cmake_minimum_required(VERSION 3.12)

project(glucose)

set(main_simp "simp/Main.cc")
set(main_parallel "parallel/Main.cc")

# Basic Library
file(GLOB lib_srcs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} mtl/*.cc core/*.cc simp/*.cc utils/*.cc)
list(REMOVE_ITEM lib_srcs ${main_simp} ${main_parallel})

# Parallel Library
#file(GLOB lib_parallel_srcs RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} parallel/*.cc)
#list(REMOVE_ITEM lib_parallel_srcs ${main_simp} ${main_parallel})

add_compile_definitions(INCREMENTAL NDEBUG)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
)

# base library
add_library(glucose STATIC ${lib_srcs})

# parallel library
#add_library(glucosep STATIC ${lib_srcs} ${lib_parallel_srcs})

# testing the libraries
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    if(BUILD_TESTING)
        add_subdirectory(tests)
    endif()
endif()
