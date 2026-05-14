// Lap_phuong.cpp
// Hình lập phương đơn vị: tâm (0,0,0), cạnh = 1.0
// Màu mỗi đỉnh ghi sẵn vào VBO — vshader đọc thẳng qua vColor
// KHÔNG chứa main — được gọi từ main.cpp

#include "Lap_phuong.h"

typedef vec4 point4;
typedef vec4 color4;

// ---------------------------------------------------------------
// Dữ liệu nội bộ — static để tránh xung đột tên với file khác
// ---------------------------------------------------------------
static const int NUM_VERTS = 36; // 6 mặt x 2 tam giác x 3 đỉnh

static point4 cubePoints[NUM_VERTS];
static color4 cubeColors[NUM_VERTS];

// 8 đỉnh của cube đơn vị
static point4 vertices[8];

// Màu 8 đỉnh
static color4 vertex_colors[8];

static GLuint cubeVAO;
static GLuint cubeVBO;
static int    cubeIndex = 0;

// ---------------------------------------------------------------
// initCube: Gán tọa độ và màu cho 8 đỉnh
// ---------------------------------------------------------------
static void initCube()
{
    // Tọa độ 8 đỉnh — tâm tại (0,0,0), cạnh = 1.0
    vertices[0] = point4(-0.5f, -0.5f, 0.5f, 1.0f);
    vertices[1] = point4(-0.5f, 0.5f, 0.5f, 1.0f);
    vertices[2] = point4(0.5f, 0.5f, 0.5f, 1.0f);
    vertices[3] = point4(0.5f, -0.5f, 0.5f, 1.0f);
    vertices[4] = point4(-0.5f, -0.5f, -0.5f, 1.0f);
    vertices[5] = point4(-0.5f, 0.5f, -0.5f, 1.0f);
    vertices[6] = point4(0.5f, 0.5f, -0.5f, 1.0f);
    vertices[7] = point4(0.5f, -0.5f, -0.5f, 1.0f);

    // Màu 8 đỉnh
    vertex_colors[0] = color4(0.0f, 0.0f, 0.0f, 1.0f); // black
    vertex_colors[1] = color4(1.0f, 0.0f, 0.0f, 1.0f); // red
    vertex_colors[2] = color4(1.0f, 1.0f, 0.0f, 1.0f); // yellow
    vertex_colors[3] = color4(0.0f, 1.0f, 0.0f, 1.0f); // green
    vertex_colors[4] = color4(0.0f, 0.0f, 1.0f, 1.0f); // blue
    vertex_colors[5] = color4(1.0f, 0.0f, 1.0f, 1.0f); // magenta
    vertex_colors[6] = color4(1.0f, 1.0f, 1.0f, 1.0f); // white
    vertex_colors[7] = color4(0.0f, 1.0f, 1.0f, 1.0f); // cyan
}

// ---------------------------------------------------------------
// quad: Tạo 1 mặt hình lập phương = 2 tam giác, gán màu đỉnh
// ---------------------------------------------------------------
static void quad(int a, int b, int c, int d)
{
    cubeColors[cubeIndex] = vertex_colors[a]; cubePoints[cubeIndex] = vertices[a]; cubeIndex++;
    cubeColors[cubeIndex] = vertex_colors[b]; cubePoints[cubeIndex] = vertices[b]; cubeIndex++;
    cubeColors[cubeIndex] = vertex_colors[c]; cubePoints[cubeIndex] = vertices[c]; cubeIndex++;
    cubeColors[cubeIndex] = vertex_colors[a]; cubePoints[cubeIndex] = vertices[a]; cubeIndex++;
    cubeColors[cubeIndex] = vertex_colors[c]; cubePoints[cubeIndex] = vertices[c]; cubeIndex++;
    cubeColors[cubeIndex] = vertex_colors[d]; cubePoints[cubeIndex] = vertices[d]; cubeIndex++;
}

// ---------------------------------------------------------------
// makeColorCube: Sinh 12 tam giác (36 đỉnh) cho 6 mặt
// ---------------------------------------------------------------
static void makeColorCube()
{
    quad(1, 0, 3, 2); // mặt trước
    quad(2, 3, 7, 6); // mặt phải
    quad(3, 0, 4, 7); // mặt dưới
    quad(6, 5, 1, 2); // mặt trên
    quad(4, 5, 6, 7); // mặt sau
    quad(5, 4, 0, 1); // mặt trái
}

// ---------------------------------------------------------------
// LapPhuong_Init: Tạo VAO/VBO, nạp geometry lên GPU
// ---------------------------------------------------------------
void LapPhuong_Init(GLuint program)
{
    initCube();
    makeColorCube();

    // Tạo VAO
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    // Tạo VBO chứa points + colors nối tiếp nhau
    glGenBuffers(1, &cubeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(cubePoints) + sizeof(cubeColors),
        NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(cubePoints), cubePoints);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(cubePoints), sizeof(cubeColors), cubeColors);

    // Bind vPosition — đọc từ đầu VBO
    GLuint loc_vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc_vPosition);
    glVertexAttribPointer(loc_vPosition, 4, GL_FLOAT, GL_FALSE, 0,
        BUFFER_OFFSET(0));

    // Bind vColor — đọc từ sau phần points
    GLuint loc_vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(loc_vColor);
    glVertexAttribPointer(loc_vColor, 4, GL_FLOAT, GL_FALSE, 0,
        BUFFER_OFFSET(sizeof(cubePoints)));

    glBindVertexArray(0); // unbind
}

// ---------------------------------------------------------------
// LapPhuong_Draw: Gửi uModel lên shader rồi vẽ cube
// vshader nhận uModel và nhân với vPosition
// ---------------------------------------------------------------
void LapPhuong_Draw(GLuint program, Angel::mat4 const& mt)
{
    GLuint loc_model = glGetUniformLocation(program, "uModel");
    glUniformMatrix4fv(loc_model, 1, GL_TRUE, mt);

    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, NUM_VERTS);
    glBindVertexArray(0);
}

void generateGeometry() {
    cubeIndex = 0;
    initCube();
    makeColorCube();
}
