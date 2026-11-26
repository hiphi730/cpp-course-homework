# Called at the submission root (framework) and each stage root (stage).
# Keep paths relative so MinGW Make does not need to parse Chinese directory names.
CXX = g++
OUT = build-mingw-course
GTEST = third_party/googletest/googletest
FLAGS = -std=c++17
SOURCES = $(sort $(wildcard src/*.cpp src/*/*.cpp tests/*.cpp))

.PHONY: framework stage
framework:
	$(CXX) $(FLAGS) -I$(GTEST) -I$(GTEST)/include -c $(GTEST)/src/gtest-all.cc -o $(OUT)/gtest.o
	$(CXX) $(FLAGS) -I$(GTEST)/include -c $(GTEST)/src/gtest_main.cc -o $(OUT)/gtest_main.o

stage:
	$(CXX) $(FLAGS) -Wall -Wextra -Werror -Wpedantic -Isrc -Iinclude -I../$(GTEST)/include $(SOURCES) ../$(OUT)/gtest_main.o ../$(OUT)/gtest.o -o $(OUT)/tests.exe
	./$(OUT)/tests.exe --gtest_brief=1
