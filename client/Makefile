CC=gcc
ARGS=-Wall -g3
LIBS=
TARGET=a.out
SRCS=main.c core_wrapper.c renderer.c game.c player.c world.c camera.c ui.c obj_loader.c viewmodel.c weapon.c network.c weapon_action_handler.c weapon_bullet.c dmap_loader.c tga.c

ifeq ($(OS),Windows_NT)
	# Windows specific settings
	ARGS += -I./thirdparty/include -L./thirdparty/lib -L.
	LIBS = -lmingw32
	TARGET = a.exe
endif

LIBS += -lSDL2main -lSDL2 -lSDL2_image -lm -lenet

all:
	$(CC) $(ARGS) -o $(TARGET) $(SRCS) $(LIBS)
