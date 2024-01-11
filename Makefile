CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = test
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

INCLUDES = -I.

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
