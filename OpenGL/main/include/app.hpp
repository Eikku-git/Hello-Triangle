#pragma once
#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"

struct app_data {
public:
	GLFWwindow* window;
    GLuint vertex_buffer, vertex_shader, fragment_shader, program;
	GLint mvp_location, vpos_location, vcol_location;
};

void init(app_data& data);
void run(app_data& data);
void terminate(app_data& data);
