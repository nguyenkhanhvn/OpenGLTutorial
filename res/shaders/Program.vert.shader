#version 330 core

//Positions/Coordinates
layout(location = 0) in vec3 aPos;
// Normal
layout(location = 1) in vec3 aNormal;
// Colors
layout(location = 2) in vec3 aColor;
// Texture Coordinates
layout(location = 3) in vec2 aTex;


// Outputs the color for the Fragment Shader
out vec3 curPos;
out vec3 Normal;
out vec2 texCoord;


// Inputs the matrices needed for 3D viewing with perspective
uniform mat4 camMatrix;

// Inputs the transformation matrices
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;

void main()
{
	curPos = (model * translation * rotation * scale * vec4(aPos, 1.0f)).xyz;
	Normal = vec3(model * vec4(aNormal, 0.0));
	texCoord = /*mat2(0.0f, -1.0f, 1.0f, 0.0f) **/ aTex;

	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(curPos, 1.0f);
}