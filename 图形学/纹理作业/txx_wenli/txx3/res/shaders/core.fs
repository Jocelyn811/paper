//Æ¬Ôª×ÅÉ«Æ÷
#version 330 core
in vec2 textcoords;
in vec3 Color;
out vec4 color;
uniform sampler2D Texture;
uniform sampler2D Texture1;
uniform float t;
void main()
{
	//color=vec4(ourColor, 1.0f);
	//color=vec4(1.0f, 0.0f, 0.0f, 1.0f);
	//color=texture(Texture, textcoords*3.0f).rgb;
	color=mix(texture(Texture, vec2(textcoords.x, 1-textcoords.y)), texture(Texture1, vec2(textcoords.x, 1-textcoords.y)), t);
}
 