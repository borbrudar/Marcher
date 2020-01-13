#pragma once
#include "Shader.h"

class Sphere {
public:
	Sphere() = default;
	Sphere(Shader shader) {
		load(shader);
	}

	void draw(Shader shader);
	void load(Shader shader);
	float vertices[18]{
		//pos
	-0.5f, -0.5f, 0.f,
	-0.5f,  0.5f, 0.f,
	 0.5f,  0.5f, 0.f,
	 0.5f,  0.5f, 0.f,
	-0.5f, -0.5f, 0.f,
	 0.5f, -0.5f, 0.f
	};

	unsigned int vao, vbo;
};