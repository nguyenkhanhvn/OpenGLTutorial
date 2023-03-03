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


static int width = 800;
static int height = 800;


// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
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
        Shader shaderProgram("res/shaders/Basic.vert.shader", "res/shaders/Basic.frag.shader");

        VertexArray va;
        VertexBuffer vb(sizeof(vertices), vertices, GL_STATIC_DRAW);
        VertexBufferLayout layout;
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 3, GL_FALSE);
		layout.Push(GL_FLOAT, 2, GL_FALSE);
        va.AddBuffer(vb, layout);


        IndexBuffer ib(sizeof(indices), indices, GL_STATIC_DRAW);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();

        Texture texture("res/textures/brick.png", GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE);
        texture.TexUnit(shaderProgram, "tex0", 0);


        // Enables the Depth Buffer
        glEnable(GL_DEPTH_TEST);


		// Variables that help the rotation of the pyramid
		float rotation = 0.0f;
		double rotationStep = 0.2f;

        float scale = 0.5f;
        float scaleStep = 0.001f;
        while (!glfwWindowShouldClose(window))
        {
            GLCall(glClearColor(0.07f, 0.19f, 0.28f, 1.0f));
            GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

            shaderProgram.Bind();
            shaderProgram.SetUniform1f("scale", scale);
            scale += scaleStep;
            if (scale > 1.0f || scale < 0.5f)
                scaleStep *= -1.0f;

			// Simple timer
			rotation += rotationStep;

			// Initializes matrices so they are not the null matrix
			glm::mat4 model = glm::mat4(1.0f);
			glm::mat4 view = glm::mat4(1.0f);
			glm::mat4 proj = glm::mat4(1.0f);

			// Assigns different transformations to each matrix
			model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
			view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
			proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);

            shaderProgram.SetUniformMat4f("model", model);
            shaderProgram.SetUniformMat4f("view", view);
            shaderProgram.SetUniformMat4f("proj", proj);


            va.Bind();
            texture.Bind();

            glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);


            GLCall(glfwSwapBuffers(window));

            GLCall(glfwPollEvents());
        }
    }

    glfwDestroyWindow(window);

    glfwTerminate();

	return 0;
}