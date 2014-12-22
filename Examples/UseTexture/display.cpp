#include "../SharedCode/header.h"
#include <iostream>
using namespace std;

void display() {
	extern ViewingLoader *viewPtr;
	extern SceneLoader *scenePtr;
	extern GLhandleARB MyShader;
	extern float coef;

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
	if (locationColor == -1 || locationHeight == -1 || locationCoef == -1)
		cerr << "Cant find texture name: coef, colorTexture or heightTexture." << endl;
	else {
		glUniform1i(locationColor, 0);
		glUniform1i(locationHeight, 1);
		glUniform1f(locationCoef, coef);
	}

	scenePtr->displayScene();

	glutSwapBuffers();
	glFlush();
}

void redisplay() {
	glutPostRedisplay();
}