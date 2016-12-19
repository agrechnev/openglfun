CPP=g++
CPPFLAGS= 

#LIBS= -lGLEW -lglfw  -lGL -lX11 -pthread -lXrandr -lXi -lm
LIBS= -lGLEW -lglfw  -lGL -lm -lSOIL
OBJS = cppgl3.o initwin.o shaders.o vao.o texture.o
DEPS=initwin.h shaders.h vao.h texture.h
TARGET=cppgl_exec3

$(TARGET): $(OBJS)
	$(CPP) -Wall  -o $@  $(OBJS) $(LIBS)

.cpp.o: $(DEPS)
	$(CPP) $(CPPFLAGS) -c $< 

clean:
	-rm $(OBJS) $(TARGET)
