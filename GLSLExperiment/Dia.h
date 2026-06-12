#pragma once
// Thay "Angel.h" bằng file thư viện tổng mà bạn đang dùng trong project
#include "Angel.h" 

typedef vec4 color4;

// Hàm tạo dữ liệu đỉnh cho hình tròn (Gọi 1 lần duy nhất lúc khởi tạo)
void initDiaTron(GLuint program);

// Hàm sắp xếp các đĩa lên bàn
void veDia(GLuint program, GLuint model_loc, const mat4& model_goc_ban, float z_matban_top);