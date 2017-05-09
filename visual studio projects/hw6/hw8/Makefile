
CC          = gcc
CLINKER     = gcc
CCC         = g++
CCLINKER    = $(CCC)
INCLUDE_DIR = -I/usr/lib/glib/include -I/usr/lib/gnome-libs/include
LINUX_LIBS  = -lGL -lglut -lGLU
MACOS_LIBS  = -framework GLUT -framework OpenGL -framework Cocoa
CFLAGS      = $(INCLUDE_DIR)
CCFLAGS     = $(CFLAGS)
OPTFLAGS    = -g
LIB_PATH    = -L/usr/X11R6/lib
LIBS        = $(LIB_PATH) $(LINUX_LIBS)
objects     = Point3f.o surface.o main.o trackball.o interface.o
exec        = surf

default: $(exec)

$(exec): $(objects)
	$(CCLINKER) $(OPTFLAGS) -o $(exec) $(objects) $(LIBS)

clean:
	rm *.o
	rm $(exec)

%.o : %.cc %.h
	$(CCC) $(CFLAGS) -w -c $< -o $@

%.o : %.c %.h
	$(CC) $(CFLAGS) -w -c $< -o $@

%.o : %.cc
	$(CCC) $(CFLAGS) -w -c $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) -w -c $< -o $@

