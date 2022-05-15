#pragma once
#include "Life.h"
#include <ctime>
#include <GL/glut.h>


#ifndef GLSCENE_H
#define GLSCENE_H

void GLScene(int argc, char* argv[]);
void Cleanup();
void newlife3d();
void DisplayGL();

void MouseWheel(int button, int state, int x, int y);
void KeyboardGL(unsigned char c, int x, int y);

void ReshapeGL(int w, int h);
void render3d();

#endif
