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
	// Kich thuoc: 0.2 x 4.4 x 3.4  |  Tam: (-2.6, 0.0, 1.7)
	mat4 instance = Translate(-2.6f, 0.0f, 1.7f)
		* Scale(0.2f, 4.4f, 3.4f);
	drawBlock(program, model_loc, model, instance, color4(155 / 255.0f, 158 / 255.0f, 155 / 255.0f, 1.0f));
}

void tuongBenTrai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 0.2 x 4.4 x 3.4  |  Tam: (2.6, 0.0, 1.7)
	mat4 instance = Translate(2.6f, 0.0f, 1.7f)
		* Scale(0.2f, 4.4f, 3.4f);
	drawBlock(program, model_loc, model, instance, color4(155 / 255.0f, 158 / 255.0f, 155 / 255.0f, 1.0f));
}

void sanNha(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 5.4 x 4.4 x 0.2  |  Tam: (0.0, 0.0, -0.1)
	mat4 instance = Translate(0.0f, 0.0f, -0.1f)
		* Scale(5.4f, 4.4f, 0.2f);
	drawBlock(program, model_loc, model, instance, color4(155 / 255.0f, 158 / 255.0f, 155 / 255.0f, 1.0f));
}

void tranNha(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 5.0 x 4.0 x 0.2  |  Tam: (0.0, 0.0, 3.3)
	mat4 instance = Translate(0.0f, 0.0f, 3.3f)
		* Scale(5.0f, 4.0f, 0.2f);
	drawBlock(program, model_loc, model, instance, color4(155 / 255.0f, 158 / 255.0f, 155 / 255.0f, 1.0f));
}

void tuongCuaVaoBenTrai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 3.5 x 0.2 x 3.4  |  Tam: (-0.75, -2.1, 1.7)
	mat4 instance = Translate(-0.75f, -2.1f, 1.7f)
		* Scale(3.5f, 0.2f, 3.4f);
	drawBlock(program, model_loc, model, instance, color4(155 / 255.0f, 158 / 255.0f, 155 / 255.0f, 1.0f));
}

void tuongCuaVaoBenTren(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 1.0 x 0.2 x 1.0  |  Tam: (1.5, -2.1, 2.9)
	mat4 instance = Translate(1.5f, -2.1f, 2.9f)
		* Scale(1.0f, 0.2f, 1.0f);
	drawBlock(program, model_loc, model, instance, color4(155 / 255.0f, 158 / 255.0f, 155 / 255.0f, 1.0f));
}

void tuongCuaVaoBenPhai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 0.5 x 0.2 x 3.4  |  Tam: (2.25, -2.1, 1.7)
	mat4 instance = Translate(2.25f, -2.1f, 1.7f)
		* Scale(0.5f, 0.2f, 3.4f);
	drawBlock(program, model_loc, model, instance, color4(155 / 255.0f, 158 / 255.0f, 155 / 255.0f, 1.0f));
}

void tuongCuaSoBenTrai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 1.8 x 0.2 x 3.4  |  Tam: (-1.6, 2.1, 1.7)
	mat4 instance = Translate(-1.6f, 2.1f, 1.7f)
		* Scale(1.8f, 0.2f, 3.4f);
	drawBlock(program, model_loc, model, instance, color4(155 / 255.0f, 158 / 255.0f, 155 / 255.0f, 1.0f));
}

void tuongCuaSoBenDuoi(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 1.4 x 0.2 x 1.0  |  Tam: (0.0, 2.1, 0.5)
	mat4 instance = Translate(0.0f, 2.1f, 0.5f)
		* Scale(1.4f, 0.2f, 1.0f);
	drawBlock(program, model_loc, model, instance, color4(155 / 255.0f, 158 / 255.0f, 155 / 255.0f, 1.0f));
}

void tuongCuaSoBenTren(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 1.4 x 0.2 x 1.0  |  Tam: (0.0, 2.1, 2.9)
	mat4 instance = Translate(0.0f, 2.1f, 2.9f)
		* Scale(1.4f, 0.2f, 1.0f);
	drawBlock(program, model_loc, model, instance, color4(155 / 255.0f, 158 / 255.0f, 155 / 255.0f, 1.0f));
}

void tuongCuaSoBenPhai(GLuint program, GLuint model_loc, const mat4& model)
{
	// Kich thuoc: 1.8 x 0.2 x 3.4  |  Tam: (1.6, 2.1, 1.7)
	mat4 instance = Translate(1.6f, 2.1f, 1.7f)
		* Scale(1.8f, 0.2f, 3.4f);
	drawBlock(program, model_loc, model, instance, color4(155 / 255.0f, 158 / 255.0f, 155 / 255.0f, 1.0f));
}
void drawTuongPhong(GLuint program, GLuint model_loc, const mat4& model)
{
	tuongBenPhai(program, model_loc, model);
	tuongBenTrai(program, model_loc, model);
	sanNha(program, model_loc, model);
	tranNha(program, model_loc, model);
	tuongCuaVaoBenTrai(program, model_loc, model);
	tuongCuaVaoBenTren(program, model_loc, model);
	tuongCuaVaoBenPhai(program, model_loc, model);
	tuongCuaSoBenTrai(program, model_loc, model);
	tuongCuaSoBenDuoi(program, model_loc, model);
	tuongCuaSoBenTren(program, model_loc, model);
	tuongCuaSoBenPhai(program, model_loc, model);
}
