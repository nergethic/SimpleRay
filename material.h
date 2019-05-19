#pragma once

#include "ray.h"
#include "hitable.h"

struct IMaterial {
	virtual bool scatter(Ray& rayIn, HitRecord& rec, V3& attenuation, Ray& scatteredRay) const = 0;
};

struct Lambertian : IMaterial {
	V3 albedo;
	Lambertian(const V3& a) : albedo(a) {}
	virtual bool scatter(Ray& rayIn, HitRecord& rec, V3& attenuation, Ray& scatteredRay) const {
		V3 target = rec.p + rec.normal + randomInUnitSphere();
		scatteredRay = Ray(rec.p, target-rec.p);
		attenuation = albedo;
		return true;
	}
};

struct Metal : IMaterial {
	V3 albedo;
	float fuzz;
	Metal(const V3& a, float f) : albedo(a) { if (f < 1) fuzz = f; else  fuzz = 1; }
	virtual bool scatter(Ray& rayIn, HitRecord& rec, V3& attenuation, Ray& scatteredRay) const {
		V3 rayDir = rayIn.direction.getNormalized(); // TODO: check if this need to be normalized
		V3 reflected = reflect(rayDir, rec.normal);
		scatteredRay = Ray(rec.p, reflected + fuzz*randomInUnitSphere());
		attenuation = albedo;
		return (dot(scatteredRay.direction, rec.normal) > 0.0f);
	}
};