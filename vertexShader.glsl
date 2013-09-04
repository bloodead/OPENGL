#version 330

in vec4 in_Position;
in vec4 in_Color;

out vec4 ex_Color;

uniform mat4 modelMatrix;
uniform mat4 modelMatrix2;
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main(void)
{
 gl_Position = projMatrix * viewMatrix * modelMatrix * modelMatrix2 *  in_Position;
 ex_Color = in_Color;
}

