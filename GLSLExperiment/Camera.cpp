// Camera.cpp
// Camera nhìn tự do sử dụng LookAt() từ mat.h
// Hệ tọa độ phòng: X=rộng, Y=sâu, Z=cao (trục Z hướng lên)

#include "Camera.h"
#include <cmath>

// ---------------------------------------------------------------
// Constructor: camera đứng trước cửa vào nhìn vào giữa phòng
// ---------------------------------------------------------------
Camera::Camera()
{
    position = vec3(2.5f, -3.0f, 1.7f);
    yaw = 90.0f;   // nhìn theo chiều +Y (vào phòng)
    pitch = 0.0f;
    moveSpeed = 3.0f;
    mouseSensitivity = 0.2f;
    mousePressed = false;
    lastMouseX = lastMouseY = 0;

    updateVectors();
}

// ---------------------------------------------------------------
// setPosition
// ---------------------------------------------------------------
void Camera::setPosition(float x, float y, float z)
{
    position = vec3(x, y, z);
}

// ---------------------------------------------------------------
// lookAt: tính yaw/pitch để nhìn về phía (tx, ty, tz)
// ---------------------------------------------------------------
void Camera::lookAt(float tx, float ty, float tz)
{
    float dx = tx - position.x;
    float dy = ty - position.y;
    float dz = tz - position.z;
    float len = std::sqrt(dx * dx + dy * dy + dz * dz);
    if (len > 0.0001f) { dx /= len; dy /= len; dz /= len; }

    pitch = std::asin(dz) * (180.0f / (float)M_PI);
    yaw = std::atan2(dy, dx) * (180.0f / (float)M_PI);
    updateVectors();
}

// ---------------------------------------------------------------
// getViewMatrix: dùng LookAt() từ mat.h
// ---------------------------------------------------------------
mat4 Camera::getViewMatrix() const
{
    vec4 eye(position.x, position.y, position.z, 1.0f);
    vec4 at(position.x + front.x,
        position.y + front.y,
        position.z + front.z, 1.0f);
    vec4 upV(up.x, up.y, up.z, 0.0f);

    return LookAt(eye, at, upV);
}

// ---------------------------------------------------------------
// processKeyboard: W/A/S/D tiến/trượt, Q/E lên xuống
// deltaTime (giây) chuẩn hóa tốc độ theo framerate
// ---------------------------------------------------------------
void Camera::processKeyboard(unsigned char key, float deltaTime)
{
    float v = moveSpeed * deltaTime;

    switch (key) {
    case 'w': case 'W':
        position.x += front.x * v;
        position.y += front.y * v;
        position.z += front.z * v;
        break;
    case 's': case 'S':
        position.x -= front.x * v;
        position.y -= front.y * v;
        position.z -= front.z * v;
        break;
    case 'a': case 'A':
        position.x -= right.x * v;
        position.y -= right.y * v;
        position.z -= right.z * v;
        break;
    case 'd': case 'D':
        position.x += right.x * v;
        position.y += right.y * v;
        position.z += right.z * v;
        break;
    case 'q': case 'Q':
        position.z += v;
        break;
    case 'e': case 'E':
        position.z -= v;
        break;
    }
}

// ---------------------------------------------------------------
// processMouseClick: ghi nhận trạng thái chuột trái
// ---------------------------------------------------------------
void Camera::processMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        mousePressed = (state == GLUT_DOWN);
        lastMouseX = x;
        lastMouseY = y;
    }
}

// ---------------------------------------------------------------
// processMouseMove: xoay camera khi kéo chuột trái
// ---------------------------------------------------------------
void Camera::processMouseMove(int x, int y)
{
    if (!mousePressed) return;

    yaw += (x - lastMouseX) * mouseSensitivity;
    pitch -= (y - lastMouseY) * mouseSensitivity; // dy âm = chuột lên = nhìn lên

    lastMouseX = x;
    lastMouseY = y;

    // Giới hạn pitch tránh lật ngược camera
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    updateVectors();
}

// ---------------------------------------------------------------
// updateVectors: tính front, right, up từ yaw và pitch
// Hệ tọa độ: trục Z là "lên" (worldUp = 0,0,1)
// ---------------------------------------------------------------
void Camera::updateVectors()
{
    float yr = yaw * (float)M_PI / 180.0f;
    float pr = pitch * (float)M_PI / 180.0f;

    // Vector hướng nhìn
    front.x = std::cos(pr) * std::cos(yr);
    front.y = std::cos(pr) * std::sin(yr);
    front.z = std::sin(pr);
    float lf = std::sqrt(front.x * front.x + front.y * front.y + front.z * front.z);
    front.x /= lf; front.y /= lf; front.z /= lf;

    // right = front x worldUp (worldUp = Z)
    right.x = front.y; // cross(front, Z) = (fy*1 - fz*0, fz*0 - fx*1, fx*0 - fy*0)
    right.y = -front.x;
    right.z = 0.0f;
    float lr = std::sqrt(right.x * right.x + right.y * right.y);
    if (lr > 0.0001f) { right.x /= lr; right.y /= lr; }

    // up = right x front
    up.x = right.y * front.z - right.z * front.y;
    up.y = right.z * front.x - right.x * front.z;
    up.z = right.x * front.y - right.y * front.x;
}