#
# "gbdsm" Makefile
#
# Copyright Tamer Aly 2019
#

CXXFLAGS := --std=c++14 -Wall -Wextra -Wpedantic -Werror

SOURCES := $(wildcard *.cc)
OBJECTS := $(SOURCES:.cc=.o)
HEADERS := $(wildcard *.h)

PROGRAM := gbdsm
INSTALL_DIR := /opt/bin

.PHONY : clean debug release install uninstall

release : CXXFLAGS += -DNDEBUG -O3
release : $(PROGRAM)

debug : CXXFLAGS += -g
debug : $(PROGRAM)

$(PROGRAM) : $(OBJECTS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(OBJECTS)

install : $(PROGRAM)
	mkdir -p $(INSTALL_DIR) && cp -f $(PROGRAM) $(INSTALL_DIR)

uninstall : $(PROGRAM)
	rm -f $(INSTALL_DIR)/$(PROGRAM)

clean :
	rm -f $(OBJECTS) $(PROGRAM)
