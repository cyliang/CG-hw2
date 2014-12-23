#include "../SharedCode/ShaderLoader.h"
#include "../SharedCode/header.h"

#include <iostream>
using namespace std;

ViewingLoader *viewPtr;
SceneLoader *scenePtr;
LightLoader *lightPtr;
GLhandleARB MyShader;

float coef = 1;

void LoadShaders();

int main(int argc, char *argv[]) {
	if (argc != 6) {
		cerr << "Usage: " << argv[0] << " <view_file> <scene_file> <light_file>" << endl;
		return -1;
	}
	viewPtr = new ViewingLoader(argv[1]);
	lightPtr = new LightLoader(argv[3]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(viewPtr->getWidth(), viewPtr->getHeight());
	glutCreateWindow("GL-Assignment1 0116229");

	if (glewInit() != GLEW_OK)
		return -1;

	scenePtr = new SceneLoader(argv[2], (const char **) argv + 4);
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
		ShaderLoad(MyShader, "../Examples/PhongShading/BumpMap.vs", GL_VERTEX_SHADER);
		ShaderLoad(MyShader, "../Examples/PhongShading/BumpMap.fs", GL_FRAGMENT_SHADER);
	}
}
