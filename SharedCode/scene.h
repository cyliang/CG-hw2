#pragma once
#include "object.h"
#include <vector>

class SceneLoader {
public:
	SceneLoader(const char *SceneInfoFile);
	void displayScene() const;

	void moveObj(float x_diff, float y_diff);
	void select(int nthObj);

private:
	struct Model {
		Model(const char *objFileName, const Texture *);

		ObjLoader obj;
		float scale_xyz[3];
		float rotate_axyz[4];
		float translate_xyz[3];
	};

	std::vector<Model> models;
	int selection;
};
