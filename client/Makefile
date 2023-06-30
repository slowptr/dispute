CC=gcc
ARGS=-Wall
LIBS=-lSDL2main -lSDL2 -lSDL2_image -lm -lenet
TARGET=a.out
SRCS=main.c core_wrapper.c renderer.c game.c player.c world.c camera.c ui.c obj_loader.c viewmodel.c weapon.c network.c
all:
	$(CC) $(ARGS) -o $(TARGET) $(SRCS) $(LIBS)
