CC 			= clang
LD			= clang
CXXFLAGS 	= -O0 -Wall -std=c++17
LDFLAGS		= -lstdc++

SOURCES 	= $(wildcard *.cc)
TEST_SOURCES= $(wildcard tests/*.cc)

OBJS 		= $(patsubst %.cc, %.o, $(SOURCES))
TEST_OBJS 	= $(patsubst %.cc, %.o, $(TEST_SOURCES))

TARGET		= main

%.o : %.cc
	$(CC) $(CXXFLAGS) -c $< -o $@

tests/%.o : tests/%.cc
	$(CC) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET)

tests : $(TEST_OBJS)

all : $(TARGET) tests

clean : 
	rm -rf $(OBJS) $(TEST_OBJS) $(TARGET)

.PHONY : all tests clean

