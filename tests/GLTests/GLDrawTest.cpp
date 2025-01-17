#include <iostream>
#include <../Lamina/include/colors.hpp>
#include <../Lamina/include/window.hpp>
#include <../Lamina/include/Math/vec2.hpp>
#include <../Lamina/include/Math/matrix.hpp>
#include <../Lamina/include/GL/opengl.hpp>
#include <chrono>

int main()
{
	if (!glfwInit()) return -1;
	lm::Window window(lm::vec2<int>(800, 600), "test window", LM_WINDOW_DEFAULT, 8);
	auto epoch = std::chrono::steady_clock::now();

	while (window.IsOpen())
	{
		glfwPollEvents();

		float time = std::chrono::duration_cast<std::chrono::duration<float>>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - epoch)).count();


		window.Clear(lm::Color{ 50, 50, 50, 255 });

		std::vector<GLfloat> vertices = {
			0.5, -0.5, 0.0, 1, 0, 0, 1,
			-0.5, -0.5, 0.0, 0, 1, 0, 1,
			-0.5, 0.5, 0.0, 0, 1, 1, 1,
			0.5, 0.5, 0.0, 1, 0, 1, 1
		};

		const GLuint indices[] =
		{
			0, 1, 2,
			2, 3, 0
		};

		glfwMakeContextCurrent(window.window);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) std::cout << "Failed to load GLAD" << std::endl;

		GLuint EBO;
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		GLuint vertexArray;
		glGenVertexArrays(1, &vertexArray);

		GLuint program = lm::GLRenderer::CompileShader("Shaders/basicVertexShader.vert", "Shaders/basicFragShader.frag");
		glUseProgram(program);
		GLint uniformTime = glGetUniformLocation(program, "currentTime");
		glUniform1f(uniformTime, time);

		glBindVertexArray(vertexArray);
		
		GLuint vertexBuffer;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7*sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		//glDisableVertexAttribArray(1);

		window.Display();
	}
	glfwTerminate();
	return 0;
}