#
# "gbdsm" Makefile
#
# Copyright Tamer Aly 2019
#

VERSION := "1.1.0"

CXXFLAGS := --std=c++14 -Wall -Wextra -Wpedantic -Werror -DGBDSM_VERSION=\"$(VERSION)\"

SOURCES := $(wildcard *.cc)
OBJECTS := $(SOURCES:.cc=.o)
HEADERS := $(wildcard *.h)

PROGRAM := gbdsm
INSTALL_DIR := /opt/bin

MAN_PAGE = $(PROGRAM).1.gz
MAN_PAGE_DIR = /opt/man
MAN_PAGE_LINK = /usr/share/man/man1

.PHONY : clean debug release install uninstall

release : CXXFLAGS += -DNDEBUG -O3
release : $(PROGRAM)

debug : CXXFLAGS += -g
debug : $(PROGRAM)

$(PROGRAM) : $(OBJECTS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(OBJECTS)

install : $(PROGRAM)
	mkdir -p $(INSTALL_DIR)
	cp -f $(PROGRAM) $(INSTALL_DIR)
	mkdir -p $(MAN_PAGE_DIR)
	cp -f $(MAN_PAGE) $(MAN_PAGE_DIR)
	ln -sf $(MAN_PAGE_DIR)/$(MAN_PAGE) $(MAN_PAGE_LINK)/$(MAN_PAGE)

uninstall :
	rm -f $(INSTALL_DIR)/$(PROGRAM)
	rm -f $(MAN_PAGE_LINK)/$(MAN_PAGE)
	rm -f $(MAN_PAGE_DIR)/$(MAN_PAGE)

clean :
	rm -f $(OBJECTS) $(PROGRAM)
