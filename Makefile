INCLUDE_LIBRARIES = glfw gl
INCLUDE_PROJECTS = hatchetfish fluxions-deps fluxions-gte viperfish
INCLUDEDIRS = $(patsubst %,-I../%/include,$(INCLUDE_PROJECTS))
LIBDIRS = $(patsubst %,-L../%/,$(INCLUDE_PROJECTS))
LIBS = $(patsubst %,-l%,$(INCLUDE_PROJECTS)) $(patsubst %,-l%,$(INCLUDE_LIBRARIES))

CXX = g++
AR = ar rcs
CXXFLAGS = -std=c++14 -g -Wall -Iinclude $(INCLUDEDIRS)
LDFLAGS = $(LIBDIRS) $(LIBS)

# We use this to 
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.hpp) $(wildcard *.h)
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))

# Write the name of your program here
TARGET = glfw-template

.PHONY: all clean

# This "phony" target says we want the target to be built
all: $(TARGET)

# This "phony" target removes all built files
clean:
	$(RM) *.o
	$(RM) $(TARGET)

# Tells make how to make target out of objects
$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)

# Tells make how to make objects out of source code
# It also says when we change a header, recompile
# $< is the input, $@ is the output
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
