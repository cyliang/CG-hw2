#pragma once

#include <GL/glew.h>
#include <GL/glut.h>
#include "light.h"
#include "scene.h"
#include "viewing.h"

void display();
void reshape(GLsizei, GLsizei);
void keyboard(int, int, int);
void redisplay();

