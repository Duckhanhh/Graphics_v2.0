#ifndef CAMERA_H
#define CAMERA_H

// Camera.h
// Camera nhìn tự do trong không gian 3D
// Điều khiển:
//   W/S       : tiến / lùi
//   A/D       : trượt trái / phải
//   Q/E       : lên / xuống
//   Kéo chuột trái : xoay nhìn (yaw / pitch)

#include "Angel.h"

class Camera {
public:
    Camera();

    // Đặt vị trí camera
    void setPosition(float x, float y, float z);

    // Đặt hướng nhìn về phía target
    void lookAt(float targetX, float targetY, float targetZ);

    // Trả về View matrix dùng LookAt() từ mat.h — truyền vào uView
    mat4 getViewMatrix() const;

    // Gọi trong glutKeyboardFunc — di chuyển camera
    void processKeyboard(unsigned char key, float deltaTime);

    // Gọi trong glutMouseFunc — ghi nhận click chuột
    void processMouseClick(int button, int state, int x, int y);

    // Gọi trong glutMotionFunc — xoay nhìn khi kéo chuột trái
    void processMouseMove(int x, int y);

private:
    vec3  position;           // Vị trí camera trong world space
    vec3  front;              // Hướng nhìn (unit vector)
    vec3  up;                 // Vector lên của camera
    vec3  right;              // Vector phải của camera

    float yaw;                // Góc xoay ngang (độ)
    float pitch;              // Góc xoay dọc  (độ)
    float moveSpeed;          // Tốc độ di chuyển (đơn vị/giây)
    float mouseSensitivity;   // Độ nhạy chuột

    bool  mousePressed;       // Đang giữ chuột trái?
    int   lastMouseX;
    int   lastMouseY;

    // Tính lại front/right/up từ yaw và pitch
    void updateVectors();
};

#endif // CAMERA_H