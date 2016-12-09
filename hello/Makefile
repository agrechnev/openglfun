CPP=g++
#LIBS= -lGLEW -lglfw  -lGL -lX11 -pthread -lXrandr -lXi
LIBS= -lGLEW -lglfw  -lGL


hello: hello.o 
	$(CPP) -Wall  -o hello hello.o $(LIBS)

hello.o: hello.cpp
	$(CPP) -c hello.cpp

clean:
	-rm hello.o hello
