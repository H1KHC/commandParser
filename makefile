STATIC_LIBRARY = lib/libcommandParserCWrapper.a
INSTALL_PREFIX = /usr/

CXXFLAGS = -fPIC
LINKFLAGS =

HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
STATIC_OBJECTS = $(patsubst %.o, .build/static/%.o, $(OBJECTS))
DYNAMIC_OBJECTS = $(patsubst %.o, .build/dynamic/%.o, $(OBJECTS))

ifdef DEBUG
CXXFLAGS += -g -Wall -Wextra
LINKFLAGS += -g
else
CXXFLAGS += -O2
LINKFLAGS += -O2
endif

.PHONY: all static example install distclean clean directories

all: static example

static: directories $(STATIC_LIBRARY)

install:
	cp -r bin/* $(INSTALL_PREFIX)/bin/*
	cp -r lib/* $(INSTALL_PREFIX)/lib/*
	cp -r * $(INSTALL_PREFIX)/include/*

distclean:
	rm -rf .build

clean: distclean
	rm -rf lib bin
	rm example/test

directories:
	mkdir -p .build lib .build/static .build/dynamic
	
example: example/test

example/test:
	g++ -o example/test example/test.cpp

$(STATIC_LIBRARY): $(STATIC_OBJECTS)
	$(AR) r $@ $^

.build/static/%.o: %.cpp $(HEADERS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) -DSTATIC_LIB
