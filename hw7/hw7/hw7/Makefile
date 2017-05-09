
CC          = gcc
CLINKER     = gcc
CCC         = g++
CCLINKER    = $(CCC)
INCLUDE_DIR = #-I/usr/lib/glib/include -I/usr/lib/gnome-libs/include
LINUX_LIBS  = -lGL -lglut -lGLU
MACOS_LIBS  = -framework GLUT -framework OpenGL -framework Cocoa
CFLAGS  = $(INCLUDE_DIR)
CCFLAGS = $(CFLAGS)
OPTFLAGS    = -g
LIB_PATH    = -L/usr/X11R6/lib
LIBS = $(LIB_PATH) $(LINUX_LIBS)

objects = solar.o Celestial.o Planet.o Earth.o Sun.o trackball.o
exec    = solar

default: $(exec)

solar: $(objects)
	$(CCLINKER) $(OPTFLAGS) -o $(exec) $(objects) $(LIBS)

clean:
	rm *.o
	rm solar

%.o : %.cc %.h
	$(CCC) $(CFLAGS) -w -c $< -o $@

%.o : %.c %.h
	$(CC) $(CFLAGS) -w -c $< -o $@

%.o : %.cc
	$(CCC) $(CFLAGS) -w -c $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) -w -c $< -o $@

