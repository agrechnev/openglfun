CC=gcc
CFLAGS=

#LIBS= -lGLEW -lglfw  -lGL -lX11 -pthread -lXrandr -lXi -lm
LIBS= -lGLEW -lglfw  -lGL -lm -lSOIL
OBJS = mygl4.o initwin.o shaders.o vao.o texture.o
DEPS=initwin.h shaders.h vao.h texture.h

mygl_exec4: $(OBJS)
	$(CC) -Wall  -o $@  $(OBJS) $(LIBS)

.c.o: $(DEPS)
	$(CC) -c $< $(CFLAGS)

clean:
	-rm $(OBJS) mygl_exec4
