#include "common.h"

#include <string>

#include "Application.h"


static std::string title = "Practice OpenGL";

static int width = 1200;
static int height = 800;


int main()
{
	Application app("Practice-OpenGL", width, height);
	return app.run();
}

//int main_bk()
//{
//	glfwInit();
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
//
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwMakeContextCurrent(window);
//
//	gladLoadGL();
//
//	glViewport(0, 0, width, height);
//
//	//GLCall(glEnable(GL_BLEND));
//	//GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
//	//GLCall(glBlendEquation(GL_FUNC_ADD));
//	{
//		// Light
//		Shader lightShader("res/shaders/Light.vert.shader", "res/shaders/Light.frag.shader");
//
//		Mesh lightMesh(lightVertices, lightIndices, {});
//
//		glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//		glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
//		glm::mat4 lightModel = glm::mat4(1.0f);
//		lightModel = glm::translate(lightModel, lightPos);
//
//		lightShader.Bind();
//		lightShader.SetUniform4f("lightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);
//		lightShader.SetUniformMat4f("model", lightModel);
//		lightShader.Unbind();
//
//
//
//		// Program
//		Shader programShader("res/shaders/Program.vert.shader", "res/shaders/Program.frag.shader");
//
//
//		programShader.Bind();
//		programShader.SetUniform4f("lightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);
//		programShader.SetUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);
//
//		Camera camera(width, height, glm::vec3(0.0f, 0.0f, 1.0f));
//
//		Model model("res/models/sword/scene.gltf");
//
//		Mesh obj(vertices, indices, {
//			Texture("res/textures/planks.png", "diffuse", 0),
//			Texture("res/textures/planksSpec.png", "specular", 1),
//			});
//
//
//		glm::vec3 pyramidPos = glm::vec3(1.0f, 0.0f, 0.0f);
//		glm::mat4 pyramidModel = glm::mat4(1.0f);
//		pyramidModel = glm::translate(pyramidModel, pyramidPos);
//
//
//		// Enables the Depth Buffer
//		glEnable(GL_DEPTH_TEST);
//
//
//		double prevTime = glfwGetTime();
//		double curTime = 0;
//		double timeDiff = 0;
//		unsigned int counter = 0;
//
//		while (!glfwWindowShouldClose(window))
//		{
//			curTime = glfwGetTime();
//			timeDiff = curTime - prevTime;
//			counter++;
//			if (timeDiff >= 1.0 / 30.0)
//			{
//				std::string fps = std::to_string(counter / timeDiff);
//				std::string ms = std::to_string(timeDiff / counter * 1000);
//				glfwSetWindowTitle(window, (title + " - FPS: " + fps + " FPS / " + ms + "ms").c_str());
//				prevTime = curTime;
//				counter = 0;
//			}
//
//
//			GLCall(glClearColor(0.07f, 0.13f, 0.17f, 1.0f));
//			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
//
//			lightMesh.DrawSimple(lightShader, camera);
//
//			camera.Input(window);
//			
//			model.Draw(programShader, camera, 0.01f);
//
//
//			obj.Draw(programShader, camera, pyramidModel);
//
//			GLCall(glfwSwapBuffers(window));
//
//			GLCall(glfwPollEvents());
//		}
//	}
//
//	glfwDestroyWindow(window);
//
//	glfwTerminate();
//
//	return 0;
//}