
CC          = gcc
CLINKER     = gcc
CCC         = g++
CCLINKER    = $(CCC)
INCLUDE_DIR = 
LIB_LIST = -framework GLUT -framework OpenGL -framework Cocoa
CFLAGS  = $(INCLUDE_DIR)
CCFLAGS = $(CFLAGS)
OPTFLAGS    = -g
LIB_PATH    =
LIBS = $(LIB_PATH) $(LIB_LIST)

objects = main.o gradient.o 

default: gradient

gradient: $(objects)
	$(CCLINKER) $(OPTFLAGS) -o gradient $(objects) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -w -c $*.c
.cc.o:
	$(CCC) $(CFLAGS) -w -c $*.cc

clean:
	rm gradient
	rm *.o
