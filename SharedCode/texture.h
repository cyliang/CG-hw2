#pragma once

class Texture {
public:
	enum TextureType {NO, SINGLE, MULTI, CUBE};

	Texture(TextureType t): type(t) {};
	TextureType getType() const {
		return type;
	}

	virtual void setTexture() const = 0;
	virtual void unsetTexture() const = 0;
	virtual void setCoor(const float ptr[]) const {};

private:
	const TextureType type;
};

class NoTexture: public Texture {
public:
	NoTexture();
	void setTexture() const;
	void unsetTexture() const;
};

class SingleTexture: public Texture {
public:
	SingleTexture(const char *path);
	void setTexture() const;
	void unsetTexture() const;
	void setCoor(const float ptr[]) const;

private:
	unsigned int textureID[1];
};

class MultiTexture: public Texture {
public:
	MultiTexture(const char *path[]);
	void setTexture() const;
	void unsetTexture() const;
	void setCoor(const float ptr[]) const;

private:
	unsigned int textureID[2];
};

class CubeTexture: public Texture {
public:
	CubeTexture(const char *path[]);
	void setTexture() const;
	void unsetTexture() const;

private:
	unsigned int textureID[1];
};
