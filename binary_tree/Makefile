
PARENTDIR = $(shell pwd)/..

CXX = g++
CXXFLAGS = -std=c++17 -m64 -Wall -W -Werror -g
TARGET = binary_tree

INCLUDES = -I$(PARENTDIR)/global_inc -I.

CXXFLAGS += $(INCLUDES)
CXXFLAGS += -Wno-unused-parameter

SOURCES := main.cpp
OBJS := $(SOURCES:.cpp=.o)

binary_tree: $(OBJS)

$(TARGET):
	$(CXX) $(INCLUDES) -o $@ $^

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
