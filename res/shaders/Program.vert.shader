#version 330 core

//Positions/Coordinates
layout(location = 0) in vec3 aPos;
// Colors
layout(location = 1) in vec3 aColor;
// Texture Coordinates
layout(location = 2) in vec2 aTex;
// Normal
layout(location = 3) in vec3 aNormal;


// Outputs the color for the Fragment Shader
out vec2 texCoord;
out vec3 Normal;
out vec3 curPos;

// Controls the scale of the vertices
uniform float scale;

// Inputs the matrices needed for 3D viewing with perspective
uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
	curPos = vec3(model * vec4(aPos.x * scale, aPos.y * scale, aPos.z * scale, 1.0));
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(curPos, 1.0f);


	texCoord = aTex;
	Normal = aNormal;
}