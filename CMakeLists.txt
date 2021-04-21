cmake_minimum_required(VERSION 3.13)

project(c-data-structures C)


include(CheckTypeSize)
check_type_size(ssize_t HAVE_SSIZE_T)

option(CDS_RUN_TESTS "Option to run tests" OFF)

add_library(cds INTERFACE)
target_include_directories(
    cds 
    INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)



if(CDS_RUN_TESTS)
   add_subdirectory(tests)
endif()

