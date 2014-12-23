#include "../SharedCode/object.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <cstdlib>
#include <valarray>
using namespace std;

typedef valarray<float> vec;

static void sendTangent(
	const float *vertexCoor1, const float *vertexCoor2, const float *vertexCoor3,
	const float *textureCoor1, const float *textureCoor2, const float *textureCoor3,
	GLint locationTangent, GLint locationBitangent)
{

	vec P1(vertexCoor1, 3);
	vec P2(vertexCoor2, 3);
	vec P3(vertexCoor3, 3);

	vec UV1(textureCoor1, 2);
	vec UV2(textureCoor2, 2);
	vec UV3(textureCoor3, 2);

	vec Edge1 = P2 - P1;
	vec Edge2 = P3 - P1;
	vec Edge1uv = UV2 - UV1;
	vec Edge2uv = UV3 - UV1;

	float cp = Edge1uv[0] * Edge2uv[1] - Edge2uv[0] * Edge1uv[1];

	if (cp != 0.0f) {
		float mul = 1.0f / cp;
		vec tangent = (Edge1 * Edge2uv[1] + Edge2 * -Edge1uv[1]) * mul;
		vec bitangent = (Edge1 * -Edge2uv[0] + Edge2 * Edge1uv[0]) * mul;

		glVertexAttrib3f(locationTangent, tangent[0], tangent[1], tangent[2]);
		glVertexAttrib3f(locationBitangent, bitangent[0], bitangent[1], bitangent[2]);
	}
}

ObjLoader::ObjLoader(const char *object_info_file, const Texture *t) : mesh(object_info_file), texture(t) {}

void ObjLoader::setObj() const {
	texture->setTexture();

	extern GLhandleARB MyShader;
	GLint locationTangent = glGetAttribLocation(MyShader, "tangent");
	GLint locationBitangent = glGetAttribLocation(MyShader, "bitangent");

	if (locationBitangent == -1 || locationTangent == -1) {
		cerr << "Can't find location: tangent or bitangent." << endl;
		exit(1);
	}

	int lastMaterial = -1;
	for (int i = 0; i<fTotal; i++) {
		if (lastMaterial != faceList[i].m) {
			lastMaterial = (int)faceList[i].m;
			const material &mtl = mList[lastMaterial];

			glMaterialfv(GL_FRONT, GL_AMBIENT, mtl.Ka);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, mtl.Kd);
			glMaterialfv(GL_FRONT, GL_SPECULAR, mtl.Ks);
			glMaterialfv(GL_FRONT, GL_SHININESS, &mtl.Ns);
		}

		glBegin(GL_TRIANGLES);
		sendTangent(
			vList[faceList[i].v[0].v].ptr, vList[faceList[i].v[1].v].ptr, vList[faceList[i].v[2].v].ptr,
			tList[faceList[i].v[0].t].ptr, tList[faceList[i].v[1].t].ptr, tList[faceList[i].v[2].t].ptr,
			locationTangent, locationBitangent
			);
		for (int j = 0; j < 3; j++) {
			texture->setCoor(tList[faceList[i].v[j].t].ptr);
			glNormal3fv(nList[faceList[i].v[j].n].ptr);
			glVertex3fv(vList[faceList[i].v[j].v].ptr);
		}
		glEnd();
	}

	texture->unsetTexture();
}

