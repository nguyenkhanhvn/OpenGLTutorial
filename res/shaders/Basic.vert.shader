#version 330 core

//Positions/Coordinates
layout(location = 0) in vec3 aPos;
// Colors
layout(location = 1) in vec3 aColor;
// Texture Coordinates
layout(location = 2) in vec2 aTex;


// Outputs the color for the Fragment Shader
out vec3 color;
out vec2 texCoord;

// Controls the scale of the vertices
uniform float scale;

// Inputs the matrices needed for 3D viewing with perspective
uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * model * vec4(aPos.x * scale, aPos.y * scale, aPos.z * scale, 1.0);
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;
}