#include "header.h"

void keyboard(int key, int x, int y) {
	extern float coef;
	extern float rotate_angle;

	switch (key) {
	case GLUT_KEY_UP:
		coef += 0.1;
		break;
	case GLUT_KEY_DOWN:
		coef -= 0.1;
		break;
	case GLUT_KEY_LEFT:
		rotate_angle += 5;
		break;
	case GLUT_KEY_RIGHT:
		rotate_angle -= 5;
		break;
	default:
		return;
	}

	redisplay();
}