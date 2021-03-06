#include "../SharedCode/header.h"
#include <iostream>
using namespace std;

void display() {
	extern ViewingLoader *viewPtr;
	extern SceneLoader *scenePtr;
	extern LightLoader *lightPtr;
	extern GLhandleARB MyShader;
	extern float coef;
	extern float rotate_angle;
	extern float light_angle[2];

	viewPtr->setViewing();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(MyShader);

	GLint locationColor = glGetUniformLocation(MyShader, "colorTexture");
	GLint locationHeight = glGetUniformLocation(MyShader, "heightTexture");
	GLint locationCoef = glGetUniformLocation(MyShader, "coef");
	GLint locationWidth = glGetUniformLocation(MyShader, "textureWidth");
	if (locationColor == -1 || locationHeight == -1 || locationCoef == -1 || locationWidth == -1)
		cerr << "Cant find name: textureWidth, coef, colorTexture or heightTexture." << endl;
	else {
		glUniform1i(locationColor, 0);
		glUniform1i(locationHeight, 1);
		glUniform1f(locationCoef, coef);
		glUniform1f(locationWidth, 1024.0);
	}

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
		glRotatef(light_angle[0], 0, 1, 0);
		glRotatef(light_angle[1], -1, 0, 0);
		lightPtr->setLight();
	glPopMatrix();

	glRotatef(rotate_angle, 0, 1, 0);

	scenePtr->displayScene();

	glutSwapBuffers();
	glFlush();
}

void redisplay() {
	glutPostRedisplay();
}