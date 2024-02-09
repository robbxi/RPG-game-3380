# List of source file directories
SRC_DIR := ./src
# SUBDIRS := $(wildcard $(SRC_DIR)/*/)
# SRC_DIRS := $(SRC_DIR) $(SUBDIRS)

# Use wildcard to find all .cpp files in the specified directories
# SRCS := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))

# SRCS := $(wildcard src/*.cpp)

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')

#OBJS specifies which files to compile as part of the project
# OBJS = ./main.cpp ./Game.cpp ./Tile.cpp
OBJS := $(SRCS:.cpp=.o)

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lraylib -lGL -lm -pthread -ldl -lX11 -lXrandr -l Xinerama -lXi -lXcursor
# LINKER_FLAGS += -ljsoncpp

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = game.out

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CC) $(COMPILER_FLAGS) -c $< -o $@

# Clean rule to remove object files and the executable
clean:
	rm -f $(OBJS) $(OBJ_NAME)

clean-object:
	rm -f $(SRCS:.cpp=.o)

