TESTS = \
  dialog_cleanup_test \
  library_shutdown_test

SCRIPTS = \
  test_all \
  test_ncurses \
  test_gtk \
  test_qt \
  virtual_x_server

CXXFLAGS = -g3 -Wall

PREFIX = /usr
LIBDIR = $(PREFIX)/$(shell rpm --eval %{_lib})
# libyui:
CPPFLAGS = -I$(PREFIX)/include/yui
LDFLAGS := -L$(LIBDIR)
LOADLIBES= -lyui

all:   $(TESTS)
check: all
	LD_LIBRARY_PATH=$(LIBDIR) ./test_all $(TESTS)

clean:
	rm -f $(TESTS) *.o

PACKAGE = libyui-test
VERSION := $(shell sed -n 's/Version: *//;T;p;q' package/*.spec)
SOURCES = $(patsubst %,%.cc,$(TESTS))

dist:
	tar cvj \
          --transform 's,^,$(PACKAGE)-$(VERSION)/,' \
          -f package/$(PACKAGE)-$(VERSION).tar.bz2 \
          $(SOURCES) $(SCRIPTS) Makefile

.PHONY: all check clean dist
