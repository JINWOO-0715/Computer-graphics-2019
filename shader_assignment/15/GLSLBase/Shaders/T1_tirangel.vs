#version 330

in vec3 in_Position; // 위치 속성
in vec3 in_Color; // 색상 속성
uniform mat4 modelTransform; 
uniform mat4 viewTransform;
uniform mat4 projectionTransform;
out vec3 ex_Color; // 프래그먼트 세이더에게 전달



void main(void)
{
	gl_Position = projectionTransform * viewTransform * modelTransform * vec4 (in_Position.x, in_Position.y, in_Position.z, 1.0);
	ex_Color = in_Color;
}