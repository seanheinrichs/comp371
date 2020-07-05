#version 440
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform int fill;

// TODO: Remove textures and use colors as specified in A1.
// It's currently a texture because it's easier to see than a solid color
void main()
{
	// Yellow
	if (fill == 0)
	{
		FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	}
	// Turquoise
	else if (fill == 1)
	{
		FragColor = vec4(0.2f, 0.3f, 0.3f, 1.0f);
	}
	// Textures
	else 
	{
		FragColor = texture(texture1, TexCoord);
	}
}