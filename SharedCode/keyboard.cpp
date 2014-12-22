#include "header.h"
#include <iostream>

void keyboard(int key, int x, int y) {
	extern float coef;
	extern ViewingLoader *viewPtr;

	switch (key) {
	case GLUT_KEY_UP:
		coef += 0.1;
		break;
	case GLUT_KEY_DOWN:
		coef -= 0.1;
		break;
	case GLUT_KEY_LEFT:
		viewPtr->rotate(true);
		break;
	case GLUT_KEY_RIGHT:
		viewPtr->rotate(false);
		break;
	default:
		return;
	}

	redisplay();
}