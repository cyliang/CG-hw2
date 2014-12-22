#include "scene.h"
#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

SceneLoader::Model::Model(const char *file_name, const Texture *t): obj(file_name, t) {
}

SceneLoader::SceneLoader(const char *info_file): selection(0) {
	std::ifstream ifile(info_file, std::ios::in);
	if(!ifile) {
		std::cerr << "Cannot load scene file: " << info_file << std::endl;
		exit(1);
	}

	Texture *nowTexture;
	std::string model_str;
	while(ifile >> model_str) {
		if(model_str == "no-texture") {
			nowTexture = new NoTexture();
			continue;
		} else if(model_str == "single-texture") {
			char texturePath[100];
			ifile >> texturePath;

			nowTexture = new SingleTexture(texturePath);
			continue;
		} else if(model_str == "multi-texture") {
			char texturePath[2][100];
			ifile >> texturePath[0] >> texturePath[1];

			const char *p[2] = {texturePath[0], texturePath[1]};
			nowTexture = new MultiTexture(p);
			continue;
		} else if(model_str == "cube-map") {
			char texturePath[6][100];
			const char *p[6];
			for(int i=0; i<6; i++) {
				ifile >> texturePath[i];
				p[i] = texturePath[i];
			}

			nowTexture = new CubeTexture(p);
			continue;
		} else if(model_str != "model") {
			std::cerr << "Error in parsing scene file: " << info_file << std::endl;
			exit(1);
		}

		std::string obj_name;
		ifile >> obj_name;
		Model m(obj_name.c_str(), nowTexture);
		
		ifile >> m.scale_xyz[0] >> m.scale_xyz[1] >> m.scale_xyz[2]
			>> m.rotate_axyz[0] >> m.rotate_axyz[1] >> m.rotate_axyz[2] >> m.rotate_axyz[3]
			>> m.translate_xyz[0] >> m.translate_xyz[1] >> m.translate_xyz[2];

		if(!ifile) {
			std::cerr << "Error in parsing scene file: " << info_file << std::endl;
			exit(1);
		}

		models.push_back(m);
	}
}

void SceneLoader::displayScene() const {
	glMatrixMode(GL_MODELVIEW);

	for(int i=0; i<models.size(); i++) {
		const Model &m = models[i];

		glPushMatrix();
			glTranslatef(m.translate_xyz[0], m.translate_xyz[1], m.translate_xyz[2]);
			glRotatef(m.rotate_axyz[0], m.rotate_axyz[1], m.rotate_axyz[2], m.rotate_axyz[3]);
			glScalef(m.scale_xyz[0], m.scale_xyz[1], m.scale_xyz[2]);

			m.obj.setObj();
		glPopMatrix();
	}
}

void SceneLoader::select(int n) {
	if(n >= 0 && n < 9)
		selection = n;
}

void SceneLoader::moveObj(float x, float y) {
	if(selection < models.size()) {
		models[selection].translate_xyz[0] += x;
		models[selection].translate_xyz[1] += y;
	}
}
