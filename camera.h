#pragma once

#include "ray.h"

struct Camera {
	V3 lowerLeftCorner;
	V3 horizontal;
	V3 vertical;
	V3 origin;
	V3 u, v, w;
	float lensRadius;
	// verticalFOV is top to bottom in degrees
	Camera(V3 lookFrom, V3 lookAt, V3 up, float verticalFOV, float aspectRatio, float aperture, float focusDist) {
		lensRadius = aperture/2.0f;
		float theta = verticalFOV*M_PI/180.0f; 
		float halfHeight = tan(theta/2.0f);
		float halfWidth = aspectRatio*halfHeight;
		origin = lookFrom;
		w = lookFrom-lookAt;
		w.normalize();
		u = cross(up, w);
		u.normalize();
		v = cross(w, u);
		// lowerLeftCorner = V3(-halfWidth, -halfHeight, -1.0f);
		lowerLeftCorner = origin - halfWidth*u*focusDist - halfHeight*v*focusDist - w*focusDist;
		horizontal = 2.0f*halfWidth*u*focusDist;
		vertical = 2.0f*halfHeight*v*focusDist;
	}

	Ray getRay(float s, float t) {
		V3 rd = lensRadius*randomInUnitDisk();
		V3 offset = u*rd.x + v*rd.y;
		return Ray(origin+offset, lowerLeftCorner+s*horizontal+t*vertical - origin - offset);
	}
};