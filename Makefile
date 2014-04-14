TESTS = \
  test_library_shutdown

CXXFLAGS = -g3 -Wall

# libyui:
CPPFLAGS = -I/usr/include/yui
LDFLAGS  = -lyui

check: $(TESTS)
	set -x; for i in $(TESTS); do ./$$i; done

clean:
	rm -f $(TESTS) *.o

PACKAGE = libyui-test
VERSION = 1.0.0
SOURCES = $(patsubst %,%.cc,$(TESTS))

dist:
	tar cvj --transform 's,^,$(PACKAGE)-$(VERSION)/,' -f package/$(PACKAGE)-$(VERSION).tar.bz2 $(SOURCES) Makefile
