#version 330

in vec3 in_Position; // ��ġ �Ӽ�
in vec3 in_Color; // ���� �Ӽ�
uniform mat4 modelTransform; 
uniform mat4 viewTransform;
uniform mat4 projectionTransform;
out vec3 ex_Color; // �����׸�Ʈ ���̴����� ����



void main(void)
{
	gl_Position = projectionTransform * viewTransform * modelTransform * vec4 (in_Position.x, in_Position.y, in_Position.z, 1.0);
	ex_Color = in_Color;
}