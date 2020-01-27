OBJS = DataManager.cpp ECS.cpp Game.cpp Login.cpp Map.cpp Menu.cpp ReadMap.cpp Settings.cpp main.cpp

CC = g++ #-std=c++11

# suppresses all warnings
COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL_mixer

OBJ_NAME = juego

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
