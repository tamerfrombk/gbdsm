#
# "gbdsm" Makefile 
#
# Copyright Tamer Aly 2019
#

CXX := g++
CXXFLAGS := --std=c++14 -Wall -Wextra -Wpedantic -Werror
SOURCES := main.cc ops.cc dasm.cc
OBJECTS := $(SOURCES:.cc=.o)
PROGRAM := gbdsm

.PHONY : all clean

release : CXXFLAGS += -DNDEBUG -O3
release : all

debug : CXXFLAGS += -g
debug : all

all : $(OBJECTS) 
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(OBJECTS) 

$(OBJECTS) : $(SOURCES) 
	$(CXX) $(CXXFLAGS) -c $(SOURCES) 

clean :
	rm -f $(OBJECTS) $(PROGRAM)
