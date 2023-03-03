#include "common.h"

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Camera.h"


static int width = 800;
static int height = 800;


// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS       //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 5.0f,      0.0f, -1.0f, 0.0f, // Bottom side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, -1.0f, 0.0f, // Bottom side

	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,     -0.8f, 0.5f,  0.0f, // Left Side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,     -0.8f, 0.5f,  0.0f, // Left Side

	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.0f, 0.5f, -0.8f, // Non-facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f, -0.8f, // Non-facing side

	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	 0.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.8f, 0.5f,  0.0f, // Right side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.8f, 0.5f,  0.0f, // Right side

	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	 5.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f, 	 0.0f, 0.0f,      0.0f, 0.5f,  0.8f, // Facing side
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	 2.5f, 5.0f,      0.0f, 0.5f,  0.8f  // Facing side
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};


GLfloat lightVertices[] =
{ //     COORDINATES     //
	-0.1f, -0.1f,  0.1f,
	-0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f, -0.1f,
	 0.1f, -0.1f,  0.1f,
	-0.1f,  0.1f,  0.1f,
	-0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f, -0.1f,
	 0.1f,  0.1f,  0.1f
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};



int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Practice OpenGL", NULL, NULL);

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, width, height);

	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glBlendEquation(GL_FUNC_ADD));
	{
		// Light
		Shader lightShader("res/shaders/Light.vert.shader", "res/shaders/Light.frag.shader");

		VertexArray lightVa;
		VertexBuffer lightVb(sizeof(lightVertices), lightVertices, GL_STATIC_DRAW);
		VertexBufferLayout lightLayout;
		lightLayout.Push(GL_FLOAT, 3, GL_FALSE);
		lightVa.AddBuffer(lightVb, lightLayout);


		IndexBuffer lightIb(sizeof(lightIndices), lightIndices, GL_STATIC_DRAW);

		lightVa.Unbind();
		lightVb.Unbind();
		lightIb.Unbind();

		glm::vec4 lightColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);

		lightShader.Bind();
		lightShader.SetUniformMat4f("model", lightModel);
		lightShader.SetUniform4f("lightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		lightShader.Unbind();


		// Program
		Shader programShader("res/shaders/Program.vert.shader", "res/shaders/Program.frag.shader");

		VertexArray va;
		VertexBuffer vb(sizeof(vertices), vertices, GL_STATIC_DRAW);
		VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		va.AddBuffer(vb, layout);


		IndexBuffer ib(sizeof(indices), indices, GL_STATIC_DRAW);

		va.Unbind();
		vb.Unbind();
		ib.Unbind();

		Texture texture("res/textures/brick.png", GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE);
		texture.TexUnit(programShader, "tex0", 0);

		glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::mat4 pyramidModel = glm::mat4(1.0f);
		pyramidModel = glm::translate(pyramidModel, pyramidPos);

		programShader.Bind();
		programShader.SetUniformMat4f("model", pyramidModel);
		programShader.SetUniform4f("lightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		programShader.SetUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);

		Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


		// Enables the Depth Buffer
		glEnable(GL_DEPTH_TEST);


		// Variables that help the rotation of the pyramid
		float rotationStep = 0.4f;

		float scale = 0.5f;
		while (!glfwWindowShouldClose(window))
		{
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));


			lightShader.Bind();

			camera.Use(lightShader, "camMatrix");

			lightVa.Bind();

			GLCall(glDrawElements(GL_TRIANGLES, sizeof(lightIndices) / sizeof(int), GL_UNSIGNED_INT, 0));



			programShader.Bind();
			programShader.SetUniform1f("scale", scale);

			// rotate pyramid
			pyramidModel = glm::rotate(pyramidModel, glm::radians(rotationStep), glm::vec3(0.0f, 1.0f, 0.0f));
			programShader.SetUniformMat4f("model", pyramidModel);

			camera.Input(window);
			camera.Use(programShader, "camMatrix");

			texture.Bind();
			va.Bind();

			GLCall(glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0));


			GLCall(glfwSwapBuffers(window));

			GLCall(glfwPollEvents());
		}
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}