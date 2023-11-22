#version 450 core
out vec4 FragColor;
in vec2 TexCoord;

uniform float Delta;

uniform vec3 ObjectColor;
uniform vec3 LightColor;

void main()
{
    FragColor = vec4(LightColor * ObjectColor, 1.0);
}