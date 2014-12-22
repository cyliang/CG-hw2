#pragma once

class Texture {
public:
	Texture(const char *path[]);
	void setTexture() const;
	void unsetTexture() const;
	void setCoor(const float ptr[]) const;

private:
	unsigned int textureID[2];
};