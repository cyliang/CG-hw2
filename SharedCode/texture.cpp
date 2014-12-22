#include "texture.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <FreeImage.h>
#include <cstdio>

void LoadTexture(const char *path, GLenum target);

Texture::Texture(const char *path[]) {
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

void Texture::setTexture() const {
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID[0]);

	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID[1]);
}

void Texture::unsetTexture() const {
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setCoor(const float ptr[]) const {
	glMultiTexCoord2fv(GL_TEXTURE0, ptr);
	glMultiTexCoord2fv(GL_TEXTURE1, ptr);
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
