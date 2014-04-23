TESTS = \
  dialog_cleanup_test \
  library_shutdown_test

SCRIPTS = \
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
CPPFLAGS = -I$(PREFIX)/include/yui
LDFLAGS = -L$(LIBDIR)
LOADLIBES= -lyui

TARGETS = ncurses qt gtk

all:   $(TESTS)
check: all
	LD_LIBRARY_PATH=$(LIBDIR) TARGETS="$(TARGETS)" ./test_all $(TESTS)

clean:
	rm -f $(TESTS) *.o *.log

PACKAGE = libyui-test
VERSION = $(shell sed -n 's/Version: *//;T;p;q' package/*.spec)
SOURCES = $(patsubst %,%.cc,$(TESTS))

dist:
	-rm package/*.tar.bz2
	VERSION=$(VERSION); tar cvj \
          --transform "s,^,$(PACKAGE)-$$VERSION/," \
          -f package/$(PACKAGE)-$$VERSION.tar.bz2 \
          $(SOURCES) $(SCRIPTS) Makefile

.PHONY: all check clean dist
