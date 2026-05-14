#ifndef TUONG_PHONG_H
#define TUONG_PHONG_H

// Tuong_phong.h
// Vẽ tường/sàn/trần căn phòng
// Mỗi khối = cube đơn vị được Scale + Translate, màu ghi thẳng vào VBO riêng
// KHÔNG chứa main

#include "Angel.h"

// Khởi tạo VAO/VBO cho tất cả khối tường — gọi 1 lần sau LapPhuong_Init
void TuongPhong_Init(GLuint program);

// Vẽ toàn bộ tường/sàn/trần
void TuongPhong_Draw(GLuint program);

#endif // TUONG_PHONG_H