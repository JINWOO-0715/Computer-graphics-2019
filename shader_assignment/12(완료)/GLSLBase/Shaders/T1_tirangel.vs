#version 330

in vec3 in_Position; // ��ġ �Ӽ�
in vec3 in_Color; // ���� �Ӽ�
uniform mat4 modelTransform; 
out vec3 ex_Color; // �����׸�Ʈ ���̴����� ����

uniform mat4 transform;

void main(void)
{
	gl_Position = modelTransform * vec4 (in_Position.x, in_Position.y, in_Position.z, 1.0);
	ex_Color = in_Color;
}