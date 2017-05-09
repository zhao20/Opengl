
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
LIB_PATH    = -L/usr/X11R6/lib
LIBS = $(LIB_PATH) $(LINUX_LIBS)

exec    = triangles
objects = geometry.o interface.o Point3f.o main.o

default: $(exec)

$(exec): $(objects)
	$(CCLINKER) $(OPTFLAGS) -o $(exec) $(objects) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -w -c $*.c
.cc.o:
	$(CCC) $(CFLAGS) -w -c $*.cc

clean:
	rm *.o
	rm $(exec)
