#include "Application.h"

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "shader.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"
#include "indexbuffer.h"
#include "texture.h"
#include "camera.h"
#include "mesh.h"
#include "model.h"




// Vertices coordinates
static std::vector<Vertex> vertices =
{ //     COORDINATES		/        NORMALS		/        COLORS				/    TexCoord	//
	{glm::vec3(-0.5f, 0.0f,  0.5f),		glm::vec3(0.0f, -1.0f, 0.0f),		glm::vec3(0.83f, 0.70f, 0.44f), 	glm::vec2(0.0f, 0.0f)},		// Bottom side
	{glm::vec3(-0.5f, 0.0f, -0.5f),		glm::vec3(0.0f, -1.0f, 0.0f),		glm::vec3(0.83f, 0.70f, 0.44f),		glm::vec2(0.0f, 2.0f)},		// Bottom side
	{glm::vec3( 0.5f, 0.0f, -0.5f),		glm::vec3(0.0f, -1.0f, 0.0f),		glm::vec3(0.83f, 0.70f, 0.44f),		glm::vec2(2.0f, 2.0f)},		// Bottom side
	{glm::vec3( 0.5f, 0.0f,  0.5f),		glm::vec3(0.0f, -1.0f, 0.0f),		glm::vec3(0.83f, 0.70f, 0.44f),		glm::vec2(2.0f, 0.0f)},		// Bottom side

	{glm::vec3(-0.5f, 0.0f,  0.5f),		glm::vec3(0.8f, 0.5f,  0.0f),		glm::vec3(0.83f, 0.70f, 0.44f), 	glm::vec2(0.0f, 0.0f)},		// Left Side
	{glm::vec3(-0.5f, 0.0f, -0.5f),		glm::vec3(0.8f, 0.5f,  0.0f),		glm::vec3(0.83f, 0.70f, 0.44f),		glm::vec2(2.0f, 0.0f)},		// Left Side
	{glm::vec3( 0.0f, 0.8f,  0.0f),		glm::vec3(0.8f, 0.5f,  0.0f),		glm::vec3(0.92f, 0.86f, 0.76f),		glm::vec2(1.0f, 2.0f)},		// Left Side

	{glm::vec3(-0.5f, 0.0f, -0.5f),		glm::vec3(0.0f, 0.5f, -0.8f),		glm::vec3(0.83f, 0.70f, 0.44f),		glm::vec2(2.0f, 0.0f)},		// Non-facing side
	{glm::vec3( 0.5f, 0.0f, -0.5f),		glm::vec3(0.0f, 0.5f, -0.8f),		glm::vec3(0.83f, 0.70f, 0.44f),		glm::vec2(0.0f, 0.0f)},		// Non-facing side
	{glm::vec3( 0.0f, 0.8f,  0.0f),		glm::vec3(0.0f, 0.5f, -0.8f),		glm::vec3(0.92f, 0.86f, 0.76f),		glm::vec2(1.0f, 2.0f)},		// Non-facing side

	{glm::vec3( 0.5f, 0.0f, -0.5f),		glm::vec3(0.8f, 0.5f,  0.0f),		glm::vec3(0.83f, 0.70f, 0.44f),		glm::vec2(0.0f, 0.0f)},		// Right side
	{glm::vec3( 0.5f, 0.0f,  0.5f),		glm::vec3(0.8f, 0.5f,  0.0f),		glm::vec3(0.83f, 0.70f, 0.44f),		glm::vec2(2.0f, 0.0f)},		// Right side
	{glm::vec3( 0.0f, 0.8f,  0.0f),		glm::vec3(0.8f, 0.5f,  0.0f),		glm::vec3(0.92f, 0.86f, 0.76f),		glm::vec2(1.0f, 2.0f)},		// Right side

	{glm::vec3( 0.5f, 0.0f,  0.5f),		glm::vec3(0.0f, 0.5f,  0.8f),		glm::vec3(0.83f, 0.70f, 0.44f),		glm::vec2(2.0f, 0.0f)},		// Facing side
	{glm::vec3(-0.5f, 0.0f,  0.5f),		glm::vec3(0.0f, 0.5f,  0.8f),		glm::vec3(0.83f, 0.70f, 0.44f), 	glm::vec2(0.0f, 0.0f)},		// Facing side
	{glm::vec3( 0.0f, 0.8f,  0.0f),		glm::vec3(0.0f, 0.5f,  0.8f),		glm::vec3(0.92f, 0.86f, 0.76f),		glm::vec2(1.0f, 2.0f)},		// Facing side
};

// Indices for vertices order
static std::vector<GLuint> indices =
{
	0, 1, 2, // Bottom side
	0, 2, 3, // Bottom side
	4, 6, 5, // Left side
	7, 9, 8, // Non-facing side
	10, 12, 11, // Right side
	13, 15, 14 // Facing side
};


static std::vector<Vertex> lightVertices =
{ //     COORDINATES     //
	{glm::vec3(-0.1f, -0.1f,  0.1f)},
	{glm::vec3(-0.1f, -0.1f, -0.1f)},
	{glm::vec3(0.1f, -0.1f, -0.1f)},
	{glm::vec3(0.1f, -0.1f,  0.1f)},
	{glm::vec3(-0.1f,  0.1f,  0.1f)},
	{glm::vec3(-0.1f,  0.1f, -0.1f)},
	{glm::vec3(0.1f,  0.1f, -0.1f)},
	{glm::vec3(0.1f,  0.1f,  0.1f)},
};

static std::vector<GLuint> lightIndices =
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


static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

Application::Application(std::string title, unsigned int width, unsigned int height): 
	Title(title), Width(width), Height(height), m_window(nullptr)
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		throw std::error_code();

	// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
	m_glsl_version = "#version 100";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
	// GL 3.2 + GLSL 150
	m_glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 3.0 + GLSL 130
	m_glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

	// Create window with graphics context
	m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (m_window == NULL)
		throw std::error_code();
	glfwMakeContextCurrent(m_window);

	// Load Glad
	gladLoadGL();

	glfwSwapInterval(1); // Enable vsync

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	m_io = &ImGui::GetIO();
	m_io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	m_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	m_io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	m_io->ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (m_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init(m_glsl_version);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	// - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);


	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);
}

Application::~Application()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}

int Application::run()
{
	
	// Our state
		// Light
	Shader lightShader("res/shaders/Light.vert.shader", "res/shaders/Light.frag.shader");

	Mesh lightMesh(lightVertices, lightIndices, {});

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	lightShader.Bind();
	lightShader.SetUniform4f("lightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	lightShader.SetUniformMat4f("model", lightModel);
	lightShader.Unbind();



	// Program
	Shader programShader("res/shaders/Program.vert.shader", "res/shaders/Program.frag.shader");


	programShader.Bind();
	programShader.SetUniform4f("lightColor", lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	programShader.SetUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);

	Camera camera(Width, Height, glm::vec3(0.0f, 0.0f, 5.0f));

	Model model("res/models/sword/scene.gltf");
	float posModel[3] = { 0.0f, 0.0f, 0.0f };
	float rotModel[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	float scaleModel[3] = { 0.1f, 0.1f, 0.1f };
	glm::mat4 modelTranslation = glm::mat4(1.0f);


	Mesh obj(vertices, indices, {
		Texture("res/textures/planks.png", "diffuse", 0),
		Texture("res/textures/planksSpec.png", "specular", 1),
		});

	float posObj[3] = { 0.0f, 0.0f, 0.0f };
	float rotObjSpd[3] = { 0.0f, 0.0f, 0.0f };
	float scaleObj[3] = { 1.0f, 1.0f, 1.0f };
	glm::mat4 objMatrix = glm::mat4(1.0f);

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Main loop
	while (!glfwWindowShouldClose(m_window))
	{
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// calculate model
		objMatrix = glm::rotate(objMatrix, glm::radians(rotObjSpd[0]), glm::vec3(1.0f, 0.0f, 0.0f));
		objMatrix = glm::rotate(objMatrix, glm::radians(rotObjSpd[1]), glm::vec3(0.0f, 1.0f, 0.0f));
		objMatrix = glm::rotate(objMatrix, glm::radians(rotObjSpd[2]), glm::vec3(0.0f, 0.0f, 1.0f));

		// Draw
		camera.Input(m_window);

		lightMesh.DrawSimple(lightShader, camera);

		model.Draw(programShader, camera, glm::vec3(posModel[0], posModel[1], posModel[2]), glm::quat(rotModel[0], rotModel[1], rotModel[2], rotModel[3]), glm::vec3(scaleModel[0], scaleModel[1], scaleModel[2]));

		obj.Draw(programShader, camera, objMatrix, glm::vec3(posObj[0], posObj[1], posObj[2]), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(scaleObj[0], scaleObj[1], scaleObj[2]));

		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// ImGui Design
		{
			ImGui::Begin("Setting");                          // Create a window called "Hello, world!" and append into it.

			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
			ImGui::SliderFloat3("Model position", posModel, -10.0f, 10.0f);
			ImGui::SliderFloat3("Model rotation quaternion", rotObjSpd, -1.0f, 1.0f);
			ImGui::SliderFloat3("Model scale", scaleModel, 0.01f, 10.0f);

			ImGui::SliderFloat3("Object position", posObj, -10.0f, 10.0f);
			ImGui::SliderFloat3("Object rotation speed", rotObjSpd, 0.01f, 1.0f);
			ImGui::SliderFloat3("Object scale", scaleObj, 0.01f, 10.0f);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(m_window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (m_io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}


		glfwSwapBuffers(m_window);
	}


	return 0;
}
