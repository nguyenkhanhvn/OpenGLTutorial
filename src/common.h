#pragma once

#include <fstream>
#include <iostream>

#include <glad/glad.h>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);


std::string get_file_contents(const char* filename);
