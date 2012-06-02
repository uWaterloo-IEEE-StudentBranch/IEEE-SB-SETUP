AM_CPPFLAGS = -DBATS_NO_DEBUG -DDATADIR="$(pkgdatadir)" -I../.. $(DEPS_CFLAGS) -I/usr/include/eigen2
AM_LDFLAGS = ../../libbats.la $(DEPS_LIBS)

noinst_PROGRAMS = helloworld
noinst_HEADERS = HelloWorldAgent/helloworldagent.hh HelloWorldAgent/helloworldagent.ih
helloworld_SOURCES = HelloWorldAgent/init.cc HelloWorldAgent/think.cc helloworld.cc
