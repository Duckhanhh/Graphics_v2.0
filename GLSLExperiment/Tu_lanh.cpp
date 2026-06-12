#include "Tu_lanh.h"
#include "Lap_phuong.h"

typedef vec4 color4;
static float goc_mo_cua_trai = 0.0f;
static float goc_mo_cua_phai = 0.0f;

static void setMaterial(GLuint program, const color4& material_color)
{
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

static void drawBlock(GLuint program, GLuint model_loc, const mat4& model, const mat4& instance, const color4& material_color)
{
	setMaterial(program, material_color);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * instance);
	drawLapPhuong();
}


void drawThanTuLanh(GLuint program, GLuint model_loc, const mat4& model)
{
	// Vỏ hông trái
	mat4 instance1 = Translate(-0.3865f, 0.0475f, 0.9f)
		* Scale(0.025f, 0.62f, 1.7f);
	drawBlock(program, model_loc, model, instance1, color4(0.015f, 0.014f, 0.013f, 1.0f));

	// Vỏ hông phải
	mat4 instance2 = Translate(0.3865f, 0.0475f, 0.9f)
		* Scale(0.025f, 0.62f, 1.7f);
	drawBlock(program, model_loc, model, instance2, color4(0.015f, 0.014f, 0.013f, 1.0f));

	// Vỏ lưng sau
	mat4 instance3 = Translate(0.0f, 0.345f, 0.9f)
		* Scale(0.798f, 0.025f, 1.7f);
	drawBlock(program, model_loc, model, instance3, color4(0.12f, 0.12f, 0.12f, 1.0f));

	// Đế dưới thân
	mat4 instance4 = Translate(0.0f, 0.0475f, 0.025f)
		* Scale(0.798f, 0.62f, 0.05f);
	drawBlock(program, model_loc, model, instance4, color4(0.015f, 0.014f, 0.013f, 1.0f));

	// Nóc thân
	mat4 instance5 = Translate(0.0f, 0.0475f, 1.765f)
		* Scale(0.798f, 0.62f, 0.03f);
	drawBlock(program, model_loc, model, instance5, color4(0.015f, 0.014f, 0.013f, 1.0f));

	// Vách chia khoang giữa
	mat4 instance6 = Translate(0.0f, 0.0475f, 0.9f)
		* Scale(0.024f, 0.62f, 1.65f);
	drawBlock(program, model_loc, model, instance6, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Viền trước thân - trên
	mat4 instance7 = Translate(0.0f, -0.2525f, 1.732f)
		* Scale(0.798f, 0.02f, 0.035f);
	drawBlock(program, model_loc, model, instance7, color4(0.015f, 0.014f, 0.013f, 1.0f));

	// Viền trước thân - dưới
	mat4 instance8 = Translate(0.0f, -0.2525f, 0.068f)
		* Scale(0.798f, 0.02f, 0.035f);
	drawBlock(program, model_loc, model, instance8, color4(0.015f, 0.014f, 0.013f, 1.0f));

	// Viền trước thân - trái
	mat4 instance9 = Translate(-0.384f, -0.2525f, 0.9f)
		* Scale(0.03f, 0.02f, 1.665f);
	drawBlock(program, model_loc, model, instance9, color4(0.015f, 0.014f, 0.013f, 1.0f));

	// Viền trước thân - phải
	mat4 instance10 = Translate(0.384f, -0.2525f, 0.9f)
		* Scale(0.03f, 0.02f, 1.665f);
	drawBlock(program, model_loc, model, instance10, color4(0.015f, 0.014f, 0.013f, 1.0f));

	// Lòng trắng khoang đông - lưng
	mat4 instance12 = Translate(-0.1885f, 0.312f, 0.905f)
		* Scale(0.341f, 0.006f, 1.57f);
	drawBlock(program, model_loc, model, instance12, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Lòng trắng khoang đông - đáy
	mat4 instance13 = Translate(-0.1885f, 0.0375f, 0.123f)
		* Scale(0.341f, 0.555f, 0.006f);
	drawBlock(program, model_loc, model, instance13, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Lòng trắng khoang đông - nóc
	mat4 instance14 = Translate(-0.1885f, 0.0375f, 1.687f)
		* Scale(0.341f, 0.555f, 0.006f);
	drawBlock(program, model_loc, model, instance14, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Lòng trắng khoang đông - thành trái
	mat4 instance15 = Translate(-0.356f, 0.0375f, 0.905f)
		* Scale(0.006f, 0.555f, 1.57f);
	drawBlock(program, model_loc, model, instance15, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Lòng trắng khoang đông - thành giữa
	mat4 instance16 = Translate(-0.021f, 0.0375f, 0.905f)
		* Scale(0.006f, 0.555f, 1.57f);
	drawBlock(program, model_loc, model, instance16, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Lòng trắng khoang mát - lưng
	mat4 instance17 = Translate(0.1885f, 0.312f, 0.905f)
		* Scale(0.341f, 0.006f, 1.57f);
	drawBlock(program, model_loc, model, instance17, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Lòng trắng khoang mát - đáy
	mat4 instance18 = Translate(0.1885f, 0.0375f, 0.123f)
		* Scale(0.341f, 0.555f, 0.006f);
	drawBlock(program, model_loc, model, instance18, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Lòng trắng khoang mát - nóc
	mat4 instance19 = Translate(0.1885f, 0.0375f, 1.687f)
		* Scale(0.341f, 0.555f, 0.006f);
	drawBlock(program, model_loc, model, instance19, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Lòng trắng khoang mát - thành giữa
	mat4 instance20 = Translate(0.021f, 0.0375f, 0.905f)
		* Scale(0.006f, 0.555f, 1.57f);
	drawBlock(program, model_loc, model, instance20, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Lòng trắng khoang mát - thành phải
	mat4 instance21 = Translate(0.356f, 0.0375f, 0.905f)
		* Scale(0.006f, 0.555f, 1.57f);
	drawBlock(program, model_loc, model, instance21, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Chân trước trái
	mat4 instance22 = Translate(-0.35f, -0.325f, 0.015f)
		* Scale(0.045f, 0.045f, 0.03f);
	drawBlock(program, model_loc, model, instance22, color4(0.015f, 0.014f, 0.013f, 1.0f));

	// Chân trước phải
	mat4 instance23 = Translate(0.35f, -0.325f, 0.015f)
		* Scale(0.045f, 0.045f, 0.03f);
	drawBlock(program, model_loc, model, instance23, color4(0.015f, 0.014f, 0.013f, 1.0f));

	// Chân sau trái
	mat4 instance24 = Translate(-0.35f, 0.325f, 0.015f)
		* Scale(0.045f, 0.045f, 0.03f);
	drawBlock(program, model_loc, model, instance24, color4(0.015f, 0.014f, 0.013f, 1.0f));

	// Chân sau phải
	mat4 instance25 = Translate(0.35f, 0.325f, 0.015f)
		* Scale(0.045f, 0.045f, 0.03f);
	drawBlock(program, model_loc, model, instance25, color4(0.015f, 0.014f, 0.013f, 1.0f));

	// Bản lề trái trên
	mat4 instance26 = Translate(-0.384f, -0.2625f, 1.762f)
		* Scale(0.03f, 0.055f, 0.035f);
	drawBlock(program, model_loc, model, instance26, color4(0.3f, 0.32f, 0.33f, 1.0f));

	// Bản lề trái dưới
	mat4 instance27 = Translate(-0.384f, -0.2625f, 0.073f)
		* Scale(0.03f, 0.055f, 0.035f);
	drawBlock(program, model_loc, model, instance27, color4(0.3f, 0.32f, 0.33f, 1.0f));

	// Bản lề phải trên
	mat4 instance28 = Translate(0.384f, -0.2625f, 1.762f)
		* Scale(0.03f, 0.055f, 0.035f);
	drawBlock(program, model_loc, model, instance28, color4(0.3f, 0.32f, 0.33f, 1.0f));

	// Bản lề phải dưới
	mat4 instance29 = Translate(0.384f, -0.2625f, 0.073f)
		* Scale(0.03f, 0.055f, 0.035f);
	drawBlock(program, model_loc, model, instance29, color4(0.3f, 0.32f, 0.33f, 1.0f));

	// Kệ kính đông 1 - mặt kính
	mat4 instance30 = Translate(-0.1885f, 0.05f, 0.575f)
		* Scale(0.31f, 0.485f, 0.01f);
	drawBlock(program, model_loc, model, instance30, color4(0.65f, 0.85f, 0.9f, 1.0f));

	// Kệ kính đông 2 - mặt kính
	mat4 instance34 = Translate(-0.1885f, 0.05f, 0.865f)
		* Scale(0.31f, 0.485f, 0.01f);
	drawBlock(program, model_loc, model, instance34, color4(0.65f, 0.85f, 0.9f, 1.0f));

	// Kệ kính đông 3 - mặt kính
	mat4 instance38 = Translate(-0.1885f, 0.05f, 1.155f)
		* Scale(0.31f, 0.485f, 0.01f);
	drawBlock(program, model_loc, model, instance38, color4(0.65f, 0.85f, 0.9f, 1.0f));

	// Kệ kính đông 4 - mặt kính
	mat4 instance42 = Translate(-0.1885f, 0.05f, 1.445f)
		* Scale(0.31f, 0.485f, 0.01f);
	drawBlock(program, model_loc, model, instance42, color4(0.65f, 0.85f, 0.9f, 1.0f));

	// Kệ kính mát 1 - mặt kính
	mat4 instance46 = Translate(0.1885f, 0.05f, 0.575f)
		* Scale(0.32f, 0.485f, 0.01f);
	drawBlock(program, model_loc, model, instance46, color4(0.65f, 0.85f, 0.9f, 1.0f));

	// Kệ kính mát 2 - mặt kính
	mat4 instance50 = Translate(0.1885f, 0.05f, 0.865f)
		* Scale(0.32f, 0.485f, 0.01f);
	drawBlock(program, model_loc, model, instance50, color4(0.65f, 0.85f, 0.9f, 1.0f));

	// Kệ kính mát 3 - mặt kính
	mat4 instance54 = Translate(0.1885f, 0.05f, 1.155f)
		* Scale(0.32f, 0.485f, 0.01f);
	drawBlock(program, model_loc, model, instance54, color4(0.65f, 0.85f, 0.9f, 1.0f));

	// Kệ kính mát 4 - mặt kính
	mat4 instance58 = Translate(0.1885f, 0.05f, 1.445f)
		* Scale(0.32f, 0.485f, 0.01f);
	drawBlock(program, model_loc, model, instance58, color4(0.65f, 0.85f, 0.9f, 1.0f));

	// Ngăn kéo đông dưới - đáy
	mat4 instance62 = Translate(-0.1885f, 0.055f, 0.146f)
		* Scale(0.31f, 0.43f, 0.012f);
	drawBlock(program, model_loc, model, instance62, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo đông dưới - mặt trước
	mat4 instance63 = Translate(-0.1885f, -0.151f, 0.22f)
		* Scale(0.31f, 0.018f, 0.16f);
	drawBlock(program, model_loc, model, instance63, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo đông dưới - thành trái
	mat4 instance64 = Translate(-0.3365f, 0.055f, 0.22f)
		* Scale(0.014f, 0.43f, 0.16f);
	drawBlock(program, model_loc, model, instance64, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo đông dưới - thành phải
	mat4 instance65 = Translate(-0.0405f, 0.055f, 0.22f)
		* Scale(0.014f, 0.43f, 0.16f);
	drawBlock(program, model_loc, model, instance65, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo đông dưới - thành sau
	mat4 instance66 = Translate(-0.1885f, 0.261f, 0.22f)
		* Scale(0.31f, 0.018f, 0.16f);
	drawBlock(program, model_loc, model, instance66, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo đông trên - đáy
	mat4 instance67 = Translate(-0.1885f, 0.055f, 0.341f)
		* Scale(0.31f, 0.43f, 0.012f);
	drawBlock(program, model_loc, model, instance67, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo đông trên - mặt trước
	mat4 instance68 = Translate(-0.1885f, -0.151f, 0.415f)
		* Scale(0.31f, 0.018f, 0.16f);
	drawBlock(program, model_loc, model, instance68, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo đông trên - thành trái
	mat4 instance69 = Translate(-0.3365f, 0.055f, 0.415f)
		* Scale(0.014f, 0.43f, 0.16f);
	drawBlock(program, model_loc, model, instance69, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo đông trên - thành phải
	mat4 instance70 = Translate(-0.0405f, 0.055f, 0.415f)
		* Scale(0.014f, 0.43f, 0.16f);
	drawBlock(program, model_loc, model, instance70, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo đông trên - thành sau
	mat4 instance71 = Translate(-0.1885f, 0.261f, 0.415f)
		* Scale(0.31f, 0.018f, 0.16f);
	drawBlock(program, model_loc, model, instance71, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo mát dưới - đáy
	mat4 instance72 = Translate(0.1885f, 0.055f, 0.146f)
		* Scale(0.32f, 0.43f, 0.012f);
	drawBlock(program, model_loc, model, instance72, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo mát dưới - mặt trước
	mat4 instance73 = Translate(0.1885f, -0.151f, 0.225f)
		* Scale(0.32f, 0.018f, 0.17f);
	drawBlock(program, model_loc, model, instance73, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo mát dưới - thành trái
	mat4 instance74 = Translate(0.0355f, 0.055f, 0.225f)
		* Scale(0.014f, 0.43f, 0.17f);
	drawBlock(program, model_loc, model, instance74, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo mát dưới - thành phải
	mat4 instance75 = Translate(0.3415f, 0.055f, 0.225f)
		* Scale(0.014f, 0.43f, 0.17f);
	drawBlock(program, model_loc, model, instance75, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo mát dưới - thành sau
	mat4 instance76 = Translate(0.1885f, 0.261f, 0.225f)
		* Scale(0.32f, 0.018f, 0.17f);
	drawBlock(program, model_loc, model, instance76, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo mát trên - đáy
	mat4 instance77 = Translate(0.1885f, 0.055f, 0.346f)
		* Scale(0.32f, 0.43f, 0.012f);
	drawBlock(program, model_loc, model, instance77, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo mát trên - mặt trước
	mat4 instance78 = Translate(0.1885f, -0.151f, 0.425f)
		* Scale(0.32f, 0.018f, 0.17f);
	drawBlock(program, model_loc, model, instance78, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo mát trên - thành trái
	mat4 instance79 = Translate(0.0355f, 0.055f, 0.425f)
		* Scale(0.014f, 0.43f, 0.17f);
	drawBlock(program, model_loc, model, instance79, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo mát trên - thành phải
	mat4 instance80 = Translate(0.3415f, 0.055f, 0.425f)
		* Scale(0.014f, 0.43f, 0.17f);
	drawBlock(program, model_loc, model, instance80, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Ngăn kéo mát trên - thành sau
	mat4 instance81 = Translate(0.1885f, 0.261f, 0.425f)
		* Scale(0.32f, 0.018f, 0.17f);
	drawBlock(program, model_loc, model, instance81, color4(0.86f, 0.92f, 0.94f, 1.0f));
}

void drawCuaTraiTuLanh(GLuint program, GLuint model_loc, const mat4& model)
{
	// Cánh cửa trái / đông - tấm chính
	mat4 instance82 = Translate(-0.1975f, -0.31f, 0.9f)
		* Scale(0.383f, 0.095f, 1.69f);
	drawBlock(program, model_loc, model, instance82, color4(0.88f, 0.90f, 0.92f, 1.0f));



	// Mặt lưng trong cửa trái
	mat4 instance92 = Translate(-0.1975f, -0.2595f, 0.9f)
		* Scale(0.335f, 0.006f, 1.55f);
	drawBlock(program, model_loc, model, instance92, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Viền trong cửa trái - trên
	mat4 instance93 = Translate(-0.1975f, -0.238f, 1.69f)
		* Scale(0.335f, 0.045f, 0.03f);
	drawBlock(program, model_loc, model, instance93, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Viền trong cửa trái - dưới
	mat4 instance94 = Translate(-0.1975f, -0.238f, 0.11f)
		* Scale(0.335f, 0.045f, 0.03f);
	drawBlock(program, model_loc, model, instance94, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Viền trong cửa trái - trái
	mat4 instance95 = Translate(-0.3575f, -0.238f, 0.9f)
		* Scale(0.03f, 0.045f, 1.55f);
	drawBlock(program, model_loc, model, instance95, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Viền trong cửa trái - phải
	mat4 instance96 = Translate(-0.0375f, -0.238f, 0.9f)
		* Scale(0.03f, 0.045f, 1.55f);
	drawBlock(program, model_loc, model, instance96, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Khay cửa đông 1
	mat4 instance97 = Translate(-0.1975f, -0.218f, 0.42f)
		* Scale(0.29f, 0.08f, 0.08f);
	drawBlock(program, model_loc, model, instance97, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Khay cửa đông 2
	mat4 instance99 = Translate(-0.1975f, -0.218f, 1.36f)
		* Scale(0.29f, 0.08f, 0.08f);
	drawBlock(program, model_loc, model, instance99, color4(0.86f, 0.92f, 0.94f, 1.0f));
}

void drawCuaPhaiTuLanh(GLuint program, GLuint model_loc, const mat4& model)
{
	// Cánh cửa phải / mát - tấm chính
	mat4 instance101 = Translate(0.1975f, -0.31f, 0.9f)
		* Scale(0.383f, 0.095f, 1.69f);
	drawBlock(program, model_loc, model, instance101, color4(0.88f, 0.90f, 0.92f, 1.0f));

	// Mặt lưng trong cửa phải
	mat4 instance107 = Translate(0.1975f, -0.2595f, 0.9f)
		* Scale(0.335f, 0.006f, 1.55f);
	drawBlock(program, model_loc, model, instance107, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Viền trong cửa phải - trên
	mat4 instance108 = Translate(0.1975f, -0.238f, 1.69f)
		* Scale(0.335f, 0.045f, 0.03f);
	drawBlock(program, model_loc, model, instance108, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Viền trong cửa phải - dưới
	mat4 instance109 = Translate(0.1975f, -0.238f, 0.11f)
		* Scale(0.335f, 0.045f, 0.03f);
	drawBlock(program, model_loc, model, instance109, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Viền trong cửa phải - trái
	mat4 instance110 = Translate(0.0375f, -0.238f, 0.9f)
		* Scale(0.03f, 0.045f, 1.55f);
	drawBlock(program, model_loc, model, instance110, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Viền trong cửa phải - phải
	mat4 instance111 = Translate(0.3575f, -0.238f, 0.9f)
		* Scale(0.03f, 0.045f, 1.55f);
	drawBlock(program, model_loc, model, instance111, color4(0.94f, 0.96f, 0.96f, 1.0f));

	// Khay cửa mát 1
	mat4 instance112 = Translate(0.1975f, -0.218f, 0.3f)
		* Scale(0.325f, 0.08f, 0.08f);
	drawBlock(program, model_loc, model, instance112, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Khay cửa mát 2
	mat4 instance114 = Translate(0.1975f, -0.218f, 0.6f)
		* Scale(0.325f, 0.08f, 0.08f);
	drawBlock(program, model_loc, model, instance114, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Khay cửa mát 3
	mat4 instance116 = Translate(0.1975f, -0.218f, 0.9f)
		* Scale(0.325f, 0.08f, 0.08f);
	drawBlock(program, model_loc, model, instance116, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Khay cửa mát 4
	mat4 instance118 = Translate(0.1975f, -0.218f, 1.2f)
		* Scale(0.325f, 0.08f, 0.08f);
	drawBlock(program, model_loc, model, instance118, color4(0.86f, 0.92f, 0.94f, 1.0f));

	// Khay cửa mát 5
	mat4 instance120 = Translate(0.1975f, -0.218f, 1.5f)
		* Scale(0.325f, 0.08f, 0.08f);
	drawBlock(program, model_loc, model, instance120, color4(0.86f, 0.92f, 0.94f, 1.0f));


}

void moCuaTraiTuLanh()
{
	if (goc_mo_cua_trai < 90.0f)
		goc_mo_cua_trai += 5.0f;
}

void dongCuaTraiTuLanh()
{
	if (goc_mo_cua_trai > 0.0f)
		goc_mo_cua_trai -= 5.0f;
}

void moCuaPhaiTuLanh()
{
	if (goc_mo_cua_phai < 90.0f)
		goc_mo_cua_phai += 5.0f;
}

void dongCuaPhaiTuLanh()
{
	if (goc_mo_cua_phai > 0.0f)
		goc_mo_cua_phai -= 5.0f;
}

void drawTuLanh(GLuint program, GLuint model_loc, const mat4& model)
{
	mat4 modelCuaTrai = model * Translate(-0.399f, -0.2625f, 0.0f) * RotateZ(-goc_mo_cua_trai) * Translate(0.399f, 0.2625f, 0.0f);
	mat4 modelCuaPhai = model * Translate(0.399f, -0.2625f, 0.0f) * RotateZ(goc_mo_cua_phai) * Translate(-0.399f, 0.2625f, 0.0f);
	drawThanTuLanh(program, model_loc, model);
	drawCuaTraiTuLanh(program, model_loc, modelCuaTrai);
	drawCuaPhaiTuLanh(program, model_loc, modelCuaPhai);
}
