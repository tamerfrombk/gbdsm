#
# "gbdsm" Makefile 
#
# Copyright Tamer Aly 2019
#

CC := g++
CXXFLAGS := --std=c++14 -Wall -Wextra -Wpedantic -Werror
SOURCES := main.cc ops.cc dasm.cc
OBJECTS := $(SOURCES:.cc=.o)
PROGRAM := gbdsm

.PHONY : all clean

all : $(OBJECTS) 
	$(CC) $(CXXFLAGS) -o $(PROGRAM) $(OBJECTS) 

$(OBJECTS) : $(SOURCES) 
	$(CC) $(CXXFLAGS) -c $(SOURCES) 

clean :
	rm -f $(OBJECTS) $(PROGRAM)
