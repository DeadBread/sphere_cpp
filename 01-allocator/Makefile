TEST_FILES = ../thirdparty/gtest/gtest-all.cc ../thirdparty/gtest/gtest_main.cc
SRC = allocator.cpp allocator_error.cpp allocator_pointer.cpp allocator_test.cpp
HDR = allocator.h allocator_error.h allocator_pointer.h


all: allocator_test

allocator_test: $(SRC) $(HDR)
	g++ -g -std=c++11 -o allocator_test $(SRC) -I../thirdparty $(TEST_FILES) -lpthread

tests.done: allocator_test
	./allocator_test
	touch tests.done
