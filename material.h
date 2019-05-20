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

struct Dielectric : IMaterial {
	float refractionIndex;
	Dielectric(float ri) : refractionIndex(ri) {}
	virtual bool scatter(Ray& rayIn, HitRecord& rec, V3& attenuation, Ray& scatteredRay) const {
		attenuation = V3(1.0f);
		V3 outwardNormal, refractedRay;
		float niOverNt, reflectProb, cosine;
		V3 reflectedRay = reflect(rayIn.direction, rec.normal);

		if (dot(rayIn.direction, rec.normal) > 0.0f) {
			outwardNormal = -rec.normal;
			niOverNt = refractionIndex;
			cosine = refractionIndex*dot(rayIn.direction, rec.normal) / rayIn.direction.length();
		} else {
			outwardNormal = rec.normal;
			niOverNt = 1.0f / refractionIndex;
			cosine = -dot(rayIn.direction, rec.normal) / rayIn.direction.length();
		}

		if (refract(rayIn.direction, outwardNormal, niOverNt, refractedRay)) {
			reflectProb = schlick(cosine,refractionIndex);
			// scatteredRay = Ray(rec.p, refractedRay);
		} else {
			scatteredRay = Ray(rec.p, reflectedRay);
			reflectProb = 1.0f;
		}

		if (getRandomNumber01() < reflectProb) {
			scatteredRay = Ray(rec.p, reflectedRay);
		} else {
			scatteredRay = Ray(rec.p, refractedRay);
		}
		return true;
	}
};