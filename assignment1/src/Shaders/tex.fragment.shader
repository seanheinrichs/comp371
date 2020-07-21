#version 440


out vec4 FragColor;


in vec3 vertexDefinedColor;
in vec2 v_TexCoord;

uniform int fill;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	FragColor = texColor;
}