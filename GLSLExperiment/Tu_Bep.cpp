#include "Tu_Bep.h"
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

    static GLfloat thetaZ = 0.0f;
    static float mocuaTrai = 0.0f;
    static float mocuaPhai = 0.0f;
    static float keoNgan1 = 0.0f;
    static float keoNgan2 = 0.0f;
    static bool batBepGa = false;

    
    // Vẽ khung của tủ bếp chính
    void drawKhungTuChinh( GLuint program,GLuint model_loc, const mat4& model)
    {
        color4 mauGo(0.55f, 0.35f, 0.18f, 1);
        
        mat4 trenTuChinh =Translate(-0.3f, 0.0f, 0.875f) * Scale(3.4f, 0.8f, 0.05f);
        drawBlock(program, model_loc, model, trenTuChinh, mauGo);

        mat4 dayTuChinh = Translate(-0.3f, 0.0f, 0.03f)* Scale(3.4f, 0.8f, 0.05f);
        drawBlock(program, model_loc, model, dayTuChinh, mauGo);

        mat4 canhTrai =Translate(-2.0f, 0.0f, 0.45f)* Scale(0.05f, 0.8f, 0.90f);
        drawBlock(program, model_loc, model,canhTrai, mauGo);

        mat4 sauTuChinh =Translate(-0.3f, 0.375f, 0.45f)* Scale(3.4f, 0.05f, 0.85f);
        drawBlock(program, model_loc, model, sauTuChinh, mauGo);

        mat4 vachNgan1 =Translate(1.15f, 0.0f, 0.45f)* Scale(0.08f, 0.8f, 0.80f);
        drawBlock(program, model_loc, model,vachNgan1, mauGo);

        mat4 vachNgan2 =Translate(0.3625f, 0.0f, 0.45f)* Scale(0.05f, 0.8f, 0.80f);
        drawBlock(program, model_loc, model,vachNgan2, mauGo);

        mat4 vachNgan3 =Translate(-0.425f, 0.0f, 0.45f) * Scale(0.05f, 0.8f, 0.80f);
        drawBlock(program, model_loc, model,vachNgan3, mauGo);

        mat4 vachNgan4 =Translate(-1.2125f, 0.0f, 0.45f)* Scale(0.05f, 0.8f, 0.80f);
        drawBlock(program, model_loc, model,vachNgan4, mauGo);
    }
    // Vẽ khung tủ phụ bên phải
    void drawKhungTuPhu(GLuint program,GLuint model_loc,const mat4& model)
    {
        color4 mauGo(0.55f, 0.35f, 0.18f, 1);

        mat4 dayTuPhu = Translate(1.6f, -0.8f, 0.025f) * Scale(0.8f, 2.4f, 0.05f);
        drawBlock(program, model_loc, model, dayTuPhu, mauGo);

        mat4 vachPhai = Translate(1.975f, -0.8f, 0.45f) * Scale(0.05f, 2.4f, 0.80f);
        drawBlock(program, model_loc, model, vachPhai, mauGo);

        mat4 matSau = Translate(1.6f, 0.375f, 0.45f) * Scale(0.75f, 0.05f, 0.80f);
        drawBlock(program, model_loc, model, matSau, mauGo);

        mat4 trenTuPhu = Translate(1.6f, -0.8f, 0.875f) * Scale(0.8f, 2.4f, 0.05f);
        drawBlock(program, model_loc, model, trenTuPhu, mauGo);

        mat4 vach1 = Translate(1.61f, -1.98f, 0.45f) * Scale(0.819f, 0.05f, 0.8f);
        drawBlock(program, model_loc, model, vach1, color4(0.65f, 0.45f, 0.25f, 1));

        mat4 vach2 = Translate(1.61f, -1.18f, 0.45f) * Scale(0.819f, 0.05f, 0.8f);
        drawBlock(program, model_loc, model, vach2, color4(0.65f, 0.45f, 0.25f, 1));

        mat4 vach3 = Translate(1.61f, -0.42f, 0.45f) * Scale(0.819f, 0.05f, 0.8f);
        drawBlock(program, model_loc, model, vach3, color4(0.65f, 0.45f, 0.25f, 1));
    }
    // Vẽ mặt đá bếp chính + phụ
    void drawMatDa(GLuint program, GLuint model_loc, const mat4& model)
    {
        mat4 daTuChinh = Translate(-0.3f, -0.025f, 0.95f) * Scale(3.48f, 0.9f, 0.10f);
        drawBlock(program, model_loc, model, daTuChinh, color4(1, 1, 1, 1));

        mat4 daTuPhu = Translate(1.6f, -0.8f, 0.95f) * Scale(0.9f, 2.45f, 0.10f);
        drawBlock(program, model_loc, model, daTuPhu, color4(1, 1, 1, 1));
    }
    // Vẽ 4 cánh tủ chính 
    void drawCanhTuChinh(GLuint program, GLuint model_loc, const mat4& model)
    {
        color4 mauTrang(1, 1, 1, 1);

        mat4 canh1 = Translate(0.756f, -0.39f, 0.45f) * Scale(0.73f, 0.03f, 0.80f);
        drawBlock(program, model_loc, model, canh1, mauTrang);

        mat4 canh2 = Translate(-0.031f, -0.39f, 0.45f) * Scale(0.73f, 0.03f, 0.80f);
        drawBlock(program, model_loc, model, canh2, mauTrang);

        mat4 canh3 = Translate(-0.819f, -0.39f, 0.45f) * Scale(0.73f, 0.03f, 0.80f);
        drawBlock(program, model_loc, model, canh3, mauTrang);

        mat4 canh4 = Translate(-1.606f, -0.39f, 0.45f) * Scale(0.73f, 0.03f, 0.80f);
        drawBlock(program, model_loc, model, canh4, mauTrang);
    }
    // Vẽ tay cầm của các cánh tủ chính
    void drawTayCamTuChinh(GLuint program, GLuint model_loc,const mat4& model)
    {
        color4 mauTayCam(0.7f, 0.7f, 0.7f, 1.0f);

        // Cánh 1
        mat4 tayCam1 =Translate(1.05f, -0.43f, 0.45f)* Scale(0.05f, 0.02f, 0.25f);
        drawBlock(program, model_loc, model, tayCam1, mauTayCam);

        // Cánh 2
        mat4 tayCam2 =Translate(0.26f, -0.43f, 0.45f)* Scale(0.05f, 0.02f, 0.25f);
        drawBlock(program, model_loc, model, tayCam2, mauTayCam);

        // Cánh 3
        mat4 tayCam3 =Translate(-0.53f, -0.43f, 0.45f)* Scale(0.05f, 0.02f, 0.25f);
        drawBlock(program, model_loc, model, tayCam3, mauTayCam);

        // Cánh 4
        mat4 tayCam4 =Translate(-1.31f, -0.43f, 0.45f)* Scale(0.05f, 0.02f, 0.25f);
        drawBlock(program, model_loc, model, tayCam4, mauTayCam);
    }
	// Vẽ 2 cánh tủ phụ bên phải + tay cầm
    void drawCanhTuPhu(GLuint program, GLuint model_loc, const mat4& model)
    {
        color4 mauTrang(1, 1, 1, 1);
        color4 mauTayNam(0.7f, 0.7f, 0.7f, 1.0f);

        // <<<<<<<<<<<CÁNH CỬA TRÁI TỦ PHỤ >>>>>>>>>>>>>>
        mat4 modelCuaTrai = model * Translate(1.21f, -1.155f, 0.45f) * RotateZ(mocuaTrai);

        mat4 canhTrai = Translate(0.0f, 0.355f, 0.0f) * Scale(0.03f, 0.71f, 0.80f);
        drawBlock(program, model_loc, modelCuaTrai, canhTrai, mauTrang);

        mat4 tayCamTrai = Translate(-0.03f, 0.60f, 0.0f) * Scale(0.02f, 0.05f, 0.25f);
        drawBlock(program, model_loc, modelCuaTrai, tayCamTrai, mauTayNam);


        // <<<<<<<<<<<CÁNH CỬA PHẢI TỦ PHỤ >>>>>>>>>>>>>>
        mat4 modelCuaPhai = model * Translate(1.21f, -1.955f, 0.45f) * RotateZ(mocuaPhai);

        mat4 canhPhai = Translate(0.0f, 0.375f, 0.0f) * Scale(0.03f, 0.75f, 0.80f);
        drawBlock(program, model_loc, modelCuaPhai, canhPhai, mauTrang);

        mat4 tayCamPhai = Translate(-0.03f, 0.60f, 0.0f) * Scale(0.02f, 0.05f, 0.25f);
        drawBlock(program, model_loc, modelCuaPhai, tayCamPhai, mauTayNam);
    }
    
	// Vẽ ngăn kéo + đồ vật bên trong ngăn kéo 2 tủ
    void drawNganKeoVaDoVat(GLuint program, GLuint model_loc, const mat4& model)
    {
        color4 mauGo(0.55f, 0.35f, 0.18f, 1);
        color4 mauTayNam(0.7f, 0.7f, 0.7f, 1);
        color4 mauDo(0.9f, 0.1f, 0.1f, 1);
        color4 mauXanh(0.1f, 0.4f, 0.9f, 1);
        color4 mauVang(1.0f, 0.8f, 0.1f, 1);
        color4 mauTrang(1, 1, 1, 1);
        color4 mauDen(0.05f, 0.05f, 0.05f, 1);

        // <<<<<<<<<<< NGĂN KÉO 1 >>>>>>>>>>>>>>
        mat4 modelNgan1 = model* Translate(1.32f - keoNgan1, -1.58f, 0.25f);

        mat4 tamNgang1 = Translate(0.30f, 0.0f, 0.0f) * Scale(0.70f, 0.72f, 0.04f);
        drawBlock(program, model_loc, modelNgan1, tamNgang1, mauGo);

        mat4 tayNam1 = Translate(-0.05f, 0.0f, 0.03f)* Scale(0.03f, 0.25f, 0.05f);
        drawBlock(program, model_loc, modelNgan1, tayNam1, mauTayNam);

        mat4 thanChai1 = Translate(0.10f, -0.25f, 0.22f) * Scale(0.12f, 0.12f, 0.35f);
        drawBlock(program, model_loc, modelNgan1, thanChai1, mauDo);

        mat4 coChai1 = Translate(0.10f, -0.25f, 0.45f)* Scale(0.07f, 0.07f, 0.12f);
        drawBlock(program, model_loc, modelNgan1, coChai1, mauDo);

        mat4 napChai1 = Translate(0.10f, -0.25f, 0.54f)* Scale(0.08f, 0.08f, 0.05f);
        drawBlock(program, model_loc, modelNgan1, napChai1, mauDen);

        mat4 thanChai2 = Translate(0.38f, 0.22f, 0.18f) * Scale(0.10f, 0.10f, 0.27f);
        drawBlock(program, model_loc, modelNgan1, thanChai2, mauXanh);

        mat4 napChai2 = Translate(0.38f, 0.22f, 0.36f) * Scale(0.07f, 0.07f, 0.05f);
        drawBlock(program, model_loc, modelNgan1, napChai2, mauTrang);

        // <<<<<<<<<<< NGĂN KÉO 2 >>>>>>>>>>>>>>
        mat4 modelNgan2 = model * Translate(1.32f - keoNgan2, -0.80f, 0.25f);

        mat4 tamNgang2 = Translate(0.30f, 0.0f, 0.0f) * Scale(0.70f, 0.72f, 0.04f);
        drawBlock(program, model_loc, modelNgan2, tamNgang2, mauGo);

        mat4 tayNam2 = Translate(-0.05f, 0.0f, 0.03f)* Scale(0.03f, 0.25f, 0.05f);
        drawBlock(program, model_loc, modelNgan2, tayNam2, mauTayNam);

        mat4 thanChai3 = Translate(0.10f, -0.22f, 0.22f)* Scale(0.12f, 0.12f, 0.35f);
        drawBlock(program, model_loc, modelNgan2, thanChai3, mauVang);

        mat4 coChai3 = Translate(0.10f, -0.22f, 0.45f)* Scale(0.07f, 0.07f, 0.12f);
        drawBlock(program, model_loc, modelNgan2, coChai3, mauVang);

        mat4 napChai3 = Translate(0.10f, -0.22f, 0.54f) * Scale(0.08f, 0.08f, 0.05f);
        drawBlock(program, model_loc, modelNgan2, napChai3, mauDen);

        mat4 hopNho = Translate(0.38f, 0.22f, 0.15f) * Scale(0.18f, 0.15f, 0.22f);
        drawBlock(program, model_loc, modelNgan2, hopNho, mauXanh);
    }
	// Vẽ bếp ga + các chi tiết của bếp ga
    void drawBepGa(GLuint program, GLuint model_loc, const mat4& model)
    {
        color4 mauDen(0.02f, 0.02f, 0.02f, 1);
        color4 mauXam(0.25f, 0.25f, 0.25f, 1);
        color4 mauXamDam(0.12f, 0.12f, 0.12f, 1);
        color4 mauBac(0.65f, 0.65f, 0.65f, 1);
        color4 mauLua(1.0f, 0.25f, 0.0f, 1);
        color4 mauVang(1.0f, 0.8f, 0.0f, 1);

        mat4 modelBepGa = model * Translate(1.6f, -0.8f, 1.02f);

        // Mặt kính bếp ga
        mat4 matBep = Translate(0.0f, 0.0f, 0.0f) * Scale(0.65f, 1.15f, 0.04f);
        drawBlock(program, model_loc, modelBepGa, matBep, mauDen);

        // <<<<<<<<<<< BẾP GA 1 >>>>>>>>>>>>>>
        mat4 modelBep1 = modelBepGa* Translate(0.0f, -0.30f, 0.015f);

        mat4 deBep1 = Translate(0.0f, 0.0f, 0.02f) * Scale(0.36f, 0.36f, 0.04f);
        drawBlock(program, model_loc, modelBep1, deBep1, mauXamDam);

        mat4 vongBep1 = Translate(0.0f, 0.0f, 0.06f) * Scale(0.24f, 0.24f, 0.04f);
        drawBlock(program, model_loc, modelBep1, vongBep1, mauXam);

        mat4 tamBep1 = Translate(0.0f, 0.0f, 0.10f) * Scale(0.12f, 0.12f, 0.04f);
        drawBlock(program, model_loc, modelBep1, tamBep1, mauBac);

        if (batBepGa)
        {
            mat4 lua1 = Translate(0.0f, 0.0f, 0.16f) * Scale(0.16f, 0.16f, 0.12f);
            drawBlock(program, model_loc, modelBep1, lua1, mauLua);

            mat4 loiLua1 = Translate(0.0f, 0.0f, 0.22f) * Scale(0.08f, 0.08f, 0.08f);
            drawBlock(program, model_loc, modelBep1, loiLua1, mauVang);
        }

        //  <<<<<<<<<<< BẾP GA 2 >>>>>>>>>>>>>>
        mat4 modelBep2 = modelBepGa* Translate(0.0f, 0.30f, 0.015f);

        mat4 deBep2 = Translate(0.0f, 0.0f, 0.02f) * Scale(0.36f, 0.36f, 0.04f);
        drawBlock(program, model_loc, modelBep2, deBep2, mauXamDam);

        mat4 vongBep2 = Translate(0.0f, 0.0f, 0.06f) * Scale(0.24f, 0.24f, 0.04f);
        drawBlock(program, model_loc, modelBep2, vongBep2, mauXam);

        mat4 tamBep2 = Translate(0.0f, 0.0f, 0.10f) * Scale(0.12f, 0.12f, 0.04f);
        drawBlock(program, model_loc, modelBep2, tamBep2, mauBac);

        if (batBepGa)
        {
            mat4 lua2 = Translate(0.0f, 0.0f, 0.16f) * Scale(0.16f, 0.16f, 0.12f);
            drawBlock(program, model_loc, modelBep2, lua2, mauLua);

            mat4 loiLua2 = Translate(0.0f, 0.0f, 0.22f)  * Scale(0.08f, 0.08f, 0.08f);
            drawBlock(program, model_loc, modelBep2, loiLua2, mauVang);
        }
    }
	// Vẽ bồn rửa + các chi tiết của bồn rửa
    void drawBonRua(GLuint program, GLuint model_loc, const mat4& model)
    {
        color4 mauBac(0.75f, 0.75f, 0.75f, 1);
        color4 mauDen(0.10f, 0.10f, 0.10f, 1);

        // <<<<<<<<<<< BỒN RỬA >>>>>>>>>>>>>>

        // Thành sau
        mat4 thanhSau = Translate(-1.15f, 0.18f, 1.08f) * Scale(0.75f, 0.04f, 0.20f);
        drawBlock(program, model_loc, model, thanhSau, mauBac);

        // Thành trước
        mat4 thanhTruoc = Translate(-1.15f, -0.28f, 1.08f) * Scale(0.75f, 0.04f, 0.20f);
        drawBlock(program, model_loc, model, thanhTruoc, mauBac);

        // Thành trái
        mat4 thanhTrai = Translate(-1.50f, -0.05f, 1.08f) * Scale(0.04f, 0.46f, 0.20f);
        drawBlock(program, model_loc, model, thanhTrai, mauBac);

        // Thành phải
        mat4 thanhPhai = Translate(-0.80f, -0.05f, 1.08f)* Scale(0.04f, 0.46f, 0.20f);
        drawBlock(program, model_loc, model, thanhPhai, mauBac);

        // Mặt đáy
        mat4 dayBon = Translate(-1.15f, -0.05f, 1.00f)* Scale(0.65f, 0.38f, 0.04f);
        drawBlock(program, model_loc, model, dayBon, mauBac);

        // Lỗ thoát nước
        mat4 loThoat = Translate(-1.15f, -0.05f, 1.04f) * Scale(0.08f, 0.08f, 0.025f);
        drawBlock(program, model_loc, model, loThoat, mauDen);

        // <<<<<<<<<<< VÒI NƯỚC >>>>>>>>>>>>>>
        mat4 chanVoi = Translate(-1.15f, 0.20f, 1.22f) * Scale(0.035f, 0.035f, 0.35f);
        drawBlock(program, model_loc, model, chanVoi, mauBac);

        mat4 canhNgang = Translate(-1.15f, 0.09f, 1.39f) * Scale(0.035f, 0.26f, 0.035f);
        drawBlock(program, model_loc, model, canhNgang, mauBac);

        mat4 dauVoi = Translate(-1.15f, -0.02f, 1.31f)* Scale(0.035f, 0.035f, 0.16f);
        drawBlock(program, model_loc, model, dauVoi, mauBac);
    }

    void drawLoMam(GLuint program, GLuint model_loc, const mat4& model)
    {
        color4 mauNau(0.45f, 0.22f, 0.05f, 1);
        color4 mauVang(0.95f, 0.75f, 0.25f, 1);
        color4 mauDo(0.8f, 0.05f, 0.05f, 1);
        color4 mauDen(0.05f, 0.05f, 0.05f, 1);
        color4 mauTrang(1, 1, 1, 1);

        // Lọ mắm 1
        mat4 thanLo1 = Translate(0.75f, 0.20f, 1.15f)* Scale(0.12f, 0.12f, 0.30f);
        drawBlock(program, model_loc, model, thanLo1, mauNau);

        mat4 nhanLo1 = Translate(0.75f, 0.135f, 1.15f)* Scale(0.10f, 0.01f, 0.12f);
        drawBlock(program, model_loc, model, nhanLo1, mauTrang);

        mat4 napLo1 = Translate(0.75f, 0.20f, 1.33f)* Scale(0.10f, 0.10f, 0.06f);
        drawBlock(program, model_loc, model, napLo1, mauDo);

        // Lọ mắm 2
        mat4 thanLo2 = Translate(0.95f, 0.20f, 1.12f)* Scale(0.10f, 0.10f, 0.24f);
        drawBlock(program, model_loc, model, thanLo2, mauVang);

        mat4 nhanLo2 = Translate(0.95f, 0.145f, 1.12f) * Scale(0.08f, 0.01f, 0.10f);
        drawBlock(program, model_loc, model, nhanLo2, mauTrang);

        mat4 napLo2 = Translate(0.95f, 0.20f, 1.27f)* Scale(0.08f, 0.08f, 0.05f);
        drawBlock(program, model_loc, model, napLo2, mauDen);

        // Lọ mắm 3
        mat4 thanLo3 = Translate(1.12f, 0.20f, 1.13f) * Scale(0.09f, 0.09f, 0.26f);
        drawBlock(program, model_loc, model, thanLo3, mauNau);

        mat4 nhanLo3 = Translate(1.12f, 0.15f, 1.13f)* Scale(0.07f, 0.01f, 0.10f);
        drawBlock(program, model_loc, model, nhanLo3, mauTrang);

        mat4 napLo3 = Translate(1.12f, 0.20f, 1.29f)* Scale(0.07f, 0.07f, 0.05f);
        drawBlock(program, model_loc, model, napLo3, mauDo);
    }

    // Mở cánh cửa trái tủ phụ
    void moTuPhuTrai()
    {
        if (mocuaTrai < 90.0f)
            mocuaTrai += 5.0f;
    }
    // Mở cánh cửa phải tủ phụ
    void moTuPhuPhai()
    {
        if (mocuaPhai < 90.0f)
            mocuaPhai += 5.0f;
    }
    // Đóng cánh cửa trái tủ phụ
    void dongTuPhuTrai()
    {
        if (mocuaTrai > 0.0f)
            mocuaTrai -= 5.0f;
    }
    // Đóng cánh cửa phải tủ phụ
    void dongTuPhuPhai()
    {
        if (mocuaPhai > 0.0f)
            mocuaPhai -= 5.0f;
    }
	// Kéo ngăn tủ 1 ra
    void keoNganTu1()
    {
        if (keoNgan1 < 0.45f)
            keoNgan1 += 0.05f;
    }
	// Đóng ngăn tủ 1 lại
    void dongNganTu1()
    {
        if (keoNgan1 > 0.0f)
            keoNgan1 -= 0.05f;
    }
	// Kéo ngăn tủ 2 ra
    void keoNganTu2()
    {
        if (keoNgan2 < 0.45f)
            keoNgan2 += 0.05f;
    }
	// Đóng ngăn tủ 2 lại
    void dongNganTu2()
    {
        if (keoNgan2 > 0.0f)
            keoNgan2 -= 0.05f;
    }
    void batTatBepGa()
    {
        batBepGa = !batBepGa;
    }



	//HÀM TỔNG HỢP VẼ TOÀN BỘ MÔ HÌNH TỦ BẾP
    void drawTuBepModel(GLuint program,GLuint model_loc, const mat4& model)
    {
        drawKhungTuChinh(program, model_loc, model);
        drawCanhTuChinh(program, model_loc, model);

        drawKhungTuPhu(program, model_loc, model);
        drawMatDa(program, model_loc, model);

        drawTayCamTuChinh(program, model_loc, model);

        drawCanhTuPhu(program, model_loc, model);

        drawNganKeoVaDoVat(program, model_loc, model);
        drawBepGa(program, model_loc, model);
        drawBonRua(program, model_loc, model);
        drawLoMam(program, model_loc, model);
    }
    