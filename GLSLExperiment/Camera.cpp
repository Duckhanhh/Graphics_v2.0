#include "Camera.h"
#include <math.h>

static mat4 view;
static mat4 projection;
static GLuint view_loc;
static GLuint projection_loc;

static GLfloat camera_x = 2.5f;
static GLfloat camera_y = -6.0f;
static GLfloat camera_z = 2.0f;
static GLfloat camera_step = 0.2f;
static GLfloat zoom_size = 1.0f;
static GLfloat aspect = 1.0f;
static GLfloat yaw = 90.0f;
static GLfloat pitch = -5.0f;
static GLfloat rotate_step = 3.0f;

static void clampPitch()
{
	if (pitch > 85.0f) {
		pitch = 85.0f;
	}
	if (pitch < -85.0f) {
		pitch = -85.0f;
	}
}

static GLfloat toRadians(GLfloat degrees)
{
	return degrees * 3.1415926535f / 180.0f;
}

static void getCameraFront(vec3& front)
{
	GLfloat yaw_r = toRadians(yaw);
	GLfloat pitch_r = toRadians(pitch);

	front.x = cos(pitch_r) * cos(yaw_r);
	front.y = cos(pitch_r) * sin(yaw_r);
	front.z = sin(pitch_r);

	front = normalize(front);
}

static void getCameraRight(vec3& right)
{
	vec3 front;
	getCameraFront(front);
	right = normalize(cross(front, vec3(0.0f, 0.0f, 1.0f)));
}

static void updateProjection()
{
	const GLfloat near_plane = 0.05f;
	const GLfloat far_plane = 100.0f;
	projection = Frustum(
		-zoom_size * aspect * near_plane, zoom_size * aspect * near_plane,
		-zoom_size * near_plane, zoom_size * near_plane,
		near_plane, far_plane);
	glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);
}

static void updateView()
{
	vec3 front;
	getCameraFront(front);

	vec4 eye(camera_x, camera_y, camera_z, 1.0f);
	vec4 at(camera_x + front.x, camera_y + front.y, camera_z + front.z, 1.0f);
	vec4 up(0.0f, 0.0f, 1.0f, 0.0f);

	view = LookAt(eye, at, up);
	glUniformMatrix4fv(view_loc, 1, GL_TRUE, view);
}

void initCamera(GLuint program)
{
	view_loc = glGetUniformLocation(program, "View");
	projection_loc = glGetUniformLocation(program, "Projection");
	updateView();
	updateProjection();
}

void reshapeCamera(int width, int height)
{
	if (height == 0) {
		height = 1;
	}
	aspect = (GLfloat)width / (GLfloat)height;
	updateProjection();
	glViewport(0, 0, width, height);
}

bool keyboardCamera(unsigned char key)
{
	vec3 front;
	vec3 right;
	bool projection_changed = false;
	getCameraFront(front);
	getCameraRight(right);

	switch (key) {
	case 'w':
	case 'W':
		camera_x += front.x * camera_step;
		camera_y += front.y * camera_step;
		camera_z += front.z * camera_step;
		break;
	case 's':
	case 'S':
		camera_x -= front.x * camera_step;
		camera_y -= front.y * camera_step;
		camera_z -= front.z * camera_step;
		break;
	case 'a':
	case 'A':
		camera_x -= right.x * camera_step;
		camera_y -= right.y * camera_step;
		camera_z -= right.z * camera_step;
		break;
	case 'd':
	case 'D':
		camera_x += right.x * camera_step;
		camera_y += right.y * camera_step;
		camera_z += right.z * camera_step;
		break;
	case 'q':
		camera_z -= camera_step;
		break;
	case 'Q':
		camera_z += camera_step;
		break;
	case '<':
		yaw -= rotate_step;
		break;
	case '>':
		yaw += rotate_step;
		break;
	case '[':
		zoom_size *= 1.1f;
		projection_changed = true;
		break;
	case ']':
		zoom_size *= 0.9f;
		projection_changed = true;
		break;
	default:
		return false;
	}

	if (projection_changed) {
		if (zoom_size < 0.2f) {
			zoom_size = 0.2f;
		}
		if (zoom_size > 5.0f) {
			zoom_size = 5.0f;
		}
	}

	updateView();
	if (projection_changed) {
		updateProjection();
	}
	return true;
}

bool specialCamera(int key)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		yaw -= rotate_step;
		break;
	case GLUT_KEY_RIGHT:
		yaw += rotate_step;
		break;
	case GLUT_KEY_UP:
		pitch += rotate_step;
		clampPitch();
		break;
	case GLUT_KEY_DOWN:
		pitch -= rotate_step;
		clampPitch();
		break;
	default:
		return false;
	}

	updateView();
	return true;
}
