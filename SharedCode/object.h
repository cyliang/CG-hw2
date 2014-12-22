#pragma once
#include "texture.h"
#include "mesh.h"

class ObjLoader: protected mesh {
public:
	ObjLoader(const char *object_info_file, const Texture *t);
	
	void setObj() const;

private:
	const Texture *texture;
	unsigned int displayListID;

};
