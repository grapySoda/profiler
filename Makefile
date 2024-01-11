# 编译器
CXX = g++

# 编译器选项
CXXFLAGS = -std=c++11 -Wall

# 可执行文件名称
TARGET = test

# 源文件
SRCS = main.cpp

# 目标文件
OBJS = $(SRCS:.cpp=.o)

# 头文件路径
INCLUDES = -I.

# all：默认目标，生成可执行文件
all: $(TARGET)

# 链接生成可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS)

# 编译生成目标文件
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# clean：清理中间文件和可执行文件
clean:
	rm -f $(OBJS) $(TARGET)
