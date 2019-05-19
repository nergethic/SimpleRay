#pragma once

#include "math.h"

struct Ray {
	V3 origin;
	V3 direction;

	Ray() {}
	Ray(V3 origin, V3 direction) {
		this->origin = origin;
		this->direction = direction;
	}

	V3 pointAtParameter(float t) {
		return origin + t*direction;
	}
};