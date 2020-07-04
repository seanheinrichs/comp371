// Shader code taken from LearnOpenGl.com (will likely be heavily changed so we can delete this comment)

#version 440
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;


// TODO: Remove textures and use colors as specified in A1.
// It's currently a texture because it's easier to see than a solid color
void main()
{
	FragColor = texture(texture1, TexCoord);
}