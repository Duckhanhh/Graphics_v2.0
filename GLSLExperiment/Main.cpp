#include "Angel.h"
#include "Camera.h"
#include "Lap_phuong.h"
#include "Tuong_phong.h"

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

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	model = mat4();
	drawTuongPhong(program, model_loc, model);

	glutSwapBuffers();
}

void reshape(int width, int height)
{
	reshapeCamera(width, height);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 033:
		exit(1);
		break;
	default:
		if (keyboardCamera(key)) {
			glutPostRedisplay();
		}
		break;
	}
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
