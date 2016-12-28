CPP=g++
CPPFLAGS= 

#LIBS= -lGLEW -lglfw  -lGL -lX11 -pthread -lXrandr -lXi -lm
LIBS= -lGLEW -lglfw  -lGL -lm -lSOIL
OBJS = cppgl6.o initwin.o shaders.o vao.o texture.o
DEPS=initwin.hpp shaders.hpp vao.hpp texture.hpp camera.h
TARGET=cppgl_exec6

$(TARGET): $(OBJS)
	$(CPP) -Wall  -o $@  $(OBJS) $(LIBS)

.cpp.o: $(DEPS)
	$(CPP) $(CPPFLAGS) -c $< 

clean:
	-rm $(OBJS) $(TARGET)
