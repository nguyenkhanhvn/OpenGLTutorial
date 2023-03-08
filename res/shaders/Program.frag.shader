#version 330 core

out vec4 FragColor;


// Inputs the color from the Vertex Shader
in vec3 curPos;
in vec3 Normal;
in vec2 texCoord;

// texture
uniform sampler2D diffuse0;
uniform sampler2D specular0;

// light
uniform vec4 lightColor;
uniform vec3 lightPos;

// cam
uniform vec3 camPos;

vec4 pointLight()
{
	vec3 lightVec = lightPos - curPos;
	vec3 lightDirection = normalize(lightVec);

	// intensity of light with respect to distance
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

	// ambient
	float ambient = 0.2f;

	// diffuse
	vec3 normal = normalize(Normal);
	float diffuse = max(dot(normal, lightDirection), 0.0f) * inten;

	// specular
	float specularScale = 1.8f;
	vec3 lightReflect = reflect(-lightDirection, normal);
	vec3 viewDirection = normalize(camPos - curPos);
	float specularAmount = pow(max(dot(lightReflect, viewDirection), 0.0f), 16);
	float specular = specularScale * specularAmount * inten;

	return ((texture(diffuse0, texCoord) * (ambient + diffuse) + texture(specular0, texCoord).r * specular) * lightColor);
}

vec4 directLight()
{
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));

	// ambient
	float ambient = 0.4f;

	// diffuse
	vec3 normal = normalize(Normal);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// specular
	float specularScale = 0.5f;
	vec3 lightReflect = reflect(-lightDirection, normal);
	vec3 viewDirection = normalize(camPos - curPos);
	float specularAmount = pow(max(dot(lightReflect, viewDirection), 0.0f), 16);
	float specular = specularScale * specularAmount;

	return (texture(diffuse0, texCoord) * (ambient + diffuse) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotLight()
{
	// controls how big the area that is lit up is
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	vec3 lightDirection = normalize(lightPos - curPos);
	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	// ambient
	float ambient = 0.2f;

	// diffuse
	vec3 normal = normalize(Normal);
	float diffuse = max(dot(normal, lightDirection), 0.0f) * inten;

	// specular
	float specularScale = 0.8f;
	vec3 lightReflect = reflect(-lightDirection, normal);
	vec3 viewDirection = normalize(camPos - curPos);
	float specularAmount = pow(max(dot(lightReflect, viewDirection), 0.0f), 16);
	float specular = specularScale * specularAmount * inten;

	return ((texture(diffuse0, texCoord) * (ambient + diffuse) + texture(specular0, texCoord).r * specular) * lightColor);
}

void main()
{
	FragColor = directLight();
}