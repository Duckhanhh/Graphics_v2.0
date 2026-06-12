#include "Angel.h"
#include "Camera.h"
#include "Lap_phuong.h"
#include "Tuong_phong.h"
#include "Tu_lanh.h"
#include "Cua_so.h"
#include "Lo_hoa.h"
#include "Ban_an.h"
#include "Ghe.h"
#include "Tivi.h"
#include "Dia.h"
#include "Tu_Bep.h"

typedef vec4 point4;
typedef vec4 color4;

GLuint program;
GLuint model_loc;
mat4 model;

void setDefaultMaterial(void)
{
	point4 light_position(0.0f, 0.0f, 1.0f, 0.0f);
	color4 light_ambient(0.2f, 0.2f, 0.2f, 1.0f);
	color4 light_diffuse(1.0f, 1.0f, 1.0f, 1.0f);
	color4 light_specular(1.0f, 1.0f, 1.0f, 1.0f);

	color4 material_ambient(1.0f, 1.0f, 1.0f, 1.0f);
	color4 material_diffuse(1.0f, 1.0f, 1.0f, 1.0f);
	color4 material_specular(0.2f, 0.2f, 0.2f, 1.0f);
	float material_shininess = 50.0f;

	color4 ambient_product = light_ambient * material_ambient;
	color4 diffuse_product = light_diffuse * material_diffuse;
	color4 specular_product = light_specular * material_specular;

	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular_product);
	glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);
	glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);
}


void shaderSetup(void)
{
	// Nap cac shader va su dung chuong trinh shader
	program = InitShader("vshader1.glsl", "fshader1.glsl");
	glUseProgram(program);

	model_loc = glGetUniformLocation(program, "Model");
	setDefaultMaterial();

	initLapPhuong(program);
	initCamera(program);
	initDiaTron(program);//Thêm vào để vẽ đĩa tròn
	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

GLfloat keo_ghe = 0.0f;
GLfloat keo_ghe_1 = 0.0f;
GLfloat keo_ghe_2 = 0.0f;
GLfloat keo_ghe_3 = 0.0f;
GLfloat keo_ghe_4 = 0.0f;

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model = mat4();
	drawTuongPhong(program, model_loc, model);

	mat4 modelTuLanh = model
		* Translate(-2.051f, 1.5925f, 0.0f);
	drawTuLanh(program, model_loc, modelTuLanh);

	mat4 modelCuaSo = model * Translate(0.0f, 2.1f, 1.7f) * RotateX(90.0f) * Scale(1.4f, 1.4f, 1.4f);
	drawCuaSo(program, model_loc, modelCuaSo);

	mat4 modelLoHoa = model * Translate(-0.2f, -0.2f, 0.6f);
	drawLoHoa(program, model_loc, modelLoHoa);

	mat4 modelBanAn = model * Translate(-0.2f, -0.2f, 0.0f);
	veBanAn(program, model_loc, modelBanAn);
	
	veDia(program, model_loc, modelBanAn, 0.75f);

	mat4 modelGhe1 = modelBanAn * Translate(-0.45f - keo_ghe - keo_ghe_1, -0.15f , 0.0f) * RotateZ(90.0f);
	veGhe(program, model_loc, modelGhe1);

	mat4 modelGhe2 = modelBanAn * Translate(-0.45f - keo_ghe - keo_ghe_2, 0.15f, 0.0f) * RotateZ(90.0f);
	veGhe(program, model_loc, modelGhe2);

	mat4 modelGhe3 = modelBanAn * Translate(0.45f + keo_ghe + keo_ghe_3, -0.15f , 0.0f) * RotateZ(270.0f);
	veGhe(program, model_loc, modelGhe3);

	mat4 modelGhe4 = modelBanAn * Translate(0.45f + keo_ghe + keo_ghe_4, 0.15f, 0.0f) * RotateZ(270.0f);
	veGhe(program, model_loc, modelGhe4);

	mat4 modelVeTV = model * Translate(-0.5f, -1.85f, 0.0f) * RotateX(90.0f);
	veTiviVaKe(program, model_loc, modelVeTV);

	mat4 modelDK = modelVeTV * Translate(-0.5f, 0.2f, 0.3f / 2.0f - 0.1f);
	veDieuKhien(program, model_loc, modelDK);

	mat4 tuBep =model *Translate(0.5f, 1.48f, 0.0f) * Scale(1.0f, 0.8f, 1.0f);
	drawTuBepModel(program,model_loc,tuBep);

	glutSwapBuffers();
}

void reshape(int width, int height)
{
	reshapeCamera(width, height);
}

bool isTvOn = false;
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 033:
		exit(1);
		break;
	//Đóng mở tủ lạnh
	case 'e':
		moCuaTraiTuLanh();
		break;
	case 'E':
		dongCuaTraiTuLanh();
		break;
	case 'r':
		moCuaPhaiTuLanh();
		break;
	case 'R':
		dongCuaPhaiTuLanh();
		break;
	//đóng mở cửa sổ
	case 'c':
		moCuaSo();
		break;
	case 'C':
		dongCuaSo();
		break;
	case 'm':
		if (keo_ghe_1 < 0.5f) {
			keo_ghe_1 += 0.05f;
		}
		break;
		//Đẩy 4 ghế vào
	case 'M':
		if (keo_ghe_1 > 0.0f) {
			keo_ghe_1 -= 0.05f;
		}
		break;
	case 'n':
		if (keo_ghe_2 < 0.5f) {
			keo_ghe_2 += 0.05f;
		}
		break;
		//Đẩy 4 ghế vào
	case 'N':
		if (keo_ghe_2 > 0.0f) {
			keo_ghe_2 -= 0.05f;
		}
		break;
	case 'p':
		if (keo_ghe_3 < 0.5f) {
			keo_ghe_3 += 0.05f;
		}
		break;
		//Đẩy 4 ghế vào
	case 'P':
		if (keo_ghe_3 > 0.0f) {
			keo_ghe_3 -= 0.05f;
		}
		break;
	case 'v':
		if (keo_ghe_4 < 0.5f) {
			keo_ghe_4 += 0.05f;
		}
		break;
		//Đẩy 4 ghế vào
	case 'V':
		if (keo_ghe_4 > 0.0f) {
			keo_ghe_4 -= 0.05f;
		}
		break;
	//Điều khiển tắt bật tivi
	case 't': 
	case 'T':
		isTvOn = !isTvOn;
		break;
	case 'h':
		moTuPhuPhai();
		glutPostRedisplay();
		break;
	case 'H':
		dongTuPhuPhai();
		glutPostRedisplay();
		break;
	case 'g':
		moTuPhuTrai();
		glutPostRedisplay();
		break;
	case 'G':
		dongTuPhuTrai();
		glutPostRedisplay();
		break;
	case '1':
		keoNganTu1();
		glutPostRedisplay();
		break;
	case '2':
		dongNganTu1();
		glutPostRedisplay();
		break;
	case '3':
		keoNganTu2();
		glutPostRedisplay();
		break;
	case '4':
		dongNganTu2();
		glutPostRedisplay();
		break;
	case 'b':
		batTatBepGa();
		glutPostRedisplay();
		break;
	default:
		if (keyboardCamera(key)) {
			
		}
		break;

	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (mouseCamera(button, state, x, y)) {
		glutPostRedisplay();
	}
}

void motion(int x, int y)
{
	if (motionCamera(x, y)) {
		glutPostRedisplay();
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Tuong phong");
	std::cout << "\n========== PHIM DIEU KHIEN ==========\n"
		<< "ESC       : Thoat chuong trinh\n"
		<< "W / S     : Camera tien / lui\n"
		<< "A         : Camera sang trai\n"
		<< "D         : Camera sang phai\n"
		<< "e / E     : Mo / dong cua trai tu lanh\n"
		<< "r / R     : Mo / dong cua phai tu lanh\n"
		<< "c / C     : Mo / dong cua so\n"
		<< "k / d     : Keo / day nhom ghe chinh\n"
		<< "m / M     : Keo / day nhom ghe 1\n"
		<< "n / N     : Keo / day nhom ghe 2\n"
		<< "p / P     : Keo / day nhom ghe 3\n"
		<< "q / Q     : Keo / day nhom ghe 4\n"
		<< "t / T     : Bat / tat TV\n"
		<< "h / H     : Mo / dong tu phu phai\n"
		<< "g / G     : Mo / dong tu phu trai\n"
		<< "1 / 2     : Keo / dong ngan tu 1\n"
		<< "3 / 4     : Keo / dong ngan tu 2\n"
		<< "b         : Bat / tat bep ga\n"
		<< "Chuot trai: Xoay camera\n"
		<< "====================================\n\n";

	glewInit();

	shaderSetup();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);

	glutMainLoop();
	return 0;
}
