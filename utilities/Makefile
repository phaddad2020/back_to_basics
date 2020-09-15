
PARENTDIR = $(shell pwd)/..

CXX = g++
CXXFLAGS = -std=c++17 -m64 -Wall -W -Werror -g
GEN_RAND_ARR_DATA_TARGET = gen_random_array_data

INCLUDES = -I$(PARENTDIR)/global_inc -I.

CXXFLAGS += $(INCLUDES)
CXXFLAGS += -Wno-unused-parameter

GEN_RAND_ARR_DATA_SOURCES := gen_random_array_data.cpp
GEN_RAND_ARR_DATA_OBJS := $(GEN_RAND_ARR_DATA_SOURCES:.cpp=.o)

gen_random_array_data: $(GEN_RAND_ARR_DATA_OBJS)

$(GEN_RAND_ARR_DATA_TARGET):
	$(CXX) $(INCLUDES) -o $@ $^

all: $(GEN_RAND_ARR_DATA_TARGET)

clean:
	rm -f $(GEN_RAND_ARR_DATA_TARGET) $(GEN_RAND_ARR_DATA_OBJS)
