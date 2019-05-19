#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "math.h"
#include "ray.h"
#include "sphere.h"
#include "hitableList.h"
#include "camera.h"
#include "material.h"

V3 getColor(Ray& r, IHitable *world, int depth) {
	HitRecord rec;
	if (world->hit(r, 0.001f, FLT_MAX, rec)) {
		Ray scatteredRay;
		V3 attenuation;
		if (depth < 50 && rec.material->scatter(r, rec, attenuation, scatteredRay)) {
			return attenuation*getColor(scatteredRay, world, depth+1.0f);
		} else {
			return V3(0.0f, 0.0f,0.0f);
		}

		//V3 target = rec.p + rec.normal + randomInUnitSphere();
		//Ray ray(rec.p, target-rec.p);
		//return 0.5f*getColor(ray, world);
	} else {
		V3 unitDirection = r.direction.getNormalized();
		float t = mapTo01(unitDirection.y, -1.0f, 1.0f);
		return lerp(V3(1.0f, 1.0f, 1.0f), V3(0.5f, 0.7f, 1.0f), t);
	}
}

int main(int argCount, char **args) {

	srand(time(NULL));

	const int width = 200;
	const int height = 100;
	const int colorChannels = 3;
	const int bytePerChannel = 1;
	const int ns = 100;
	unsigned char* data = (unsigned char*)malloc(width*height*colorChannels*bytePerChannel);

	int stride = width*colorChannels;

	IHitable *objectList[4];
	objectList[0] = new Sphere(V3(0.0f, 0.0f, -1.0f), 0.5f, new Lambertian(V3(0.8f, 0.3f, 0.3f)));
	objectList[1] = new Sphere(V3(0.0f, -100.5f, -1.0f), 100.0f, new Lambertian(V3(0.8f, 0.8f, 0.0f)));
	objectList[2] = new Sphere(V3(1.0f, 0.0f, -1.0f), 0.5f, new Metal(V3(0.8f, 0.6f, 0.2f), 1.0f));
	objectList[3] = new Sphere(V3(-1.0f, 0.0f, -1.0f), 0.5f, new Metal(V3(0.8f, 0.8f, 0.8f), 0.3f));
	IHitable *world = new HitableList(objectList, 4);
	Camera camera;
	unsigned char* currentTexel = data;
	auto cc = sizeof(*currentTexel);
	for (int y = height-1; y >= 0; --y) {
		for (int x = 0; x < width; ++x) {
			V3 color(0.0f);
			for (int s = 0; s<ns; ++s) {
				float u = float(x + getRandomNumber01())/float(width);
				float v = float(y + getRandomNumber01())/float(height);
				Ray ray = camera.getRay(u, v);
				V3 p = ray.pointAtParameter(2.0f);
				color = color + getColor(ray, world, 0);
			}
			color = color / float(ns);
			color = V3(sqrt(color.r), sqrt(color.g), sqrt(color.b));
			
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