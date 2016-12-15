CC=gcc
CFLAGS=

#LIBS= -lGLEW -lglfw  -lGL -lX11 -pthread -lXrandr -lXi -lm
LIBS= -lGLEW -lglfw  -lGL -lm
OBJS = mygl3.o initwin.o shaders.o vao.o
DEPS=initwin.h shaders.h vao.h

mygl_exec3: $(OBJS)
	$(CC) -Wall  -o $@  $(OBJS) $(LIBS)

.c.o: $(DEPS)
	$(CC) -c $< $(CFLAGS)

clean:
	-rm $(OBJS) mygl_exec3
