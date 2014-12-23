#include "../SharedCode/ShaderLoader.h"
#include "../SharedCode/header.h"

#include <iostream>
using namespace std;

ViewingLoader *viewPtr;
SceneLoader *scenePtr;
LightLoader *lightPtr;
GLhandleARB MyShader;

float coef = 0.4;
float rotate_angle = 0;
float light_angle[2] = { 0.0, 0.0 }; // Horizontal, Vertical

void LoadShaders();
void lightCtrl(unsigned char key, int x, int y);

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
	glutKeyboardFunc(lightCtrl);
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

void lightCtrl(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':
		light_angle[1] += 5;
		break;
	case 's':
		light_angle[1] -= 5;
		break;
	case 'a':
		light_angle[0] -= 5;
		break;
	case 'd':
		light_angle[0] += 5;
		break;
	default:
		return;
	}

	redisplay();
}