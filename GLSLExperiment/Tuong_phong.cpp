#include "Tuong_phong.h"
#include "Lap_phuong.h"

typedef vec4 color4;

static void setMaterial(GLuint program, const color4& material_color)
{
	color4 light_ambient(0.2f, 0.2f, 0.2f, 1.0f);
	color4 light_diffuse(1.0f, 1.0f, 1.0f, 1.0f);
	color4 light_specular(1.0f, 1.0f, 1.0f, 1.0f);
	color4 material_specular(0.2f, 0.2f, 0.2f, 1.0f);

	color4 ambient_product = light_ambient * material_color;
	color4 diffuse_product = light_diffuse * material_color;
	color4 specular_product = light_specular * material_specular;

	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular_product);
	glUniform1f(glGetUniformLocation(program, "Shininess"), 50.0f);
}

static void drawBlock(GLuint program, GLuint model_loc, const mat4& model, const mat4& instance, const color4& material_color)
{
	setMaterial(program, material_color);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * instance);
	drawLapPhuong();
}

void tuongBenPhai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 0.2 x 4.4 x 3.4  |  Tam: (-0.1, 2.2, 1.6)
	mat4 instance = Translate(-0.1f, 2.2f, 1.6f)
		* Scale(0.2f, 4.4f, 3.4f);
	drawBlock(program, model_loc, model, instance, color4(170 / 255.0f, 90 / 255.0f, 80 / 255.0f, 1.0f));
}

void tuongBenTrai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 0.2 x 4.4 x 3.4  |  Tam: (5.1, 2.2, 1.6)
	mat4 instance = Translate(5.1f, 2.2f, 1.6f)
		* Scale(0.2f, 4.4f, 3.4f);
	drawBlock(program, model_loc, model, instance, color4(170 / 255.0f, 90 / 255.0f, 80 / 255.0f, 1.0f));
}

void sanNha(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 5.4 x 4.4 x 0.2  |  Tam: (2.5, 2.2, -0.2)
	mat4 instance = Translate(2.5f, 2.2f, -0.2f)
		* Scale(5.4f, 4.4f, 0.2f);
	drawBlock(program, model_loc, model, instance, color4(120 / 255.0f, 85 / 255.0f, 60 / 255.0f, 1.0f));
}

void tranNha(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 5.0 x 4.0 x 0.2  |  Tam: (2.5, 2.2, 3.2)
	mat4 instance = Translate(2.5f, 2.2f, 3.2f)
		* Scale(5.0f, 4.0f, 0.2f);
	drawBlock(program, model_loc, model, instance, color4(190 / 255.0f, 170 / 255.0f, 145 / 255.0f, 1.0f));
}

void tuongCuaVaoBenTrai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 3.5 x 0.2 x 3.4  |  Tam: (1.75, 0.1, 1.6)
	mat4 instance = Translate(1.75f, 0.1f, 1.6f)
		* Scale(3.5f, 0.2f, 3.4f);
	drawBlock(program, model_loc, model, instance, color4(190 / 255.0f, 170 / 255.0f, 145 / 255.0f, 1.0f));
}

void tuongCuaVaoBenTren(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 1.0 x 0.2 x 1.0  |  Tam: (4.0, 0.1, 2.8)
	mat4 instance = Translate(4.0f, 0.1f, 2.8f)
		* Scale(1.0f, 0.2f, 1.0f);
	drawBlock(program, model_loc, model, instance, color4(190 / 255.0f, 170 / 255.0f, 145 / 255.0f, 1.0f));
}

void tuongCuaVaoBenPhai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 0.5 x 0.2 x 3.4  |  Tam: (4.75, 0.1, 1.6)
	mat4 instance = Translate(4.75f, 0.1f, 1.6f)
		* Scale(0.5f, 0.2f, 3.4f);
	drawBlock(program, model_loc, model, instance, color4(190 / 255.0f, 170 / 255.0f, 145 / 255.0f, 1.0f));
}

void tuongCuaSoBenTrai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 1.8 x 0.2 x 3.4  |  Tam: (0.9, 4.3, 1.6)
	mat4 instance = Translate(0.9f, 4.3f, 1.6f)
		* Scale(1.8f, 0.2f, 3.4f);
	drawBlock(program, model_loc, model, instance, color4(145 / 255.0f, 158 / 255.0f, 135 / 255.0f, 1.0f));
}

void tuongCuaSoBenDuoi(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 1.4 x 0.2 x 1.0  |  Tam: (2.5, 4.3, 0.4)
	mat4 instance = Translate(2.5f, 4.3f, 0.4f)
		* Scale(1.4f, 0.2f, 1.0f);
	drawBlock(program, model_loc, model, instance, color4(145 / 255.0f, 158 / 255.0f, 135 / 255.0f, 1.0f));
}

void tuongCuaSoBenTren(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 1.4 x 0.2 x 1.0  |  Tam: (2.5, 4.3, 2.8)
	mat4 instance = Translate(2.5f, 4.3f, 2.8f)
		* Scale(1.4f, 0.2f, 1.0f);
	drawBlock(program, model_loc, model, instance, color4(145 / 255.0f, 158 / 255.0f, 135 / 255.0f, 1.0f));
}

void tuongCuaSoBenPhai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 1.8 x 0.2 x 3.4  |  Tam: (4.1, 4.3, 1.6)
	mat4 instance = Translate(4.1f, 4.3f, 1.6f)
		* Scale(1.8f, 0.2f, 3.4f);
	drawBlock(program, model_loc, model, instance, color4(145 / 255.0f, 158 / 255.0f, 135 / 255.0f, 1.0f));
}


void sanNhaTong(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 13.0 x 10.0 x 0.2  |  Tam: (6.5, 5.0, -0.3)
	mat4 instance = Translate(6.5f, 5.0f, -0.3f)
		* Scale(13.0f, 10.0f, 0.2f);
	drawBlock(program, model_loc, model, instance, color4(0.62f, 0.62f, 0.62f, 1.0f));
}

void tranNhaTong(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 13.0 x 10.0 x 0.2  |  Tam: (6.5, 5.0, 3.8)
	mat4 instance = Translate(6.5f, 5.0f, 3.8f)
		* Scale(13.0f, 10.0f, 0.2f);
	drawBlock(program, model_loc, model, instance, color4(0.78f, 0.78f, 0.78f, 1.0f));
}

void tuongNgoaiTrai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 0.2 x 10.0 x 3.8  |  Tam: (-0.1, 5.0, 1.75)
	mat4 instance = Translate(-0.1f, 5.0f, 1.75f)
		* Scale(0.2f, 10.0f, 3.8f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void tuongNgoaiPhai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 0.2 x 10.0 x 3.8  |  Tam: (13.1, 5.0, 1.75)
	mat4 instance = Translate(13.1f, 5.0f, 1.75f)
		* Scale(0.2f, 10.0f, 3.8f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void tuongNgoaiSau(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 13.0 x 0.2 x 3.8  |  Tam: (6.5, 10.1, 1.75)
	mat4 instance = Translate(6.5f, 10.1f, 1.75f)
		* Scale(13.0f, 0.2f, 3.8f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void tuongNgoaiTruocTraiCua(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 5.1 x 0.2 x 3.8  |  Tam: (2.55, -0.1, 1.75)
	mat4 instance = Translate(2.55f, -0.1f, 1.75f)
		* Scale(5.1f, 0.2f, 3.8f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void tuongNgoaiTruocPhaiCua(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 5.9 x 0.2 x 3.8  |  Tam: (10.05, -0.1, 1.75)
	mat4 instance = Translate(10.05f, -0.1f, 1.75f)
		* Scale(5.9f, 0.2f, 3.8f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void tuongNgoaiTruocTrenCua(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 1.9 x 0.2 x 1.2  |  Tam: (6.05, -0.1, 3.2)
	mat4 instance = Translate(6.05f, -0.1f, 3.2f)
		* Scale(1.9f, 0.2f, 1.2f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void cotCuaChinhTrai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 0.25 x 0.5 x 2.4  |  Tam: (5.1, 0.15, 1.2)
	mat4 instance = Translate(5.1f, 0.15f, 1.2f)
		* Scale(0.25f, 0.5f, 2.4f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void cotCuaChinhPhai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 0.25 x 0.5 x 2.4  |  Tam: (7.0, 0.15, 1.2)
	mat4 instance = Translate(7.0f, 0.15f, 1.2f)
		* Scale(0.25f, 0.5f, 2.4f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void thanhGiangCuaChinh(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 1.9 x 0.2 x 0.35  |  Tam: (6.05, 0.35, 2.55)
	mat4 instance = Translate(6.05f, 0.35f, 2.55f)
		* Scale(1.9f, 0.2f, 0.35f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void vachTraiPhongTruocDoanTruoc(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 0.2 x 1.8 x 3.3  |  Tam: (5.0, 0.9, 1.65)
	mat4 instance = Translate(5.0f, 0.9f, 1.65f)
		* Scale(0.2f, 1.8f, 3.3f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void vachTraiPhongTruocDoanSau(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 0.2 x 1.8 x 3.3  |  Tam: (5.0, 3.7, 1.65)
	mat4 instance = Translate(5.0f, 3.7f, 1.65f)
		* Scale(0.2f, 1.8f, 3.3f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void vachNgangPhongTruocTrai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 5.0 x 0.2 x 3.3  |  Tam: (2.5, 4.5, 1.65)
	mat4 instance = Translate(2.5f, 4.5f, 1.65f)
		* Scale(5.0f, 0.2f, 3.3f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void vachPhaiKhuBep(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 0.2 x 3.8 x 3.3  |  Tam: (4.9, 7.3, 1.65)
	mat4 instance = Translate(4.9f, 7.3f, 1.65f)
		* Scale(0.2f, 3.8f, 3.3f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void vachTrenPhongGiua(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 0.2 x 4.0 x 3.3  |  Tam: (6.4, 8.0, 1.65)
	mat4 instance = Translate(6.4f, 8.0f, 1.65f)
		* Scale(0.2f, 4.0f, 3.3f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void vachNgangPhongSauPhai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 6.8 x 0.2 x 3.3  |  Tam: (9.6, 6.2, 1.65)
	mat4 instance = Translate(9.6f, 6.2f, 1.65f)
		* Scale(6.8f, 0.2f, 3.3f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void vachPhaiDoanTruocCuaPhong(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 0.2 x 2.0 x 3.3  |  Tam: (7.2, 1.0, 1.65)
	mat4 instance = Translate(7.2f, 1.0f, 1.65f)
		* Scale(0.2f, 2.0f, 3.3f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void vachPhaiDoanSauCuaPhong(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 0.2 x 1.8 x 3.3  |  Tam: (7.2, 4.1, 1.65)
	mat4 instance = Translate(7.2f, 4.1f, 1.65f)
		* Scale(0.2f, 1.8f, 3.3f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void vachNgangGiuaPhai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 5.4 x 0.2 x 3.3  |  Tam: (9.9, 3.5, 1.65)
	mat4 instance = Translate(9.9f, 3.5f, 1.65f)
		* Scale(5.4f, 0.2f, 3.3f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void vachNgangSauGiuaDoanTrai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 1.6 x 0.2 x 3.3  |  Tam: (7.4, 6.2, 1.65)
	mat4 instance = Translate(7.4f, 6.2f, 1.65f)
		* Scale(1.6f, 0.2f, 3.3f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void vachNgangSauGiuaDoanPhai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 4.0 x 0.2 x 3.3  |  Tam: (11.0, 6.2, 1.65)
	mat4 instance = Translate(11.0f, 6.2f, 1.65f)
		* Scale(4.0f, 0.2f, 3.3f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void vachDungPhongPhai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 0.2 x 2.4 x 3.3  |  Tam: (7.2, 7.9, 1.65)
	mat4 instance = Translate(7.2f, 7.9f, 1.65f)
		* Scale(0.2f, 2.4f, 3.3f);
	drawBlock(program, model_loc, model, instance, color4(0.82f, 0.80f, 0.76f, 1.0f));
}

void drawKhungNha(GLuint program, GLuint model_loc, const mat4& model)
{
	sanNhaTong(program, model_loc, model);
	tranNhaTong(program, model_loc, model);
	tuongNgoaiTrai(program, model_loc, model);
	tuongNgoaiPhai(program, model_loc, model);
	tuongNgoaiSau(program, model_loc, model);
	tuongNgoaiTruocTraiCua(program, model_loc, model);
	tuongNgoaiTruocPhaiCua(program, model_loc, model);
	tuongNgoaiTruocTrenCua(program, model_loc, model);
	cotCuaChinhTrai(program, model_loc, model);
	cotCuaChinhPhai(program, model_loc, model);
	thanhGiangCuaChinh(program, model_loc, model);
	vachTraiPhongTruocDoanTruoc(program, model_loc, model);
	vachTraiPhongTruocDoanSau(program, model_loc, model);
	vachNgangPhongTruocTrai(program, model_loc, model);
	vachNgangPhongSauPhai(program, model_loc, model);
	vachPhaiDoanTruocCuaPhong(program, model_loc, model);
	vachPhaiDoanSauCuaPhong(program, model_loc, model);
	vachNgangGiuaPhai(program, model_loc, model);
	vachNgangSauGiuaDoanTrai(program, model_loc, model);
	vachNgangSauGiuaDoanPhai(program, model_loc, model);
	vachDungPhongPhai(program, model_loc, model);
}
void drawTuongPhong(GLuint program, GLuint model_loc, const mat4& model)
{
	drawKhungNha(program, model_loc, model);

	mat4 phongBep = model * Translate(4.7f, 4.8f, 0.0f) * RotateZ(90.0f);
	tuongBenPhai(program, model_loc, phongBep);
	tuongBenTrai(program, model_loc, phongBep);
	sanNha(program, model_loc, phongBep);
	tranNha(program, model_loc, phongBep);
	tuongCuaVaoBenTrai(program, model_loc, phongBep);
	tuongCuaVaoBenTren(program, model_loc, phongBep);
	tuongCuaVaoBenPhai(program, model_loc, phongBep);
	tuongCuaSoBenTrai(program, model_loc, phongBep);
	tuongCuaSoBenDuoi(program, model_loc, phongBep);
	tuongCuaSoBenTren(program, model_loc, phongBep);
	tuongCuaSoBenPhai(program, model_loc, phongBep);
}

