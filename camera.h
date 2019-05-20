#pragma once

#include "ray.h"

struct Camera {
	V3 lowerLeftCorner;
	V3 horizontal;
	V3 vertical;
	V3 origin;

	// verticalFOV is top to bottom in degrees
	Camera(V3 lookFrom, V3 lookAt, V3 up, float verticalFOV, float aspectRatio) {
		float theta = verticalFOV*M_PI/180.0f; 
		float halfHeight = tan(theta/2.0f);
		float halfWidth = aspectRatio*halfHeight;
		origin = lookFrom;
		V3 w = lookFrom-lookAt;
		w.normalize();
		V3 u = cross(up, w);
		u.normalize();
		V3 v = cross(w, u);
		lowerLeftCorner = V3(-halfWidth, -halfHeight, -1.0f);
		lowerLeftCorner = origin - halfWidth*u - halfHeight*v - w;
		horizontal = 2.0f*halfWidth*u;
		vertical = 2.0f*halfHeight*v;
	}

	Ray getRay(float u, float v) {
		return Ray(origin, lowerLeftCorner+u*horizontal+v*vertical - origin);
	}
};