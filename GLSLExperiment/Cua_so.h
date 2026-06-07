#ifndef CUA_SO_H
#define CUA_SO_H

#include "Angel.h"

// Các hàm tương tác mở/đóng cửa sổ
void moCuaSo(void);
void dongCuaSo(void);

// Hàm vẽ chính
void drawCuaSo(GLuint program, GLuint model_loc, const mat4& model);

#endif