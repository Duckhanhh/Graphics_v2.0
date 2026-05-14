#pragma once
#include "Angel.h"

extern vec4 points[36];
extern vec4 colors[36];
extern vec4 vertices[8];
extern vec4 vertex_colors[8];

void initCube();
void makeColorCube();
void generateGeometry();
void LapPhuong_Init(unsigned int vao);
void LapPhuong_Draw(unsigned int vao, const Angel::mat4& model);