CC=gcc
CFLAGS= -I 
INCLUDES = -I/usr/include/libxml2/ -I/home/pi/Desktop/beamy/beagle/fmod
DEPS = command.h alarm.h xml.h video.h server.h definition.h

OBJ = main.o server.o video.o xml.o alarm.o command.o
LFLAGS = -L/home/pi/Desktop/beamy/beagle
LIBS= -lxml2 -lcurl /home/pi/Desktop/beamy/beagle/fmod/libfmod.so
MAIN= main



%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDES) $(LIBS)

$(MAIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(INCLUDES) $(LIBS)

