
CC          = gcc
CLINKER     = gcc
CCC         = g++
CCLINKER    = $(CCC)
INCLUDE_DIR = 
LINUX_LIBS  = -lGL -lglut -lGLU
MACOS_LIBS  = -framework GLUT -framework OpenGL -framework Cocoa
CFLAGS  = $(INCLUDE_DIR)
CCFLAGS = $(CFLAGS)
OPTFLAGS    = -g
LIB_PATH    =
LIBS = $(LIB_PATH) $(LINUX_LIBS)

objects = main.o interface.o sierpinski.o

default: fractal

fractal: $(objects)
	$(CCLINKER) $(OPTFLAGS) -o fractal $(objects) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -w -c $*.c
.cc.o:
	$(CCC) $(CFLAGS) -w -c $*.cc

clean:
	rm fractal
	rm *.o
