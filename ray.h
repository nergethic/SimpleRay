#pragma once

#include "math.h"

struct Ray {
	V3 origin;
	V3 direction;

	Ray(V3 origin, V3 direction) {
		this->origin = origin;
		this->direction = direction;
	}

	V3 point_at_t(float t) {
		return origin + t*direction;
	}
};