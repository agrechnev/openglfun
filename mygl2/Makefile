CC=gcc
CFLAGS=

#LIBS= -lGLEW -lglfw  -lGL -lX11 -pthread -lXrandr -lXi
LIBS= -lGLEW -lglfw  -lGL
OBJS = mygl2.o initwin.o shaders.o vao.o
DEPS=initwin.h shaders.h vao.h

mygl_exec2: $(OBJS)
	$(CC) -Wall  -o $@  $(OBJS) $(LIBS)

.c.o: $(DEPS)
	$(CC) -c $< $(CFLAGS)

clean:
	-rm $(OBJS) mygl_exec2
