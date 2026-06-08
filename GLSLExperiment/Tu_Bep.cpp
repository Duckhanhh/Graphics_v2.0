#include "Tu_Bep.h"
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

    static GLfloat thetaZ = 0.0f;
    static float mocuaTrai = 0.0f;
    static float mocuaPhai = 0.0f;

	void drawMatDa(GLuint program, GLuint model_loc, const mat4& model)
	{
		mat4 daTuChinh =Translate(-0.3f, 0.0f, 0.95f)* Scale(3.48f, 0.9f, 0.10f);
		drawBlock(program, model_loc, model,daTuChinh,color4(1, 1, 1, 1));

		mat4 daTuPhu =Translate(1.6f, -0.8f, 0.95f)* Scale(0.9f, 2.45f, 0.10f);
		drawBlock(program, model_loc, model,daTuPhu,color4(1, 1, 1, 1));
	}
    void drawKhungTuChinh(
        GLuint program,
        GLuint model_loc,
        const mat4& model)
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
    void drawCanhTuChinh(
        GLuint program,
        GLuint model_loc,
        const mat4& model)
    {
        color4 mauTrang(1, 1, 1, 1);

        mat4 canh2 = Translate(0.756f, -0.39f, 0.45f)* Scale(0.73f, 0.03f, 0.80f);
        drawBlock(program, model_loc, model, canh2, mauTrang);

        mat4 canh3 =Translate(-0.031f, -0.39f, 0.45f) * Scale(0.73f, 0.03f, 0.80f);
        drawBlock(program, model_loc, model,canh3, mauTrang);

        mat4 canh4 =Translate(-0.819f, -0.39f, 0.45f)* Scale(0.73f, 0.03f, 0.80f);
        drawBlock(program, model_loc, model,canh4, mauTrang);

        mat4 canh5 = Translate(-1.606f, -0.39f, 0.45f)* Scale(0.73f, 0.03f, 0.80f);
        drawBlock(program, model_loc, model,canh5, mauTrang);
    }

    void drawKhungTuPhu(
        GLuint program,
        GLuint model_loc,
        const mat4& model)
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

    void drawTayCamTuChinh(
        GLuint program,
        GLuint model_loc,
        const mat4& model)
    {
        color4 mauTayCam(0.7f, 0.7f, 0.7f, 1.0f);

        // Cánh 2
        mat4 tayCam2 =Translate(1.05f, -0.43f, 0.45f)* Scale(0.05f, 0.02f, 0.25f);
        drawBlock(program, model_loc, model, tayCam2, mauTayCam);

        // Cánh 3
        mat4 tayCam3 =Translate(0.26f, -0.43f, 0.45f)* Scale(0.05f, 0.02f, 0.25f);
        drawBlock(program, model_loc, model, tayCam3, mauTayCam);

        // Cánh 4
        mat4 tayCam4 =Translate(-0.53f, -0.43f, 0.45f)* Scale(0.05f, 0.02f, 0.25f);
        drawBlock(program, model_loc, model, tayCam4, mauTayCam);

        // Cánh 5
        mat4 tayCam5 =Translate(-1.31f, -0.43f, 0.45f)* Scale(0.05f, 0.02f, 0.25f);
        drawBlock(program, model_loc, model, tayCam5, mauTayCam);
    }

    //void drawCanhPhaiTuPhu(
    //    GLuint program,
    //    GLuint model_loc,
    //    const mat4& model)
    //{
    //    color4 mauTrang(1, 1, 1, 1);
    //    color4 mauTayCam(0.7f, 0.7f, 0.7f, 1.0f);

    //    // Cánh 1
    //    mat4 canhPhu1 =Translate(1.21f, -1.58f, 0.45f) * Scale(0.03f, 0.75f, 0.80f);
    //    drawBlock(program, model_loc, model, canhPhu1, mauTrang);

    //    // Tay cầm cánh 1
    //    mat4 tayCam1 = Translate(1.17f , -1.38f, 0.45f) * Scale(0.02f, 0.05f, 0.2f);
    //    drawBlock(program, model_loc, model, tayCam1, mauTayCam);


    //}
    void drawCanhPhaiTuPhu(GLuint program, GLuint model_loc, const mat4& model)
    {
        color4 mauTrang(1, 1, 1, 1);
        color4 mauTayNam(0.7f, 0.7f, 0.7f, 1.0f);

        mat4 canh = Translate(0.0f, 0.375f, 0.0f)
            * Scale(0.03f, 0.75f, 0.80f);
        drawBlock(program, model_loc, model, canh, mauTrang);

        mat4 tayCam = Translate(-0.03f, 0.60f, 0.0f)
            * Scale(0.02f, 0.05f, 0.25f);
        drawBlock(program, model_loc, model, tayCam, mauTayNam);
    }
    //void drawCanhTraiTuPhu(
    //    GLuint program,
    //    GLuint model_loc,
    //    const mat4& model)
    //{
    //    color4 mauTrang(1, 1, 1, 1);
    //    color4 mauTayCam(0.7f, 0.7f, 0.7f, 1.0f);

    //    // Cánh 2
    //    mat4 canhPhu2 = Translate(1.21f, -0.80f, 0.45f) * Scale(0.03f, 0.71f, 0.80f);
    //    drawBlock(program, model_loc, model, canhPhu2, mauTrang);

    //    // Tay cầm cánh 2
    //    mat4 tayCam2 = Translate(1.17f, -1.0f, 0.45f) * Scale(0.02f, 0.05f, 0.2f);
    //    drawBlock(program, model_loc, model, tayCam2, mauTayCam);
    //}
    void drawCanhTraiTuPhu(GLuint program, GLuint model_loc, const mat4& model)
    {
        color4 mauTrang(1, 1, 1, 1);

        mat4 canh =
            Translate(0.0f, 0.355f, 0.0f)
            * Scale(0.03f, 0.71f, 0.80f);

        drawBlock(program, model_loc, model, canh, mauTrang);

        mat4 tayCam =
            Translate(-0.03f, 0.60f, 0.0f)
            * Scale(0.02f, 0.05f, 0.25f);

        drawBlock(program, model_loc, model, tayCam,
            color4(0.7f, 0.7f, 0.7f, 1));
    }

   
    void moTuPhuTrai()
    {
        if (mocuaTrai < 90.0f)
            mocuaTrai += 5.0f;
    }

    void moTuPhuPhai()
    {
        if (mocuaPhai < 90.0f)
            mocuaPhai += 5.0f;
    }

    void dongTuPhuTrai()
    {
        if (mocuaTrai > 0.0f)
            mocuaTrai -= 5.0f;
    }

    void dongTuPhuPhai()
    {
        if (mocuaPhai > 0.0f)
            mocuaPhai -= 5.0f;
    }

   
    void drawTuBepModel(
        GLuint program,
        GLuint model_loc,
        const mat4& model)
    {
        drawMatDa(program, model_loc, model);

        drawKhungTuChinh(program, model_loc, model);
        drawCanhTuChinh(program, model_loc, model);

        drawKhungTuPhu(program, model_loc, model);
        drawTayCamTuChinh(program, model_loc, model);
       // mat4 modelCuaTrai = model * Translate(0.015f, -0.375f, 0.0f) * RotateZ(mocuaTrai) * Translate(-0.015f, 0.375f, 0.0f);
        //mat4 modelCuaTrai = model  * RotateZ(mocuaTrai) ;
        mat4 modelCuaTrai = model * Translate(1.21f, -1.155f, 0.45f) * RotateZ(mocuaTrai);

        
        drawCanhTraiTuPhu(program, model_loc, modelCuaTrai);
        mat4 modelCuaPhai =
            model
            * Translate(1.21f, -1.955f, 0.45f)
            * RotateZ(mocuaPhai);
        //mat4 modelCuaPhai = model * Translate(-0.015f, 0.355f, 0.0f) * RotateZ(mocuaPhai) * Translate(0.015f, -0.355f, 0.0f);
        drawCanhPhaiTuPhu(program, model_loc, modelCuaPhai);
    }
    