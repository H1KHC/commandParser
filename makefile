STATIC_LIBRARY = lib/libcommandParser.a
DYNAMIC_LIBRARY = bin/commandParser.dll
IMPORT_LIBRARY = lib/libcommandParser.dll.a
INSTALL_PREFIX = /usr/

CXXFLAGS = -fPIC
LINKFLAGS =

HEADERS = $(wildcard src/*.h include/*.h)
OBJECTS = $(patsubst src/%.cpp, %.o, $(wildcard src/*.cpp))
STATIC_OBJECTS = $(patsubst %.o, .build/static/%.o, $(OBJECTS))
DYNAMIC_OBJECTS = $(patsubst %.o, .build/dynamic/%.o, $(OBJECTS))

ifdef DEBUG
CXXFLAGS += -g -Wall -Wextra
LINKFLAGS += -g
else
CXXFLAGS += -O2
LINKFLAGS += -O2
endif

.PHONY: all static dynamic install distclean clean directories

all: static dynamic

static: directories $(STATIC_LIBRARY)

dynamic: directories $(DYNAMIC_LIBRARY)

install:
	cp -r bin/* $(INSTALL_PREFIX)/bin/*
	cp -r lib/* $(INSTALL_PREFIX)/lib/*
	cp -r include/* $(INSTALL_PREFIX)/include/*

distclean:
	rm -rf .build

clean: distclean
	rm -rf lib bin

directories:
	mkdir -p .build lib bin .build/static .build/dynamic
	
example:
	g++ -o test/test test/test.cpp

$(STATIC_LIBRARY): $(STATIC_OBJECTS)
	$(AR) r $@ $^

$(DYNAMIC_LIBRARY): $(DYNAMIC_OBJECTS)
	$(CXX) -shared -o $@ $^ $(CXXFLAGS) -Wl,--out-implib=$(IMPORT_LIBRARY)

.build/static/%.o: src/%.cpp $(HEADERS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) -DSTATIC_LIB

.build/dynamic/%.o: src/%.cpp $(HEADERS)
	$(CXX) -c -o $@ $< $(CXXFLAGS) -DLIB_IMPLEMENT