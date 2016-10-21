# Copyright (C) 2014 SUSE LLC
# This library is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as
# published by the Free Software Foundation; either version 2.1 of the
# License, or (at your option) version 3.0 of the License. This library
# is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
# License for more details. You should have received a copy of the GNU
# Lesser General Public License along with this library; if not, write
# to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
# Floor, Boston, MA 02110-1301 USA

# This Makefile offers an interface like automake without using it.

TESTS = \
  dialog_cleanup_test \
  library_shutdown_test \
  tree_item_selection_test

TESTS_NCURSES = \
  input_field_test.exp

PROGRAMS = \
  dialog_cleanup_test \
  input_field_test \
  library_shutdown_test \
  tree_item_selection_test

SCRIPTS = \
  input_field_test.exp \
  test_all \
  test_ncurses \
  test_gtk \
  test_qt \
  virtual_terminal \
  virtual_x_server

CXXFLAGS = -g3 -Wall

LIB64 := $(shell rpm --eval %{_lib})
PREFIX = /usr
LIBDIR = $(PREFIX)/$(LIB64)
# libyui:
CPPFLAGS = -I$(PREFIX)/include/yui -std=c++0x
LDFLAGS = -L$(LIBDIR)
LOADLIBES= -lyui

TARGETS = ncurses qt gtk

all:   $(PROGRAMS)
check: all
	LD_LIBRARY_PATH=$(LIBDIR) TARGETS="$(TARGETS)" ./test_all $(TESTS)
ifneq (,$findstring(ncurses,$(TARGETS)))
	LD_LIBRARY_PATH=$(LIBDIR) TARGETS="ncurses"    ./test_all $(TESTS_NCURSES)
endif

clean:
	rm -f $(PROGRAMS) *.o *.log

PACKAGE = libyui-test
VERSION = 1.0.7
SOURCES = $(patsubst %,%.cc,$(PROGRAMS))

dist:
	-rm package/*.tar.bz2
	sed -i -e 's/^\(Version: *\).*/\1$(VERSION)/' package/*.spec
	tar cvj \
          --transform "s,^,$(PACKAGE)-$(VERSION)/," \
          -f package/$(PACKAGE)-$(VERSION).tar.bz2 \
          $(SOURCES) $(SCRIPTS) Makefile

.PHONY: all check clean dist
