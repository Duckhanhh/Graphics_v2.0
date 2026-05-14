// main.cpp
// Điểm vào duy nhất — kết hợp Lap_phuong + Tuong_phong + Camera
//
// Điều khiển:
//   W/A/S/D         : tiến / trượt trái / lùi / trượt phải
//   Q/E             : lên / xuống
//   Chuột trái kéo  : xoay nhìn
//   ESC             : thoát

#include "Angel.h"
#include "Lap_phuong.h"
#include "Tuong_phong.h"
#include "Camera.h"

// ---------------------------------------------------------------
// Biến toàn cục
// ---------------------------------------------------------------
static GLuint  program;
static Camera  camera;
static int     windowWidth = 900;
static int     windowHeight = 700;
static int     lastTime = 0;
static float   deltaTime = 100.0f;

// ---------------------------------------------------------------
// buildProjection: Perspective 60° theo tỉ lệ cửa sổ
// ---------------------------------------------------------------
static mat4 buildProjection()
{
    float aspect = (float)windowWidth / (float)windowHeight;
    return Perspective(60.0f, aspect, 0.1f, 50.0f);
}

// ---------------------------------------------------------------
// display: Vẽ toàn bộ scene mỗi frame
// ---------------------------------------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // --- Gửi View và Projection lên shader (dùng chung mọi object) ---
    mat4 view = camera.getViewMatrix();
    mat4 projection = buildProjection();

    GLuint loc_view = glGetUniformLocation(program, "uView");
    glUniformMatrix4fv(loc_view, 1, GL_TRUE, view);

    GLuint loc_proj = glGetUniformLocation(program, "uProjection");
    glUniformMatrix4fv(loc_proj, 1, GL_TRUE, projection);

    // --- Vẽ tường phòng ---
    TuongPhong_Draw(program);

    glutSwapBuffers();
}

// ---------------------------------------------------------------
// keyboard: Di chuyển camera + ESC thoát
// ---------------------------------------------------------------
void keyboard(unsigned char key, int x, int y)
{
    if (key == 033) exit(0); // ESC

    float speedMultiplier = 30.0f; // Tăng tốc độ di chuyển
    camera.processKeyboard(key, deltaTime * speedMultiplier);
    glutPostRedisplay();
}

// ---------------------------------------------------------------
// mouse / mouseMotion: Xoay camera bằng chuột trái
// ---------------------------------------------------------------
void mouse(int button, int state, int x, int y)
{
    camera.processMouseClick(button, state, x, y);
}

void mouseMotion(int x, int y)
{
    camera.processMouseMove(x, y);
    glutPostRedisplay();
}

// ---------------------------------------------------------------
// reshape: Cập nhật viewport khi resize
// ---------------------------------------------------------------
void reshape(int w, int h)
{
    windowWidth = w;
    windowHeight = (h > 0) ? h : 1;
    glViewport(0, 0, windowWidth, windowHeight);
    glutPostRedisplay();
}

// ---------------------------------------------------------------
// idle: Tính deltaTime giữa các frame
// ---------------------------------------------------------------
void idle()
{
    int cur = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = (cur - lastTime) / 1000.0f;
    if (deltaTime > 0.1f) deltaTime = 0.1f;
    lastTime = cur;
    glutPostRedisplay();
}

// ---------------------------------------------------------------
// initScene: Nạp shader và khởi tạo toàn bộ đối tượng
// ---------------------------------------------------------------
void initScene()
{
    // Nạp shader — hàm InitShader khai báo trong Angel.h
    program = InitShader("vshader1.glsl", "fshader1.glsl");
    glUseProgram(program);

    // Khởi tạo cube đơn vị (dùng cho Lap_phuong và demo cube)
    LapPhuong_Init(program);

    // Khởi tạo VAO/VBO riêng cho từng khối tường
    TuongPhong_Init(program);

    // Camera: đứng trước cửa, nhìn vào giữa phòng
    camera.setPosition(2.5f, -3.0f, 1.7f);
    camera.lookAt(2.5f, 2.0f, 1.5f);

    glClearColor(0.15f, 0.15f, 0.15f, 1.0f); // Nền xám tối
    glEnable(GL_DEPTH_TEST);                 // Bật depth test
}

// ---------------------------------------------------------------
// main
// ---------------------------------------------------------------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Room Viewer  |  WASD di chuyen  |  Chuot trai xoay");

    glewInit();
    initScene();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);

    lastTime = glutGet(GLUT_ELAPSED_TIME);
    glutMainLoop();
    return 0;
}