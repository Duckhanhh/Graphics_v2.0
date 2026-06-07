#include "Cua_so.h"
#include "Lap_phuong.h"

typedef vec4 color4;

// Biến trạng thái lưu độ trượt của cửa (trượt theo trục X)
static float do_truot_cua_so = 0.0f;

// Hàm thiết lập vật liệu (copy style từ Tu_lanh.cpp)
static void setMaterialCuaSo(GLuint program, const color4& material_color) {
	color4 light_ambient(0.2f, 0.2f, 0.2f, 1.0f);
	color4 light_diffuse(1.0f, 1.0f, 1.0f, 1.0f);
	color4 light_specular(1.0f, 1.0f, 1.0f, 1.0f);
	color4 material_specular(0.5f, 0.5f, 0.5f, 1.0f);

	color4 ambient_product = light_ambient * material_color;
	color4 diffuse_product = light_diffuse * material_color;
	color4 specular_product = light_specular * material_specular;

	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular_product);
	glUniform1f(glGetUniformLocation(program, "Shininess"), 80.0f);
}

// Hàm vẽ khối cơ bản có áp dụng ma trận (copy style từ Tu_lanh.cpp)
static void drawBlockCuaSo(GLuint program, GLuint model_loc, const mat4& model, const mat4& instance, const color4& material_color) {
	setMaterialCuaSo(program, material_color);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * instance);
	drawLapPhuong();
}

// --- CÁC HÀM XỬ LÝ LOGIC ---
void moCuaSo(void) {
	// Giới hạn độ trượt tối đa để cửa không bay ra khỏi khung
	if (do_truot_cua_so < 0.45f) {
		do_truot_cua_so += 0.05f;
	}
}

void dongCuaSo(void) {
	if (do_truot_cua_so > 0.1f) {
		do_truot_cua_so -= 0.05f;
	}
}

// --- CÁC HÀM VẼ THÀNH PHẦN ---
void drawKhungCuaSo(GLuint program, GLuint model_loc, const mat4& model) {
	color4 mauKhung(0.4f, 0.2f, 0.0f, 1.0f); // Màu nâu gỗ

	// Thanh ngang trên
	mat4 instance1 = Translate(0.0f, 0.5f, 0.0f) * Scale(1.0f, 0.05f, 0.1f);
	drawBlockCuaSo(program, model_loc, model, instance1, mauKhung);

	// Thanh ngang dưới
	mat4 instance2 = Translate(0.0f, -0.5f, 0.0f) * Scale(1.0f, 0.05f, 0.1f);
	drawBlockCuaSo(program, model_loc, model, instance2, mauKhung);

	// Thanh dọc trái
	mat4 instance3 = Translate(-0.475f, 0.0f, 0.0f) * Scale(0.05f, 1.0f, 0.1f);
	drawBlockCuaSo(program, model_loc, model, instance3, mauKhung);

	// Thanh dọc phải
	mat4 instance4 = Translate(0.475f, 0.0f, 0.0f) * Scale(0.05f, 1.0f, 0.1f);
	drawBlockCuaSo(program, model_loc, model, instance4, mauKhung);
}

void drawCanhCuaTrai(GLuint program, GLuint model_loc, const mat4& model) {
	// Cánh trái nằm ở rãnh phía trước (z = +0.02)
	color4 mauVien(0.9f, 0.9f, 0.9f, 1.0f);     // Màu trắng nhôm kính
	color4 mauKinh(0.6f, 0.8f, 0.9f, 0.8f);     // Màu kính (xanh nhạt)

	// Viền cánh cửa
	mat4 instanceVien = Translate(0.0f, 0.0f, 0.02f) * Scale(0.48f, 0.95f, 0.04f);
	drawBlockCuaSo(program, model_loc, model, instanceVien, mauVien);

	// Tấm kính (nhô ra trước một chút xíu để đè lên viền, hoặc làm lọt lòng)
	mat4 instanceKinh = Translate(0.0f, 0.0f, 0.025f) * Scale(0.42f, 0.85f, 0.045f);
	drawBlockCuaSo(program, model_loc, model, instanceKinh, mauKinh);
}

void drawCanhCuaPhai(GLuint program, GLuint model_loc, const mat4& model) {
	// Cánh phải nằm ở rãnh phía sau (z = -0.02) cố định
	color4 mauVien(0.9f, 0.9f, 0.9f, 1.0f);
	color4 mauKinh(0.6f, 0.8f, 0.9f, 0.8f);

	// Viền cánh cửa
	mat4 instanceVien = Translate(0.0f, 0.0f, -0.02f) * Scale(0.48f, 0.95f, 0.04f);
	drawBlockCuaSo(program, model_loc, model, instanceVien, mauVien);

	// Tấm kính
	mat4 instanceKinh = Translate(0.0f, 0.0f, -0.015f) * Scale(0.42f, 0.85f, 0.045f);
	drawBlockCuaSo(program, model_loc, model, instanceKinh, mauKinh);
}

// --- HÀM TỔNG HỢP ---
void drawCuaSo(GLuint program, GLuint model_loc, const mat4& model) {
	// 1. Vẽ khung cố định
	drawKhungCuaSo(program, model_loc, model);

	// 2. Vẽ cánh phải cố định
	mat4 modelCanhPhai = model * Translate(0.24f, 0.0f, 0.0f);
	drawCanhCuaPhai(program, model_loc, modelCanhPhai);

	// 3. Vẽ cánh trái (CÓ TRƯỢT SANG NGANG)
	// Áp dụng biến do_truot_cua_so vào ma trận tịnh tiến
	mat4 modelCanhTrai = model * Translate(-0.24f + do_truot_cua_so, 0.0f, 0.0f);
	drawCanhCuaTrai(program, model_loc, modelCanhTrai);
}