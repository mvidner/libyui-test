TESTS = \
  test_library_shutdown
SCRIPTS = \
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
	set -x; \
	for i in $(TESTS); do \
	  LD_LIBRARY_PATH=$(LIBDIR) ./virtual_x_server ./$$i; \
	done

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
