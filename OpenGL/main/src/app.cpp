#include "app.hpp"
#include <iostream>
#include "linmath.hpp"

struct vertex {
public:
	float x, y;
	float r = 1, g = 1, b = 0;
	vertex(float x = 0, float y = 0, float r = 0, float g = 0, float b = 0) {
		this->x = x; this->y = y; this->r = r; this->g = g; this->b = b;
	}
};


static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";

static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

void init(app_data& data) {
	glfwInit();
	data.window = glfwCreateWindow(540, 540, "engine", nullptr, nullptr);
	glfwMakeContextCurrent(data.window);
	gladLoadGL();
	glfwSwapInterval(1);
	vertex triangle[3] = { vertex(-0.6f, -0.4f, 1, 0, 0), vertex(0.6f, -0.4f, 0, 1, 0), vertex(0.f, 0.6f, 0, 0, 1) };
	glGenBuffers(1, &data.vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, data.vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

	data.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(data.vertex_shader, 1, &vertex_shader_text, nullptr);
	glCompileShader(data.vertex_shader);

	data.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(data.fragment_shader, 1, &fragment_shader_text, NULL);
	glCompileShader(data.fragment_shader);

	data.program = glCreateProgram();
	glAttachShader(data.program, data.vertex_shader);
	glAttachShader(data.program, data.fragment_shader);
	glLinkProgram(data.program);

	data.mvp_location = glGetUniformLocation(data.program, "MVP");
	data.vpos_location = glGetAttribLocation(data.program, "vPos");
	data.vcol_location = glGetAttribLocation(data.program, "vCol");

	glEnableVertexAttribArray(data.vpos_location);
	glVertexAttribPointer(data.vpos_location, 2, GL_FLOAT, GL_FALSE,
		sizeof(vertex), (void*)0);
	glEnableVertexAttribArray(data.vcol_location);
	glVertexAttribPointer(data.vcol_location, 3, GL_FLOAT, GL_FALSE,
		sizeof(vertex), (void*)(sizeof(float) * 2));
}

void run(app_data& data) {
	int width, height;
	quaternion rotation;
	float* rotationMatrix;
	while (!glfwWindowShouldClose(data.window)) {
		glfwPollEvents();
		glfwGetFramebufferSize(data.window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(data.program);
		rotation.createRotationAroundAxis(1.5f + glfwGetTime(), vec3(1, 0, 1));
		rotationMatrix = rotation.createRotationMatrix();
		glUniformMatrix4fv(data.mvp_location, 1, GL_FALSE, rotationMatrix);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(data.window);
	}
}


void terminate(app_data& data) {
	glfwTerminate();
}