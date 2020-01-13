#include "Sphere.h"

void Sphere::draw(Shader shader)
{
	shader.use();
	// render box
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Sphere::load(Shader shader)
{
	//vao and vbo
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);	
}
