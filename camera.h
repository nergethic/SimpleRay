#pragma once

#include "ray.h"

struct Camera {
	V3 lowerLeftCorner;
	V3 horizontal;
	V3 vertical;
	V3 origin;

	Camera() {
		lowerLeftCorner = V3(-2.0f, -1.0f, -1.0f);
		horizontal = V3(4.0f, 0.0f, 0.0f);
		vertical = V3(0.0f, 2.0f, 0.0f);
		origin = V3(0.0f, 0.0f, 0.0f);
	}

	Ray getRay(float u, float v) {
		return Ray(origin, lowerLeftCorner+u*horizontal+v*vertical - origin);
	}
};