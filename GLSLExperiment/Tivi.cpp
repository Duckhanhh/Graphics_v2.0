#include "Tuong_phong.h"
#include "Lap_phuong.h"

typedef vec4 color4;
extern bool isLightOn;
extern float lightIntensity;

static void setMaterial(GLuint program, const color4& material_color)
{
	float intensity = isLightOn ? lightIntensity : 0.0f;
	float ambient_intensity = isLightOn ? (0.2f * lightIntensity) : 0.05f;

	color4 light_ambient(ambient_intensity, ambient_intensity, ambient_intensity, 1.0f);
	color4 light_diffuse(1.0f * intensity, 1.0f * intensity, 1.0f * intensity, 1.0f);
	color4 light_specular(1.0f * intensity, 1.0f * intensity, 1.0f * intensity, 1.0f);
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

const GLfloat RONG_KE = 2.5f;   
const GLfloat CAO_KE = 0.2f;
const GLfloat SAU_KE = 0.3f;

const GLfloat RONG_TV = 1.44f;   
const GLfloat CAO_TV = 0.81f;  
const GLfloat SAU_TV = 0.05f;

const GLfloat CAO_STAND = 0.15f;
const GLfloat RONG_STAND = 0.6f;
const GLfloat SAU_STAND = 0.2f;

const GLfloat RONG_DK = 0.05f;
const GLfloat CAO_DK = 0.015f;
const GLfloat SAU_DK = 0.15f;

const GLfloat RONG_NUT = 0.02f;
const GLfloat CAO_NUT = 0.005f;
const GLfloat SAU_NUT = 0.02f;

void veKhoiTivi(GLuint program, GLuint model_loc, mat4 matrix, GLfloat sx, GLfloat sy, GLfloat sz, const color4& mau)
{
	mat4 instance = Scale(sx, sy, sz);
	drawBlock(program, model_loc, matrix, instance, mau);
}

extern bool isTvOn;
void veTiviVaKe(GLuint program, GLuint model_loc, const mat4& model_goc)
{
	const color4 mauKe(210 / 255.0f, 140 / 255.0f, 70 / 255.0f, 1.0f);  // Màu kệ
	const color4 mauTvOff(10 / 255.0f, 10 / 255.0f, 15 / 255.0f, 1.0f); // Màu tivi khi tắt + viền
	const color4 mauTvOn(100 / 255.0f, 200 / 255.0f, 255 / 255.0f, 1.0f); // Màu tivi khi bật
	
	//Kệ gỗ
	mat4 ke = model_goc * Translate(0.0f, CAO_KE / 2.0f, 0.0f);
	veKhoiTivi(program, model_loc, ke, RONG_KE, CAO_KE, SAU_KE, mauKe);

	//Chân đế tivi
	mat4 de = ke * Translate(0.0f, CAO_KE / 2.0f + CAO_STAND / 2.0f, 0.0f);
	veKhoiTivi(program, model_loc, de, RONG_STAND, CAO_STAND, SAU_STAND, mauTvOff);

	GLfloat VIEN_DAY = 0.02f; // Độ dày của viền tivi (3cm)
	GLfloat RONG_MAN_HINH = RONG_TV - 2 * VIEN_DAY;
	GLfloat CAO_MAN_HINH = CAO_TV - 2 * VIEN_DAY;
	GLfloat SAU_MAN_HINH = SAU_TV + 0.002f; // Màn hình rất mỏng
	//Màn hình tivi
	mat4 khung = de * Translate(0.0f, CAO_STAND / 2.0f + CAO_TV / 2.0f, 0.0f);
	veKhoiTivi(program, model_loc, khung, RONG_TV, CAO_TV, SAU_TV, mauTvOff);
	//mat4 man = ke * Translate(0.0f, 0.0f, SAU_TV / 2.0f + SAU_MAN_HINH / 2.0f);
	color4 mauTv = isTvOn ? mauTvOn : mauTvOff;
	veKhoiTivi(program, model_loc, khung, RONG_MAN_HINH, CAO_MAN_HINH, SAU_MAN_HINH, mauTv);
}

void veDieuKhien(GLuint program, GLuint model_loc, const mat4& model_goc)
{
	const color4 mauDieuKhien(0.2f, 0.2f, 0.2f, 1.0f);
	const color4 mauNutNguon(0.8f, 0.1f, 0.1f, 1.0f);
	
	//Điều khiển
	mat4 than = model_goc * Translate(0.0f, CAO_DK / 2.0f, 0.0f);
	veKhoiTivi(program, model_loc, than, RONG_DK, CAO_DK, SAU_DK, mauDieuKhien);

	//Nút nguồn
	mat4 nut = than * Translate(0.0f, CAO_DK / 2.0f + CAO_NUT / 2.0f, -SAU_DK / 2.0f + 0.03f);
	veKhoiTivi(program, model_loc, nut, RONG_NUT, CAO_NUT, SAU_NUT, mauNutNguon);
}