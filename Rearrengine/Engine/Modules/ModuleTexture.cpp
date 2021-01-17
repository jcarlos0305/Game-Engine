#include "ModuleTexture.h"
#include "Utils/Globals.h"

#include <GL/glew.h>
#include <IL/il.h>
#include <IL/ilu.h>

#include "Utils/LeakTest.h"

bool ModuleTexture::Init() {
	ilInit();
	return true;
}

unsigned int ModuleTexture::LoadTexture(const char* path) {
	unsigned int image, texture_id;

	ilGenImages(1, &image);
	ilBindImage(image);

	bool success = ilLoadImage(path);

	if (success) {
		ILinfo ilImageInfo;
		iluGetImageInfo(&ilImageInfo);

		if (ilImageInfo.Origin == IL_ORIGIN_UPPER_LEFT) {
			iluFlipImage();
		}

		/* Convert every color component into unsigned byte */
		success = ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);

		if (!success) {
			return false;
		}

		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);

		/* Linear interpolation for magnification & minifying filters */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		/* Texture specs */
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			ilGetInteger(IL_IMAGE_BPP),
			ilGetInteger(IL_IMAGE_WIDTH),
			ilGetInteger(IL_IMAGE_HEIGHT),
			0,
			ilGetInteger(IL_IMAGE_FORMAT),
			GL_UNSIGNED_BYTE,
			ilGetData()
		);
	}
	else {
		return false;
	}
	/* Releasing the memory used by image. */
	ilDeleteImages(1, &image);

	return texture_id;
}

UpdateStatus ModuleTexture::PreUpdate() {
	return UpdateStatus::kUpdateContinue;
}

UpdateStatus ModuleTexture::Update() {
	return UpdateStatus::kUpdateContinue;
}

UpdateStatus ModuleTexture::PostUpdate() {
	return UpdateStatus::kUpdateContinue;
}

bool ModuleTexture::CleanUp() {
	return true;
}