#
# "gbdsm" Makefile 
#
# Copyright Tamer Aly 2019
#

CXXFLAGS := --std=c++14 -Wall -Wextra -Wpedantic -Werror

SOURCES := main.cc ops.cc dasm.cc
OBJECTS := $(SOURCES:.cc=.o)

PROGRAM := gbdsm
INSTALL_DIR := /opt/bin

.PHONY : all clean debug release install uninstall

release : CXXFLAGS += -DNDEBUG -O3
release : all

debug : CXXFLAGS += -g
debug : all

install : all
	mkdir -p $(INSTALL_DIR) && cp -f $(PROGRAM) $(INSTALL_DIR)

uninstall : all
	rm -f $(INSTALL_DIR)/$(PROGRAM)

all : $(OBJECTS) 
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(OBJECTS) 

$(OBJECTS) : $(SOURCES) 
	$(CXX) $(CXXFLAGS) -c $(SOURCES) 

clean :
	rm -f $(OBJECTS) $(PROGRAM)
