#version 440
out vec4 FragColor;

in vec3 vertexDefinedColor;

uniform int fill;

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
	// Vertex Defined Colors
	else 
	{
		FragColor = vec4(vertexDefinedColor, 1.0f);
	}

}