#version 330
out vec4 FragColor;

in vec2 v_TexCoord;

uniform int fill;
uniform sampler2D u_Texture;

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
	// Grey
	else if (fill == 2)
	{
		FragColor = vec4(0.75f, 0.75f, 0.75f, 1.0f);
	}
	// Purple
	else if (fill == 3)
	{
		FragColor = vec4(0.6f, 0.0f, 0.8f, 1.0f);
	}
	else if (fill == 4)
	{
		vec4 texColor = texture(u_Texture, v_TexCoord);
		FragColor = texColor;
	}
	// Vertex Defined Colors


}