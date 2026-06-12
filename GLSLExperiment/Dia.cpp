#include "Dia.h"

const GLfloat DIA_X = 0.12f, DIA_Y = 0.12f;
const int SO_PHAN_DOAN = 36;

GLuint vao_dia;
GLuint vbo_dia;

void initDiaTron(GLuint program)
{
	vec4 points[SO_PHAN_DOAN + 2];
	vec3 normals[SO_PHAN_DOAN + 2];

	// Điểm đầu tiên là Tâm của hình tròn
	points[0] = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	normals[0] = vec3(0.0f, 0.0f, 1.0f); // Pháp tuyến hướng lên trên

	// Các điểm nằm trên viền đường tròn
	for (int i = 0; i <= SO_PHAN_DOAN; i++) {
		float goc = (2.0f * 3.1415926f * i) / SO_PHAN_DOAN;
		points[i + 1] = vec4(cos(goc), sin(goc), 0.0f, 1.0f);
		normals[i + 1] = vec3(0.0f, 0.0f, 1.0f);
	}

	glGenVertexArrays(1, &vao_dia);
	glBindVertexArray(vao_dia);
	glGenBuffers(1, &vbo_dia);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_dia);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(normals), NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(normals), normals);

	// Lấy vị trí của vPosition và vNormal từ Shader để kết nối
	GLuint loc_pos = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc_pos);
	glVertexAttribPointer(loc_pos, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	GLuint loc_norm = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(loc_norm);
	glVertexAttribPointer(loc_norm, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(points));

	glBindVertexArray(0);
}

static void setMaterialDia(GLuint program, const color4& material_color)
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

static void drawBlockDia(GLuint program, GLuint model_loc, const mat4& model, const mat4& instance, const color4& material_color)
{
	setMaterialDia(program, material_color);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * instance);
	glBindVertexArray(vao_dia);
	glDrawArrays(GL_TRIANGLE_FAN, 0, SO_PHAN_DOAN + 2);
	glBindVertexArray(0);
}

void veMotDia(GLuint program, GLuint model_loc, mat4 matrix_phancap, const color4& mau)
{
	mat4 instance = Scale(DIA_X, DIA_Y, 1.0f);
	drawBlockDia(program, model_loc, matrix_phancap, instance, mau);
}

//Vẽ đĩa
void veDia(GLuint program, GLuint model_loc, const mat4& model_ban, float z_matban_top)
{
	color4 mauDia(1.0f, 1.0f, 1.0f, 1.0f); // Màu trắng

	float z_dia = z_matban_top + 0.001f;

	// 4 đĩa cá nhân
	mat4 model_dia1 = model_ban * Translate(-0.3f, -0.2f, z_dia);
	veMotDia(program, model_loc, model_dia1, mauDia);

	mat4 model_dia2 = model_ban * Translate(-0.3f, 0.2f, z_dia);
	veMotDia(program, model_loc, model_dia2, mauDia);

	mat4 model_dia3 = model_ban * Translate(0.3f, -0.2f, z_dia);
	veMotDia(program, model_loc, model_dia3, mauDia);

	mat4 model_dia4 = model_ban * Translate(0.3f, 0.2f, z_dia);
	veMotDia(program, model_loc, model_dia4, mauDia);
}