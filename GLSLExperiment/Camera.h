#ifndef CAMERA_H
#define CAMERA_H

#include "Angel.h"

void initCamera(GLuint program);
void reshapeCamera(int width, int height);
bool keyboardCamera(unsigned char key);
bool specialCamera(int key);
bool mouseCamera(int button, int state, int x, int y);
bool motionCamera(int x, int y);

#endif
