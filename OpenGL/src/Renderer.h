#pragma once

#include <GL/glew.h>

#define ASSERT(x) if(!(x)) __debugbreak();
//call GlClearError than call a given function
//than check error
//# - turns to string
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);