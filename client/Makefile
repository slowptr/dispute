CC=gcc
ARGS=-Wall
LIBS=
TARGET=a.out
SRCS=main.c core_wrapper.c renderer.c game.c player.c world.c camera.c ui.c obj_loader.c viewmodel.c weapon.c network.c

ifeq ($(OS),Windows_NT)
	# Windows specific settings
	ARGS += -I./thirdparty/include -L./thirdparty/lib -L.
	LIBS = -lmingw32
	TARGET = a.exe
endif

LIBS += -lSDL2main -lSDL2 -lSDL2_image -lm -lenet

all:
	$(CC) $(ARGS) -o $(TARGET) $(SRCS) $(LIBS)
