#include "texture.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <FreeImage.h>
#include <cstdio>

void LoadTexture(const char *path, GLenum target);

NoTexture::NoTexture(): Texture(NO) {
}

SingleTexture::SingleTexture(const char *path): Texture(SINGLE) {
	glGenTextures(1, textureID);

	glBindTexture(GL_TEXTURE_2D, textureID[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	LoadTexture(path, GL_TEXTURE_2D);

	glGenerateMipmap(GL_TEXTURE_2D);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

MultiTexture::MultiTexture(const char *path[]): Texture(MULTI) {
	glGenTextures(2, textureID);

	for(int i=0; i<2; i++) {
		glBindTexture(GL_TEXTURE_2D, textureID[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		LoadTexture(path[i], GL_TEXTURE_2D);

		glGenerateMipmap(GL_TEXTURE_2D);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	}
}

CubeTexture::CubeTexture(const char *path[]): Texture(CUBE) {
	glGenTextures(1, textureID);

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	LoadTexture(path[0], GL_TEXTURE_CUBE_MAP_POSITIVE_X);
	LoadTexture(path[1], GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	LoadTexture(path[2], GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	LoadTexture(path[3], GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
	LoadTexture(path[4], GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	LoadTexture(path[5], GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void NoTexture::setTexture() const {
}

void NoTexture::unsetTexture() const {
}

void SingleTexture::setTexture() const {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID[0]);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);
}

void SingleTexture::unsetTexture() const {
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void SingleTexture::setCoor(const float ptr[]) const {
	glTexCoord2fv(ptr);
}

void MultiTexture::setTexture() const {
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
}

void MultiTexture::unsetTexture() const {
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void MultiTexture::setCoor(const float ptr[]) const {
	glMultiTexCoord2fv(GL_TEXTURE0, ptr);
	glMultiTexCoord2fv(GL_TEXTURE1, ptr);
}

void CubeTexture::setTexture() const {
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);

	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE);
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_REPLACE);
}

void CubeTexture::unsetTexture() const {
	glDisable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_S);
}

void LoadTexture(const char *pFilename, GLenum target) {
	FIBITMAP *pImage = FreeImage_Load(FreeImage_GetFileType(pFilename, 0), pFilename);
	FIBITMAP *p32BitsImage = FreeImage_ConvertTo32Bits(pImage);

	int iWidth = FreeImage_GetWidth(p32BitsImage);
	int iHeight = FreeImage_GetHeight(p32BitsImage);

	glTexImage2D(target, 0, GL_RGBA8, iWidth, iHeight,
			0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(p32BitsImage));

	FreeImage_Unload(p32BitsImage);
	FreeImage_Unload(pImage);
}
