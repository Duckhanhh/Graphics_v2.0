#include "Tu_Bat.h"
#include "Lap_phuong.h"
typedef vec4 color4;
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

float moCuaTraiTu1 = 0.0f;
float moCuaPhaiTu1 = 0.0f;
float moCuaTu2 = 0.0f;
bool batMayHutMui = false;
bool batDenHutMui = false;
int tocDoQuat = 0;      

// Vẽ khung tủ bát 1 
void drawKhungTuBat1(GLuint program, GLuint model_loc, const mat4& model)
{
    color4 mauGo(0.55f, 0.35f, 0.18f, 1);

    // Nóc
    mat4 tren = Translate(0.0f, 0.0f, 0.675f) * Scale(0.8f, 1.8f, 0.05f);
    drawBlock(program, model_loc, model, tren, mauGo);

    // Đáy
    mat4 day = Translate(0.0f, 0.0f, 0.03f) * Scale(0.8f, 1.8f, 0.05f);
    drawBlock(program, model_loc, model, day, mauGo);

    // Thành dưới
    mat4 duoi = Translate(0.0f, -0.9f, 0.35f) * Scale(0.8f, 0.05f, 0.7f);
    drawBlock(program, model_loc, model, duoi, mauGo);

    // Thành trên
    mat4 trenBen = Translate(0.0f, 0.9f, 0.35f) * Scale(0.8f, 0.05f, 0.7f);
    drawBlock(program, model_loc, model, trenBen, mauGo);

    // Mặt sau
    mat4 sau = Translate(0.375f, 0.0f, 0.35f) * Scale(0.05f, 1.8f, 0.65f);
    drawBlock(program, model_loc, model, sau, mauGo);

    // Vách ngăn giữa
    mat4 vachGiua = Translate(0.0f, 0.0f, 0.35f) * Scale(0.8f, 0.05f, 0.6f);
    drawBlock(program, model_loc, model, vachGiua, mauGo);

    // Kệ tủ
    mat4 keNgangTu1 = model * Translate(0.0f, 0.0f, 0.35f) * Scale(0.75f, 1.7f, 0.03f);
    drawBlock(program, model_loc, keNgangTu1, mat4(), mauGo);
}

// Vẽ khung tủ bát 2 
void drawKhungTuBat2(GLuint program, GLuint model_loc, const mat4& model)
{
    color4 mauGo(0.55f, 0.35f, 0.18f, 1);

    // Nóc
    mat4 tren = Translate(-0.525f, 1.3f, 0.675f) * Scale(1.8f, 0.8f, 0.05f);
    drawBlock(program, model_loc, model, tren, mauGo);

    // Đáy
    mat4 day = Translate(-0.525f, 1.3f, 0.03f) * Scale(1.8f, 0.8f, 0.05f);
    drawBlock(program, model_loc, model, day, mauGo);

    // Thành trái 
    mat4 trai = Translate(-1.425f, 1.3f, 0.35f) * Scale(0.05f, 0.8f, 0.7f);
    drawBlock(program, model_loc, model, trai, mauGo);

    // Thành phải 
    mat4 phai = Translate(0.375f, 1.3f, 0.35f) * Scale(0.05f, 0.8f, 0.7f);
    drawBlock(program, model_loc, model, phai, mauGo);

    // Mặt sau 
    mat4 sau = Translate(-0.525f, 1.675f, 0.35f) * Scale(1.8f, 0.05f, 0.65f);
    drawBlock(program, model_loc, model, sau, mauGo);

    // Kệ tủ
    mat4 keNgang = model * Translate(-0.525f, 1.3f, 0.35f) * Scale(1.7f, 0.7f, 0.03f);
    drawBlock(program, model_loc, keNgang, mat4(), mauGo);
}

// Vẽ cửa tủ bát 1 kèm tay cầm dọc
void drawCanhTuBat1(GLuint program, GLuint model_loc, const mat4& model)
{
    color4 mauTrang(1, 1, 1, 1);
    color4 mauTayCam(0.7f, 0.7f, 0.7f, 1.0f);

    // Cánh cửa trái tủ 1
    mat4 modelCuaTrai = model * Translate(-0.375f, -0.85f, 0.35f) * RotateZ(moCuaTraiTu1);

    mat4 canhTrai = Translate(0.0f, 0.40f, 0.0f) * Scale(0.04f, 0.9f, 0.60f);
    drawBlock(program, model_loc, modelCuaTrai, canhTrai, mauTrang);

    mat4 tayCamTrai = Translate(-0.03f, 0.65f, 0.0f) * Scale(0.02f, 0.05f, 0.15f);
    drawBlock(program, model_loc, modelCuaTrai, tayCamTrai, mauTayCam);

    // Cánh cửa phải tủ 1
    mat4 modelCuaPhai = model * Translate(-0.375f, 0.05f, 0.35f) * RotateZ(moCuaPhaiTu1);

    mat4 canhPhai = Translate(0.0f, 0.40f, 0.0f) * Scale(0.04f, 0.9f, 0.60f);
    drawBlock(program, model_loc, modelCuaPhai, canhPhai, mauTrang);

    mat4 tayCamPhai = Translate(-0.03f, 0.65f, 0.0f) * Scale(0.02f, 0.05f, 0.15f);
    drawBlock(program, model_loc, modelCuaPhai, tayCamPhai, mauTayCam);
}

// Vẽ cánh cửa tủ bát 2 kèm tay cầm ngang
void drawCanhTuBat2(GLuint program, GLuint model_loc, const mat4& model)
{
    color4 mauTrang(1, 1, 1, 1);
    color4 mauTayCam(0.7f, 0.7f, 0.7f, 1.0f);

    // Cánh cửa tủ 2
    mat4 modelCua2 = model * Translate(-0.9f, 0.925f, 0.65f) * RotateX(-moCuaTu2);

    mat4 canhCua = Translate(0.0f, 0.0f, -0.30f) * Scale(1.03f, 0.04f, 0.6f);
    drawBlock(program, model_loc, modelCua2, canhCua, mauTrang);

    // Tay cầm tủ 2
    mat4 tayCam2 = Translate(0.0f, -0.03f, -0.53f) * Scale(0.20f, 0.02f, 0.03f);
    drawBlock(program, model_loc, modelCua2, tayCam2, mauTayCam);
}

// Vẽ máy hút mùi
void drawMayHutMuiChuan(GLuint program, GLuint model_loc, const mat4& model)
{
    // Màu sắc
    color4 mauThanTren(0.25f, 0.25f, 0.25f, 1.0f);
    color4 mauTangGiua(0.40f, 0.40f, 0.40f, 1.0f);
    color4 mauTangDuoi(0.55f, 0.55f, 0.55f, 1.0f);

    color4 mauNutBong(0.85f, 0.85f, 0.85f, 1.0f);
    color4 mauLuoi(0.15f, 0.15f, 0.15f, 1.0f);
    color4 mauQuat(0.15f, 0.15f, 0.15f, 1.0f);
    color4 mauTat(0.3f, 0.3f, 0.3f, 1);

    // Màu đèn báo trạng thái

    // Đèn nguồn
    color4 denNguon =
        batMayHutMui ?
        color4(1, 0, 0, 1) :
        mauTat;

    // Đèn tốc độ quạt
    color4 denQuat;

    if (tocDoQuat == 1)
        denQuat = color4(1, 0, 0, 1);
    else if (tocDoQuat == 2)
        denQuat = color4(1, 1, 0, 1);
    else if (tocDoQuat == 3)
        denQuat = color4(0, 1, 0, 1);
    else
        denQuat = mauTat;

    // Đèn chiếu sáng
    color4 denAnhSang = 
        batDenHutMui ?
        color4(0.0f, 0.5f, 1.0f, 1.0f):
        mauTat;

    // Thân trên
    mat4 modelTren = model * Translate(-0.02f, 0.40f, -0.09f) * Scale(0.45f, 0.65f, 0.08f);
    drawBlock(program, model_loc, modelTren, mat4(), mauThanTren);

    // Thân giữa (bảng điều khiển)
    mat4 modelGiua = model * Translate(-0.05f, 0.40f, -0.14f) * Scale(0.55f, 0.75f, 0.04f);
    drawBlock(program, model_loc, modelGiua, mat4(), mauTangGiua);

    // 3 đèn báo trạng thái

    // Nguồn
    mat4 den1 = model * Translate(-0.41f, 0.30f, -0.19f) * Scale(0.015f, 0.03f, 0.015f);
    drawBlock(program, model_loc, den1, mat4(), denNguon);

    // Quạt
    mat4 den2 = model * Translate(-0.41f, 0.40f, -0.19f) * Scale(0.015f, 0.03f, 0.015f);
    drawBlock(program, model_loc, den2, mat4(), denQuat);

    // Đèn
    mat4 den3 = model * Translate(-0.41f, 0.50f, -0.19f) * Scale(0.015f, 0.03f, 0.015f);
    drawBlock(program, model_loc, den3, mat4(), denAnhSang);

    // Hàng nút bấm

    // Nút nguồn
    mat4 nutNguon = model * Translate(-0.33f, 0.25f, -0.14f) * Scale(0.01f, 0.04f, 0.015f);
    drawBlock(program, model_loc, nutNguon, mat4(), mauNutBong);

    // Tăng tốc quạt
    mat4 nutTang = model * Translate(-0.33f, 0.35f, -0.14f) * Scale(0.01f, 0.04f, 0.015f);

    drawBlock(program, model_loc, nutTang, mat4(), mauNutBong);

    // Giảm tốc quạt
    mat4 nutGiam = model * Translate(-0.33f, 0.45f, -0.14f) * Scale(0.01f, 0.04f, 0.015f);

    drawBlock(program, model_loc, nutGiam, mat4(), mauNutBong);

    // Nút đèn
    mat4 nutDen = model * Translate(-0.33f, 0.55f, -0.14f) * Scale(0.01f, 0.04f, 0.015f);
    drawBlock(program, model_loc, nutDen, mat4(), mauNutBong);

    // Thân dưới
    mat4 modelDuoi = model * Translate(-0.08f, 0.40f, -0.19f) * Scale(0.66f, 0.88f, 0.06f);
    drawBlock(program, model_loc, modelDuoi, mat4(), mauTangDuoi);

    color4 mauKhung(0.45f, 0.45f, 0.45f, 1.0f);

    // Trái trên
    mat4 khung1 = model
        * Translate(-0.26f, 0.68f, -0.22f)
        * Scale(0.015f, 0.18f, 0.10f);
    drawBlock(program, model_loc, khung1, mat4(), mauKhung);

    // Phải trên
    mat4 khung2 = model
        * Translate(0.10f, 0.68f, -0.22f)
        * Scale(0.015f, 0.18f, 0.10f);
    drawBlock(program, model_loc, khung2, mat4(), mauKhung);

    // Trái dưới
    mat4 khung3 = model
        * Translate(-0.26f, 0.12f, -0.22f)
        * Scale(0.015f, 0.18f, 0.10f);
    drawBlock(program, model_loc, khung3, mat4(), mauKhung);

    // Phải dưới
    mat4 khung4 = model
        * Translate(0.10f, 0.12f, -0.22f)
        * Scale(0.015f, 0.18f, 0.10f);
    drawBlock(program, model_loc, khung4, mat4(), mauKhung);

    // Quạt

    // Cánh 1
    mat4 quat1 = model
        * Translate(-0.08f, 0.40f, -0.25f)
        * Translate(0.10f, 0, 0)
        * Scale(0.16f, 0.025f, 0.015f);
    drawBlock(program, model_loc, quat1, mat4(), mauQuat);

    // Cánh 2
    mat4 quat2 = model
        * Translate(-0.08f, 0.40f, -0.25f)
        * Translate(0.10f, 0, 0)
        * Scale(0.16f, 0.025f, 0.015f);
    drawBlock(program, model_loc, quat2, mat4(), mauQuat);

    // Cánh 3
    mat4 quat3 = model
        * Translate(-0.08f, 0.40f, -0.25f)
        * Translate(0.10f, 0, 0)
        * Scale(0.16f, 0.025f, 0.015f);
    drawBlock(program, model_loc, quat3, mat4(), mauQuat);

    // Cánh 4
    mat4 quat4 = model
        * Translate(-0.08f, 0.40f, -0.25f)
        * Translate(0.10f, 0, 0)
        * Scale(0.16f, 0.025f, 0.015f);
    drawBlock(program, model_loc, quat4, mat4(), mauQuat);

    // Trục quạt
    mat4 trucQuat = model * Translate(-0.08f, 0.40f, -0.25f) * Scale(0.045f, 0.045f, 0.03f);
    drawBlock(program, model_loc, trucQuat, mat4(), mauQuat);

    // Trục treo quạt
    mat4 giaDoQuat = model * Translate(-0.08f, 0.40f, -0.235f) * Scale(0.02f, 0.02f, 0.08f);        
    drawBlock(program, model_loc, giaDoQuat, mat4(), mauQuat);

    // Lưới ngang
    for (int i = -3; i <= 3; i++)
    {
        mat4 thanhLuoi = model * Translate(-0.08f, 0.40f + i * 0.093f, -0.27f) * Scale(0.37f, 0.015f, 0.01f);
        drawBlock(program, model_loc, thanhLuoi, mat4(), mauLuoi);
    }

    // Lưới dọc
    for (int i = -3; i <= 3; i++)
    {
        mat4 thanhDoc = model * Translate(-0.08f + i * 0.06f, 0.40f, -0.27f) * Scale(0.02f, 0.57f, 0.01f);
        drawBlock(program, model_loc, thanhDoc, mat4(), mauLuoi);
    }

    // Đèn chiếu sáng
    color4 mauDen =
        batDenHutMui ?
        color4(1.0f, 1.0f, 0.6f, 1.0f) :
        color4(0.15f, 0.15f, 0.15f, 1.0f);

    mat4 denChieuSang =
        model
        * Translate(-0.34f, 0.40f, -0.23f)
        * Scale(0.06f, 0.3f, 0.01f);
    drawBlock(program, model_loc, denChieuSang, mat4(), mauDen);
}

// Vẽ Hệ thống ống thông gió 
void drawOngThongGioGiauKinh(GLuint program, GLuint model_loc, const mat4& model)
{
    color4 mauOng(0.7f, 0.7f, 0.7f, 1.0f);

    // Đoạn ống ngang
    mat4 ongNgang = model * Translate(-0.02f, 0.85f, -0.06f) * Scale(0.18f, 0.90f, 0.12f);
    drawBlock(program, model_loc, ongNgang, mat4(), mauOng);

    // Đoạn ống dọc
    mat4 ongDung = model * Translate(-0.02f, 1.21f, 0.45f) * Scale(0.18f, 0.12f, 1.10f);
    drawBlock(program, model_loc, ongDung, mat4(), mauOng);

    // Đoạn ống thoát khí
    mat4 ongThoatNgoai = model * Translate(-0.02f, 1.65f, 0.94f) * Scale(0.18f, 1.00f, 0.12f);
    drawBlock(program, model_loc, ongThoatNgoai, mat4(), mauOng);
}

// --- ĐIỀU KHIỂN CỬA TỦ ---
void moCanhTraiTu1()
{
    if (moCuaTraiTu1 < 90.0f)
        moCuaTraiTu1 += 5.0f;
}

void dongCanhTraiTu1()
{
    if (moCuaTraiTu1 > 0.0f)
        moCuaTraiTu1 -= 5.0f;
}

void moCanhPhaiTu1()
{
    if (moCuaPhaiTu1 < 90.0f)
        moCuaPhaiTu1 += 5.0f;
}

void dongCanhPhaiTu1()
{
    if (moCuaPhaiTu1 > 0.0f)
        moCuaPhaiTu1 -= 5.0f;
}

void moCanhTu2() { if (moCuaTu2 < 90.0f) moCuaTu2 += 5.0f; }
void dongCanhTu2() { if (moCuaTu2 > 0.0f) moCuaTu2 -= 5.0f; }

// --- ĐIỀU KHIỂN MÁY HÚT MÙI ---
void batTatMayHutMui()
{
    batMayHutMui = !batMayHutMui;

    if (!batMayHutMui)
        tocDoQuat = 0;
}

void tangTocDoQuat()
{
    if (batMayHutMui && tocDoQuat < 3)
        tocDoQuat++;
}

void giamTocDoQuat()
{
    if (batMayHutMui && tocDoQuat > 0)
        tocDoQuat--;
}

void batTatDenHutMui()
{
    batDenHutMui = !batDenHutMui;
}

void drawTuBatModel(GLuint program, GLuint model_loc, const mat4& model)
{
    drawKhungTuBat1(program, model_loc, model);
    drawKhungTuBat2(program, model_loc, model);
    drawCanhTuBat1(program, model_loc, model);
    drawCanhTuBat2(program, model_loc, model);
    drawMayHutMuiChuan(program, model_loc, model);
    drawOngThongGioGiauKinh(program, model_loc, model);
}