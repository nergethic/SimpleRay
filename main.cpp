#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define _USE_MATH_DEFINES
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

IHitable *getRandomScene() {
	int n = 500;
	IHitable **list = new IHitable*[n+1];
	list[0] = new Sphere(V3(0.0f, -1000.0f, 0.0f), 1000.0f, new Lambertian(V3(0.5f, 0.5f, 0.5f)));
	int i = 1;
	for (int a = -11; a < 11; ++a) {
		for (int b = -11; b < 11; ++b) {
			float chooseMaterial = getRandomNumber01();
			V3 center(a+0.9f*getRandomNumber01(), 0.2f, b+0.9f*getRandomNumber01());
			float length = (center-V3(4.0f, 0.2f, 0.0f)).length();
			if (length > 0.9f) {
				if (chooseMaterial < 0.8) {
					list[i++] = new Sphere(center, 0.2f, new Lambertian(getRandomVector01()*getRandomVector01()));
				} else if (chooseMaterial < 0.95f) {
					list[i++] = new Sphere(center, 0.2f, new Metal(0.5f*(getRandomVector01()+V3(1.0f)), 0.5f*getRandomNumber01()));
				} else {
					list[i++] = new Sphere(center, 0.2f, new Dielectric(1.5f));
				}
			} 
		}
	}

	list[i++] = new Sphere(V3(0.0f, 1.0f, 0.0f), 1.0f, new Dielectric(1.5f));
	list[i++] = new Sphere(V3(-4.0f, 1.0f, 0.0f), 1.0f, new Lambertian(V3(0.4f, 0.2f, 0.1f)));
	list[i++] = new Sphere(V3(4.0f, 1.0f, 0.0f), 1.0f, new Metal(V3(0.7f, 0.6f, 0.5f), 0.0f));

	return new HitableList(list, i);
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

	IHitable *objectList[5];
	float R = cos(M_PI/4.0f);
	IHitable *world = getRandomScene();

	Camera camera(V3(-2.0f, 2.0f, 1.0f), V3(0.0f, 0.0f, -1.0f), V3(0.0f, 1.0f, 0.0f), 90.0f, float(width)/float(height));
	unsigned char* currentTexel = data;
	auto cc = sizeof(*currentTexel);
	printf("y lines done:\n");
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
		printf("%d\n", height-y);
	}

	if (!stbi_write_png("render.png", width, height, colorChannels, data, 0)) {
		// TODO: handle this error
	} else {
		printf("Image generated!\n");
	}
	
	return 0;
}