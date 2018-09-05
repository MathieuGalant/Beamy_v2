CC=gcc
CFLAGS= -I 
INCLUDES = -I/home/debian/beamy/fmod
DEPS = command.h alarm.h xml.h video.h server.h definition.h

OBJ = main.o server.o video.o xml.o alarm.o command.o
LFLAGS = -L/home/debian/beamy/
LIBS= -lxml2 /home/debian/beamy/fmod/libfmod.so -lfmod -L/home/debian/beamy
MAIN= main



%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDES) $(LIBS)

$(MAIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(INCLUDES) $(LIBS)

