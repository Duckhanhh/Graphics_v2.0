#include "Lo_hoa.h"
#include "Lap_phuong.h"

typedef vec4 color4;

// Hàm thiết lập vật liệu bóng loáng cho lọ gốm sứ và hoa
static void setMaterialLoHoa(GLuint program, const color4& material_color) {
	color4 light_ambient(0.2f, 0.2f, 0.2f, 1.0f);
	color4 light_diffuse(1.0f, 1.0f, 1.0f, 1.0f);
	color4 light_specular(1.0f, 1.0f, 1.0f, 1.0f);
	color4 material_specular(0.6f, 0.6f, 0.6f, 1.0f); // Tăng specular cho độ bóng gốm

	color4 ambient_product = light_ambient * material_color;
	color4 diffuse_product = light_diffuse * material_color;
	color4 specular_product = light_specular * material_specular;

	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular_product);
	glUniform1f(glGetUniformLocation(program, "Shininess"), 100.0f); // Độ bóng cao
}

static void drawBlockLoHoa(GLuint program, GLuint model_loc, const mat4& model, const mat4& instance, const color4& material_color) {
	setMaterialLoHoa(program, material_color);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * instance);
	drawLapPhuong();
}

void drawLoHoa(GLuint program, GLuint model_loc, const mat4& model) {
	// Bảng màu sắc cho lọ hoa
	color4 mauGom(0.2f, 0.6f, 0.6f, 1.0f);       // Màu xanh ngọc của bình gốm
	color4 mauCanh(0.4f, 0.25f, 0.15f, 1.0f);    // Màu nâu của cành cây
	color4 mauLa(0.15f, 0.5f, 0.2f, 1.0f);       // Màu xanh lá
	color4 mauHoaDo(0.9f, 0.2f, 0.3f, 1.0f);     // Màu hoa đỏ
	color4 mauHoaVang(0.9f, 0.8f, 0.1f, 1.0f);   // Màu hoa vàng nhị

	// ==========================================
	// PART 1: VẼ THÂN LỌ HOA GỐM (Phân cấp từ dưới lên)
	// ==========================================

	// 1. Đế lọ hoa (Sát mặt sàn Z = 0)
	mat4 instDe = Translate(0.0f, 0.0f, 0.03f) * Scale(0.2f, 0.2f, 0.06f);
	drawBlockLoHoa(program, model_loc, model, instDe, mauGom);

	// 2. Thân dưới (Phình to)
	mat4 instThanDuoi = Translate(0.0f, 0.0f, 0.2f) * Scale(0.32f, 0.32f, 0.28f);
	drawBlockLoHoa(program, model_loc, model, instThanDuoi, mauGom);

	// 3. Thân trên (Thuôn nhỏ dần lên cao)
	mat4 instThanTren = Translate(0.0f, 0.0f, 0.44f) * Scale(0.22f, 0.22f, 0.2f);
	drawBlockLoHoa(program, model_loc, model, instThanTren, mauGom);

	// 4. Cổ lọ hoa
	mat4 instCo = Translate(0.0f, 0.0f, 0.58f) * Scale(0.1f, 0.1f, 0.1f);
	drawBlockLoHoa(program, model_loc, model, instCo, mauGom);

	// 5. Miệng lọ hoa (Loe nhẹ ra ngoài)
	mat4 instMieng = Translate(0.0f, 0.0f, 0.64f) * Scale(0.15f, 0.15f, 0.04f);
	drawBlockLoHoa(program, model_loc, model, instMieng, mauGom);


	// ==========================================
	// PART 2: VẼ CÀNH, LÁ VÀ HOA (Mọc từ miệng bình Z >= 0.65)
	// ==========================================

	// --- CÀNH CHÍNH GIỮA (Thẳng đứng) ---
	mat4 instCanhGiua = Translate(0.0f, 0.0f, 0.72f) * Scale(0.015f, 0.015f, 0.14f);
	drawBlockLoHoa(program, model_loc, model, instCanhGiua, mauCanh);

	// Bông hoa giữa
	mat4 instHoaGiua = Translate(0.0f, 0.0f, 0.81f) * Scale(0.09f, 0.09f, 0.06f);
	drawBlockLoHoa(program, model_loc, model, instHoaGiua, mauHoaVang);


	// --- CÀNH BÊN TRÁI (Nghiêng theo trục X) ---
	mat4 instCanhTrai = Translate(-0.06f, 0.0f, 0.71f) * RotateY(-25.0f) * Scale(0.015f, 0.015f, 0.15f);
	drawBlockLoHoa(program, model_loc, model, instCanhTrai, mauCanh);

	// Bông hoa bên trái
	mat4 instHoaTrai = Translate(-0.12f, 0.0f, 0.79f) * Scale(0.08f, 0.08f, 0.08f);
	drawBlockLoHoa(program, model_loc, model, instHoaTrai, mauHoaDo);

	// Chiếc lá bên trái (Xoay nhẹ tạo góc tự nhiên)
	mat4 instLaTrai = Translate(-0.05f, 0.04f, 0.69f) * RotateX(30.0f) * Scale(0.08f, 0.02f, 0.03f);
	drawBlockLoHoa(program, model_loc, model, instLaTrai, mauLa);


	// --- CÀNH BÊN PHẢI (Nghiêng ngược lại) ---
	mat4 instCanhPhai = Translate(0.06f, 0.0f, 0.71f) * RotateY(25.0f) * Scale(0.015f, 0.015f, 0.15f);
	drawBlockLoHoa(program, model_loc, model, instCanhPhai, mauCanh);

	// Bông hoa bên phải
	mat4 instHoaPhai = Translate(0.12f, 0.0f, 0.79f) * Scale(0.08f, 0.08f, 0.08f);
	drawBlockLoHoa(program, model_loc, model, instHoaPhai, mauHoaDo);

	// Chiếc lá bên phải
	mat4 instLaPhai = Translate(0.05f, -0.04f, 0.69f) * RotateX(-30.0f) * Scale(0.08f, 0.02f, 0.03f);
	drawBlockLoHoa(program, model_loc, model, instLaPhai, mauLa);
}