#pragma once

#include "hitable.h"

struct Sphere: IHitable {
	V3 center;
	float radius;

	Sphere(V3 cen, float r) : center(cen), radius(r) {};
	virtual bool hit(Ray& r, float tMin, float tMax, HitRecord& rec) const;
};

bool Sphere::hit(Ray& r, float tMin, float tMax, HitRecord& rec) const {
	V3 oc = r.origin - center;
	float a = dot(r.direction, r.direction);
	//float b = 2.0f * dot(oc, r.direction);
	float b = dot(oc, r.direction);
	float c = dot(oc, oc) - radius*radius;

	float discriminant = b*b - a*c;
	if (discriminant > 0) {

		float temp = (-b - sqrt(discriminant)) / a;
		if (temp > tMin && temp < tMax) {
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}

		temp = (-b + sqrt(discriminant)) / a;
		if (temp > tMin && temp < tMax) {
			rec.t = temp;
			rec.p = r.pointAtParameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	} 
	
	return false;
}