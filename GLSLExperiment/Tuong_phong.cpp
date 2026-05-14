// Tuong_phong.cpp
// Vẽ tường/sàn/trần căn phòng
// Mỗi khối = cube đơn vị (tâm 0,0,0 cạnh 1) được Scale(R,L,W) * Translate(cx,cy,cz)
// Màu đồng nhất của mỗi khối được ghi thẳng vào VBO — vshader đọc qua vColor
// → Không cần uniform color, shader luôn đọc vColor bình thường
// KHÔNG chứa main — được gọi từ main.cpp

#include "Tuong_phong.h"
#include <vector>
using namespace std;

typedef vec4 point4;
typedef vec4 color4;

// ---------------------------------------------------------------
// Cấu trúc mô tả 1 khối trong phòng
// ---------------------------------------------------------------
struct Cuboid {
    float cx, cy, cz;  // Tâm khối
    float R, L, W;   // Kích thước: X (rộng), Y (dài), Z (cao)
    float r, g, b;   // Màu RGB (0.0 – 1.0)
};

// ---------------------------------------------------------------
// Danh sách toàn bộ các khối của căn phòng
// ---------------------------------------------------------------
static Cuboid roomParts[] = {

    // --- Tường bên phải (màu kem) ---
    // Kích thước: 0.2 x 4.4 x 3.4  |  Tâm: (-0.1, 2.2, 1.6)
    { -0.1f,  2.2f,  1.6f,   0.2f, 4.4f, 3.4f,   170 / 255.f, 90 / 255.f, 80 / 255.f },

    // --- Tường bên trái (màu kem) ---
    // Kích thước: 0.2 x 4.4 x 3.4  |  Tâm: (5.1, 2.2, 1.6)
    {  5.1f,  2.2f,  1.6f,   0.2f, 4.4f, 3.4f,   170 / 255.f, 90 / 255.f, 80 / 255.f },

    // --- Sàn nhà (màu kem) ---
    // Kích thước: 5.0 x 4.0 x 0.2  |  Tâm: (2.5, 2.2, -0.1)
    {  2.5f,  2.2f, 0.0f,   5.0f, 4.0f, 0.2f,   120 / 255.f, 85 / 255.f, 60 / 255.f },

    // --- Trần nhà (màu kem) ---
    // Kích thước: 5.0 x 4.0 x 0.2  |  Tâm: (2.5, 2.2, 3.1)
    {  2.5f,  2.2f,  3.2f,   5.0f, 4.0f, 0.2f,   245 / 255.f, 235 / 255.f, 226 / 255.f },

    // --- Tường cửa vào (màu kem) ---
        // Khối bên trái cửa: 3.5 x 0.2 x 3.4  |  Tâm: (1.75, -0.1, 1.7)
        {  1.75f, 0.1f,  1.6f,   3.5f, 0.2f, 3.4f,   245 / 255.f, 235 / 255.f, 226 / 255.f },

        // Khối bên trên cửa: 1.0 x 0.2 x 1.0  |  Tâm: (4.0, -0.1, 2.7)
        {  4.0f,  0.1f,  2.8f,   1.0f, 0.2f, 1.0f,   245 / 255.f, 235 / 255.f, 226 / 255.f },

        // Khối bên phải cửa: 0.5 x 0.2 x 3.4  |  Tâm: (4.75, -0.1, 1.7)
        {  4.75f, 0.1f,  1.6f,   0.5f, 0.2f, 3.4f,   126 / 255.f, 136 / 255.f, 118 / 255.f },

    // --- Tường cửa sổ (màu xanh rêu) ---
        // Khối bên trái cửa sổ: 1.8 x 0.2 x 3.4  |  Tâm: (0.9, 4.1, 1.6)
        {  0.9f,   4.3f,  1.6f,   1.8f, 0.2f, 3.4f,   126 / 255.f, 136 / 255.f, 118 / 255.f },

        // Khối bên dưới cửa sổ: 1.4 x 0.2 x 1.0  |  Tâm: (2.5, 4.1, 0.4)
        {  2.5f,   4.3f,  0.4f,   1.4f, 0.2f, 1.0f,   126 / 255.f, 136 / 255.f, 118 / 255.f },

        // Khối bên trên cửa sổ: 1.4 x 0.2 x 1.0  |  Tâm: (2.5, 4.1, 2.5)
        {  2.5f,   4.3f,  2.8f,   1.4f, 0.2f, 1.0f,   126 / 255.f, 136 / 255.f, 118 / 255.f },

        // Khối bên phải cửa sổ: 1.8 x 0.2 x 3.4  |  Tâm: (4.1, 4.1, 1.6)
        {  4.1f,   4.3f,  1.6f,   1.8f, 0.2f, 3.4f,   126 / 255.f, 136 / 255.f, 118 / 255.f },
};

static const int NUM_PARTS = sizeof(roomParts) / sizeof(roomParts[0]);

// Mỗi khối có VAO riêng để bind đúng màu VBO của nó
static GLuint partVAO[NUM_PARTS];
// Model matrix của mỗi khối tính sẵn lúc Init
static mat4   partModel[NUM_PARTS];

// ---------------------------------------------------------------
// buildCuboidVBO: Sinh 36 đỉnh cho cube đơn vị với màu đồng nhất
// Ghi màu (r,g,b) vào tất cả 36 đỉnh trong VBO
// → vshader đọc vColor bình thường, không cần uniform nào thêm
// ---------------------------------------------------------------
static void buildCuboidVBO(GLuint vao, float r, float g, float b,
    GLuint program)
{
    // 8 đỉnh cube đơn vị (cạnh 1, tâm gốc)
    static const point4 v[8] = {
        point4(-0.5f, -0.5f,  0.5f, 1.0f), // 0
        point4(-0.5f,  0.5f,  0.5f, 1.0f), // 1
        point4(0.5f,  0.5f,  0.5f, 1.0f), // 2
        point4(0.5f, -0.5f,  0.5f, 1.0f), // 3
        point4(-0.5f, -0.5f, -0.5f, 1.0f), // 4
        point4(-0.5f,  0.5f, -0.5f, 1.0f), // 5
        point4(0.5f,  0.5f, -0.5f, 1.0f), // 6
        point4(0.5f, -0.5f, -0.5f, 1.0f), // 7
    };

    // Thứ tự đỉnh 6 mặt (mỗi mặt 2 tam giác = 6 đỉnh)
    static const int faces[36] = {
        1,0,3, 1,3,2,  // mặt trước
        2,3,7, 2,7,6,  // mặt phải
        3,0,4, 3,4,7,  // mặt dưới
        6,5,1, 6,1,2,  // mặt trên
        4,5,6, 4,6,7,  // mặt sau
        5,4,0, 5,0,1,  // mặt trái
    };

    // Sinh mảng 36 điểm và 36 màu
    point4 pts[36];
    color4 cls[36];
    color4 col(r, g, b, 1.0f);

    for (int i = 0; i < 36; i++) {
        pts[i] = v[faces[i]];
        cls[i] = col; // tất cả đỉnh cùng màu → khối đồng nhất
    }

    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pts) + sizeof(cls), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(pts), pts);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(pts), sizeof(cls), cls);

    // Bind vPosition
    GLuint loc_pos = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(loc_pos);
    glVertexAttribPointer(loc_pos, 4, GL_FLOAT, GL_FALSE, 0,
        BUFFER_OFFSET(0));

    // Bind vColor
    GLuint loc_col = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(loc_col);
    glVertexAttribPointer(loc_col, 4, GL_FLOAT, GL_FALSE, 0,
        BUFFER_OFFSET(sizeof(pts)));

    glBindVertexArray(0);
}

// ---------------------------------------------------------------
// TuongPhong_Init: Build VAO/VBO riêng cho từng khối
// Model matrix tính sẵn = Translate(cx,cy,cz) * Scale(R,L,W)
// ---------------------------------------------------------------
void TuongPhong_Init(GLuint program)
{
    glGenVertexArrays(NUM_PARTS, partVAO);

    for (int i = 0; i < NUM_PARTS; i++) {
        Cuboid& p = roomParts[i];

        // Tính model matrix: đặt tâm rồi scale theo kích thước
        partModel[i] = Translate(p.cx, p.cy, p.cz) * Scale(p.R, p.L, p.W);

        // Build VBO với màu ghi thẳng vào từng đỉnh
        buildCuboidVBO(partVAO[i], p.r, p.g, p.b, program);
    }
}

// ---------------------------------------------------------------
// TuongPhong_Draw: Vẽ từng khối với model matrix đã tính sẵn
// vshader nhận uModel + đọc vColor từ VBO của từng khối
// ---------------------------------------------------------------
void TuongPhong_Draw(GLuint program)
{
    GLuint loc_model = glGetUniformLocation(program, "uModel");

    for (int i = 0; i < NUM_PARTS; i++) {
        // Gửi model matrix của khối này lên shader
        glUniformMatrix4fv(loc_model, 1, GL_TRUE, partModel[i]);

        // Bind VAO của khối này (mang theo VBO màu riêng)
        glBindVertexArray(partVAO[i]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
}