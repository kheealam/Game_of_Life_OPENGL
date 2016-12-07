#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 offset;
layout (location = 2) in int isAlive;

out vec4 Color;

void main(){

	gl_Position = vec4(position.x+offset.x,position.y+offset.y,-0.51f,1.0f);
	Color=vec4(float(isAlive),float(isAlive),float(isAlive),1.0);
};