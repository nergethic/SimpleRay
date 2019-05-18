#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "math.h"
#include "ray.h"

float hitSphere(V3 center, float radius, Ray& r) {
	V3 oc = r.origin - center;
	float a = dot(r.direction, r.direction);
	float b = 2.0f * dot(oc, r.direction);
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - 4*a*c;
	if (discriminant < 0) {
		return -1.0f;
	} else {
		return (-b - sqrt(discriminant)) / (2.0f*a);
	}
}

V3 getColor(Ray& r) {
	float t = hitSphere(V3(0.0f, 0.0f, -1.0f), 0.5f, r);
	if (t > 0.0f) {
		// sphere normal is (hitpoint - sphere center)
		V3 normal = r.point_at_t(t) - V3(0.0f, 0.0f, -1.0f);
		normal.normalize();
		return 0.5f*(V3(normal.x, normal.y, normal.z) + V3(1.0f));
	}

	V3 unitDirection = r.direction.get_normalized();
	t = 0.5f*(unitDirection.y + 1.0f);
	return lerp(V3(0.2f, 0.8f, 1.0f), V3(0.8f, 0.7f, 1.0f), t);
}

int main(int argCount, char **args) {

	const int width = 200;
	const int height = 100;
	const int colorChannels = 3;
	const int bytePerChannel = 1;
	unsigned char* data = (unsigned char*)malloc(width*height*colorChannels*bytePerChannel);

	int stride = width*colorChannels;
	//V3 upperLeftCorner(-2.0f, 1.0f, -1.0f);
	V3 lowerLeftCorner(-2.0f, -1.0f, -1.0f);
	V3 horizontal(4.0f, 0.0f, 0.0f);
	V3 vertical(0.0f, 2.0f, 0.0f);
	V3 origin(0.0f, 0.0f, 0.0f);
	unsigned char* currentTexel = data;
	auto cc = sizeof(*currentTexel);
	for (int y = height-1; y >= 0; --y) {
	// for (unsigned int y = 0; y < height; ++y) {
		float v = float(y)/float(height);
		for (int x = 0; x < width; ++x) {
			float u = float(x)/float(width);
			V3 rayDir = lowerLeftCorner + u*horizontal + v*vertical;
			Ray ray(origin, rayDir);
			V3 color = getColor(ray);
			*currentTexel = int(color.r*255.99f);
			currentTexel++;
			*currentTexel = int(color.g*255.99f);
			currentTexel++;
			*currentTexel = int(color.b*255.99f);
			currentTexel++;
		}
	}

	if (!stbi_write_png("render.png", width, height, colorChannels, data, 0)) {
		// TODO: handle this error
	} else {
		printf("Image generated!\n");
	}
	
	return 0;
}