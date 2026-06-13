#ifndef TU_BAT_H
#define TU_BAT_H

#include "Angel.h"

// Hàm vẽ tủ bát phân cấp
void drawTuBatModel(GLuint program, GLuint model_loc, const mat4& model);
void drawKhungTuBat1(GLuint program, GLuint model_loc, const mat4& model);
void drawKhungTuBat2(GLuint program, GLuint model_loc, const mat4& model);
void drawCanhTuBat1(GLuint program, GLuint model_loc, const mat4& model);
void drawCanhTuBat2(GLuint program, GLuint model_loc, const mat4& model);
void drawMayHutMuiChuan(GLuint program, GLuint model_loc, const mat4& model);
void drawOngThongGioGiauKinh(GLuint program, GLuint model_loc, const mat4& model);

// Control
void moCanhTraiTu1();
void dongCanhTraiTu1();
void moCanhPhaiTu1();
void dongCanhPhaiTu1();

void moCanhTu2();
void dongCanhTu2();

void batTatMayHutMui();
void batTatDenHutMui();

// State
extern float moCuaTraiTu1;
extern float moCuaPhaiTu1;
extern float moCuaTu2;

extern bool batMayHutMui;
extern bool batDenHutMui;

extern int tocDoQuat;

#endif
