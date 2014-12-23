#include "../SharedCode/ShaderLoader.h"
#include "../SharedCode/header.h"

#include <iostream>
using namespace std;

ViewingLoader *viewPtr;
SceneLoader *scenePtr;
GLhandleARB MyShader;

float coef = 2;
float rotate_angle = 0;

void LoadShaders();

int main(int argc, char *argv[]) {
	if (argc != 5) {
		cerr << "Usage: " << argv[0] << " <view_file> <scene_file>" << endl;
		return -1;
	}
	viewPtr = new ViewingLoader(argv[1]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(viewPtr->getWidth(), viewPtr->getHeight());
	glutCreateWindow("GL-Assignment1 0116229");

	if (glewInit() != GLEW_OK)
		return -1;

	scenePtr = new SceneLoader(argv[2], (const char **) argv + 3);
	LoadShaders();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(keyboard);
	glutMainLoop();
	return 0;
}

void reshape(GLsizei w, GLsizei h) {
	viewPtr->setWidthHeight(w, h);
}

void LoadShaders()
{
	MyShader = glCreateProgram();
	if (MyShader != 0)
	{
		ShaderLoad(MyShader, "../Examples/UseTexture/DisplacementMap.vs", GL_VERTEX_SHADER);
		ShaderLoad(MyShader, "../Examples/UseTexture/DisplacementMap.fs", GL_FRAGMENT_SHADER);
	}
}
