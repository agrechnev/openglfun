CC=gcc
CFLAGS=

#LIBS= -lGLEW -lglfw  -lGL -lX11 -pthread -lXrandr -lXi -lm
LIBS= -L. -lGLEW -lglfw  -lGL -lm -lSOIL
OBJS = mygl5.o initwin.o shaders.o vao.o texture.o
DEPS=initwin.h shaders.h vao.h texture.h
TARGET=mygl_exec5

$(TARGET): $(OBJS)
	$(CC) -Wall  -o $@  $(OBJS) $(LIBS)

.c.o: $(DEPS)
	$(CC) $(CFLAGS) -c $< 

clean:
	-rm $(OBJS) $(TARGET)
