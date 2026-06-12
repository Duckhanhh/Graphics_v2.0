#include "Lap_phuong.h"
#include "Den.h"

typedef vec4 color4;
extern bool isLightOn;
extern void setDefaultMaterial();

void veBongDen(GLuint program, GLuint model_loc, const mat4& model_goc) {
	// Nếu đèn bật thì màu trắng sáng, tắt thì màu xám tối
	color4 mauDen = isLightOn ? color4(0.95f, 0.95f, 0.9f, 1.0f) : color4(0.3f, 0.3f, 0.3f, 1.0f);

	// Thiết lập vật liệu phát quang riêng cho hệ thống đèn
	color4 ambient_product = mauDen * (isLightOn ? 1.0f : 0.4f);
	color4 diffuse_product = mauDen;
	color4 specular_product = color4(1.0f, 1.0f, 1.0f, 1.0f);

	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular_product);
	glUniform1f(glGetUniformLocation(program, "Shininess"), 100.0f);

	GLfloat rong_den = 0.05f, cao_den = 0.04f;
	GLfloat vi_tri_z = 3.16f;


	GLfloat chieu_dai_x = 3.0f;
	GLfloat chieu_rong_y = 2.0f;

	GLfloat offset_x = chieu_dai_x / 2.0f; 
	GLfloat offset_y = chieu_rong_y / 2.0f; 

	mat4 canhTren = model_goc * Translate(0.0f, offset_y, vi_tri_z) * Scale(chieu_dai_x, rong_den, cao_den);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, canhTren);
	drawLapPhuong();

	mat4 canhDuoi = model_goc * Translate(0.0f, -offset_y, vi_tri_z) * Scale(chieu_dai_x, rong_den, cao_den);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, canhDuoi);
	drawLapPhuong();

	mat4 canhTrai = model_goc * Translate(-offset_x, 0.0f, vi_tri_z) * Scale(rong_den, chieu_rong_y, cao_den);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, canhTrai);
	drawLapPhuong();

	mat4 canhPhai = model_goc * Translate(offset_x, 0.0f, vi_tri_z) * Scale(rong_den, chieu_rong_y, cao_den);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, canhPhai);
	drawLapPhuong();

	setDefaultMaterial();
}