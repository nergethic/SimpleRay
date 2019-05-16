#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(int argCount, char **args) {

	int width = 512;
	int height = 512;
	int colorChannels = 3;
	unsigned char* data = (unsigned char*)malloc(width*height*colorChannels);

	// int stride = width*colorChannels;
	unsigned char* currentPixel = data;
	for (unsigned int y = 0; y < height; ++y) {
		for (unsigned int x = 0; x < width; ++x) {
			*currentPixel = 255.0f*((float)x/width);
			currentPixel++;
			*currentPixel = 255.0f*((float)y/height);
			currentPixel++;
			*currentPixel = 0.2f*255.0f;
			currentPixel++;
			//currentPixel += colorChannels;
		}
	}

	if (!stbi_write_png("render.png", width, height, colorChannels, data, 0)) {
		// TODO: handle this error
	} else {
		printf("Image generated!\n");
	}
	
	return 0;
}