cmake_minimum_required(VERSION 3.7)
project(01_allocator)

set(CMAKE_CXX_STANDARD 11)

add_custom_target(01_allocator COMMAND make -C ${01_allocator_SOURCE_DIR}
        CLION_EXE_DIR=${PROJECT_BINARY_DIR})

#set(SOURCE_FILES
#        allocator.cpp
#        allocator.h
#        allocator_error.cpp
#        allocator_error.h
#        allocator_pointer.cpp
#        allocator_pointer.h
#        allocator_test.cpp)
#
#add_executable(01_allocator ${SOURCE_FILES})