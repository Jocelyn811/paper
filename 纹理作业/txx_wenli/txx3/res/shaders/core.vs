#version 330 core
layout(location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout(location = 2) in vec2 textCoords;
out vec2 textcoords;
out vec3 Color;
void main()
{
	gl_Position = vec4(position, 1.0f);
	Color = color;
	//textcoords = textCoords;
	textcoords = vec2(textCoords.x, textCoords.y);
}