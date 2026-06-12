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

const GLfloat GHE_RONG = 0.25f;
const GLfloat GHE_SAU = 0.4f;
const GLfloat GHE_CAO_MAT = 0.45f;
const GLfloat GHE_CAO_TONG = 0.85f;
const GLfloat GHE_CHAN_DAY = 0.04f;
const GLfloat GHE_GO_DAY = 0.02f;
const GLfloat GHE_DEM_DAY = 0.05f;

void veKhoiGhe(GLuint program, GLuint model_loc, mat4 matrix_phancap, GLfloat sx, GLfloat sy, GLfloat sz, const color4& mau)
{
    mat4 instance = Scale(sx, sy, sz);
    drawBlock(program, model_loc, matrix_phancap, instance, mau);
}

void veGhe(GLuint program, GLuint model_loc, const mat4& model_goc)
{
    // Màu sắc của ghế 
    color4 mauGo(230 / 255.0f, 195 / 255.0f, 150 / 255.0f, 1.0f);
    color4 mauDem(245 / 255.0f, 245 / 255.0f, 240 / 255.0f, 1.0f);

    float half_rong = GHE_RONG / 2.0f;
    float half_sau = GHE_SAU / 2.0f;
    float half_chan = GHE_CHAN_DAY / 2.0f;
    float cao_chan_truoc = GHE_CAO_MAT - GHE_DEM_DAY - GHE_GO_DAY;

    mat4 model_ghe = model_goc;

    // Chân trước trái
    mat4 m_chan_tt = model_ghe * Translate(-half_rong + half_chan, -half_sau + half_chan, cao_chan_truoc / 2.0f);
    veKhoiGhe(program, model_loc, m_chan_tt, GHE_CHAN_DAY, GHE_CHAN_DAY, cao_chan_truoc, mauGo);

    // Chân trước phải
    mat4 m_chan_tp = model_ghe * Translate(half_rong - half_chan, -half_sau + half_chan, cao_chan_truoc / 2.0f);
    veKhoiGhe(program, model_loc, m_chan_tp, GHE_CHAN_DAY, GHE_CHAN_DAY, cao_chan_truoc, mauGo);

    // Chân sau trái 
    mat4 m_chan_st = model_ghe * Translate(-half_rong + half_chan, half_sau - half_chan, GHE_CAO_TONG / 2.0f);
    veKhoiGhe(program, model_loc, m_chan_st, GHE_CHAN_DAY, GHE_CHAN_DAY, GHE_CAO_TONG, mauGo);

    // Chân sau phải 
    mat4 m_chan_sp = model_ghe * Translate(half_rong - half_chan, half_sau - half_chan, GHE_CAO_TONG / 2.0f);
    veKhoiGhe(program, model_loc, m_chan_sp, GHE_CHAN_DAY, GHE_CHAN_DAY, GHE_CAO_TONG, mauGo);

    mat4 model_van_go = model_ghe * Translate(0.0f, 0.0f, cao_chan_truoc + GHE_GO_DAY / 2.0f);
    veKhoiGhe(program, model_loc, model_van_go, GHE_RONG, GHE_SAU, GHE_GO_DAY, mauGo);

    //Nệm ngồi
    mat4 model_dem_ngoi = model_van_go * Translate(0.0f, 0.0f, GHE_GO_DAY / 2.0f + GHE_DEM_DAY / 2.0f);
    veKhoiGhe(program, model_loc, model_dem_ngoi, GHE_RONG, GHE_SAU, GHE_DEM_DAY, mauDem);

    //Tựa lưng
    mat4 model_khung_tua = model_ghe * Translate(0.0f, half_sau - half_chan, 0.0f);

    float rong_tua = GHE_RONG - 2 * GHE_CHAN_DAY;
    float cao_thanh_ngang = 0.06f;
    mat4 model_thanh_ngang = model_khung_tua * Translate(0.0f, 0.0f, GHE_CAO_TONG - cao_thanh_ngang / 2.0f);
    veKhoiGhe(program, model_loc, model_thanh_ngang, rong_tua, GHE_CHAN_DAY, cao_thanh_ngang, mauGo);

    //Nệm tựa lưng
    float z_day_tua = cao_chan_truoc + GHE_GO_DAY + GHE_DEM_DAY;
    float z_dinh_tua = GHE_CAO_TONG - cao_thanh_ngang;
    float cao_dem_tua = z_dinh_tua - z_day_tua;
    float z_dem_tua = z_day_tua + cao_dem_tua / 2.0f;

    mat4 model_dem_tua = model_khung_tua * Translate(0.0f, -0.015f, z_dem_tua);
    veKhoiGhe(program, model_loc, model_dem_tua, rong_tua, GHE_CHAN_DAY + 0.02f, cao_dem_tua, mauDem);
}