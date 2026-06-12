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

// Kích thước của bàn
const GLfloat MAT_X = 1.0f, MAT_Y = 0.75f, MAT_Z = 0.05f;  // Mặt bàn
const GLfloat CHAN_X = 0.06f, CHAN_Y = 0.06f, CHAN_Z = 0.7f;   // Chân bàn
const GLfloat NGAN_X = 0.85f, NGAN_Y = 0.6f, NGAN_Z = 0.03f;  // Ngăn bàn

void veMatBan(GLuint program, GLuint model_loc, mat4 matrix_phancap, const color4& mau)
{
	mat4 instance = Scale(MAT_X, MAT_Y, MAT_Z);
	drawBlock(program, model_loc, matrix_phancap, instance, mau);
}

void veNganBan(GLuint program, GLuint model_loc, mat4 matrix_phancap, const color4& mau)
{
	mat4 instance = Scale(NGAN_X, NGAN_Y, NGAN_Z);
	drawBlock(program, model_loc, matrix_phancap, instance, mau);
}

void veChanBan(GLuint program, GLuint model_loc, mat4 matrix_phancap, const color4& mau)
{
	mat4 instance = Scale(CHAN_X, CHAN_Y, CHAN_Z);
	drawBlock(program, model_loc, matrix_phancap, instance, mau);
}

void veBanAn(GLuint program, GLuint model_loc, const mat4& model_goc)
{
    // Màu sắc đồng bộ cho toàn bộ bàn
    color4 mauGo(230 / 255.0f, 195 / 255.0f, 150 / 255.0f, 1.0f);

    mat4 model_ban = model_goc;

    //Mặt bàn
    mat4 model_matban = model_ban * Translate(0.0f, 0.0f, CHAN_Z + MAT_Z / 2.0f);
    veMatBan(program, model_loc, model_matban, mauGo);

    //Ngăn bàn
    mat4 model_nganban = model_ban * Translate(0.0f, 0.0f, 0.52f);
    veNganBan(program, model_loc, model_nganban, mauGo);

    float x_offset = (MAT_X / 2.0f) - (CHAN_X / 2.0f) - 0.02f;
    float y_offset = (MAT_Y / 2.0f) - (CHAN_Y / 2.0f) - 0.02f;
    float z_offset = CHAN_Z / 2.0f; 

    // Chân 1 (Góc phải - trên)
    mat4 model_c1 = model_ban * Translate(x_offset, y_offset, z_offset);
    veChanBan(program, model_loc, model_c1, mauGo);

    // Chân 2 (Góc trái - trên)
    mat4 model_c2 = model_ban * Translate(-x_offset, y_offset, z_offset);
    veChanBan(program, model_loc, model_c2, mauGo);

    // Chân 3 (Góc phải - dưới)
    mat4 model_c3 = model_ban * Translate(x_offset, -y_offset, z_offset);
    veChanBan(program, model_loc, model_c3, mauGo);

    // Chân 4 (Góc trái - dưới)
    mat4 model_c4 = model_ban * Translate(-x_offset, -y_offset, z_offset);
    veChanBan(program, model_loc, model_c4, mauGo);
}
