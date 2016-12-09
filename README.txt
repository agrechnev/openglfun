My fun with OpenGL (+GLFW+GLEW) by Oleksiy Grechnyev

I mainly follow learnopengl.com

hello is taken from the cite as is,

but mygl<number> I wrote by hand, in pure C (no C++), with many changes

---
LINUX:

You need:
OpenGL 3.3+ (e.g. MESA), libGL.so library is fine, no headers or static libs required
GLFW 3 development version (with .a and .h files), e.g. packages libglfw3 and libglfw-devel
GLEW  development version (with .a and .h files), e.g. packages glew and glew-devel

If MESA does not work with your handware or version is <3.3, force software mode with

export LIBGL_ALWAYS_SOFTWARE=1

read MESA docs for more options, and also this link

http://stackoverflow.com/questions/39213757/glfw-cannot-create-a-window-glx-failed-to-create-context-glxbadfbconfig

---
WINDOWS:

For Visual Studio, first install GLFW+GLEW. Place static  *.lib and *.f files somewhere.
Ignore makefiles, create a project (from existing sources?).
Add your lib and include directories to your project.  Build, run.

Probably possible with MinGW and MinGW-W64 (But NOT MSYS !), but I didn't try yet.

OpenGL itself comes from your graphics card driver
