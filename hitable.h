#pragma once

#include "ray.h"

struct IMaterial;

struct HitRecord {
	float t;
	V3 p;
	V3 normal;
	IMaterial *material;
};

struct IHitable {
	virtual bool hit(Ray& r, float tMin, float tMax, HitRecord& rec) const = 0;
};