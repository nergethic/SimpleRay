#pragma once

#include <math.h>

class V3 {
public:
	union {
		struct {
			float x, y, z;
		};

		struct {
			float r, g, b;
		};

		float e[3];
	};

	V3() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	V3(float val) {
		this->x = val;
		this->y = val;
		this->z = val;
	}

	V3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline float operator[](int i) { return e[i]; }

	inline float length() {
		return sqrt(x*x + y*y + z*z);
	}

	inline float lengthSquared() {
		return x*x + y*y + z*z;
	}

	inline void normalize() {
		float k = 1.0f / length();
		x *= k;
		y *= k;
		z *= k;
	}

	inline V3 getNormalized() {
		V3 v(x, y, z);
		v.normalize();
		return v;
	}
};

inline bool operator==(const V3& a, const V3& b) { return (a.x == b.x && a.y == b.y && a.z == b.z); }
inline bool operator!=(const V3& a, const V3& b) { return (a.x != b.x || a.y != b.y || a.z != b.z); }
inline V3 operator+(const V3& a, const V3& b) { return V3(a.x+b.x, a.y+b.y, a.z+b.z); }
inline V3 operator-(const V3& a, const V3& b) { return V3(a.x-b.x, a.y-b.y, a.z-b.z); }
inline V3 operator*(const V3& a, const V3& b) { return V3(a.x*b.x, a.y*b.y, a.z*b.z); }
inline V3 operator/(const V3& a, const V3& b) { return V3(a.x/b.x, a.y/b.y, a.z/b.z); }

inline V3 operator*(float t, const V3& b) { return V3(t*b.x, t*b.y, t*b.z); }
inline V3 operator*(const V3& b, float t) { return V3(b.x*t, b.y*t, b.z*t); }
inline V3 operator/(float t, const V3& b) { return V3(t/b.x, t/b.y, t/b.z); }
inline V3 operator/(const V3& b, float t) { return V3(b.x/t, b.y/t, b.z/t); }

inline float dot(V3 a, V3 b) {
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

//inline float cross(V3 a, V3 b) {
//	return ;
//}

inline float lerp(float a, float b, float t) {
	return (1.0f-t)*a + t*b;
}

inline V3 lerp(V3 a, V3 b, float t) {
	return (1.0f-t)*a + t*b;
}

inline float mapFrom01(float x, float min, float max) {
	return((max-min)*x + min);
}

inline V3 mapFrom01(V3 x, float min, float max) {
	return((max-min)*x + V3(min));
}

inline float mapTo01(float x, float min, float max) {
	return((x+abs(min))/(max - min));
}

inline V3 mapTo01(V3 x, float min, float max) {
	return((x+V3(abs(min)))/V3((max - min)));
}

inline float map(float x, float fromMin, float fromMax, float toMin, float toMax) {
	return(toMin + (x-fromMin)*(toMax-toMin)/(fromMax-fromMin));
}
inline V3 map(V3 x, float fromMin, float fromMax, float toMin, float toMax) {
	return(V3(toMin) + ((x-V3(fromMin))*V3((toMax-toMin)/(fromMax-fromMin))));
}

// range of generated number: [0-1)
inline float getRandomNumber01() {
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) - 0.0001f;
}

V3 randomInUnitSphere() {
	V3 p;
	do {
		p = mapFrom01(V3(getRandomNumber01(), getRandomNumber01(), getRandomNumber01()), -1.0f, 1.0f);
	} while (p.lengthSquared() >= 1.0f);
	return p;
}

V3 reflect(V3& v, V3& normal) {
	return(v - 2.0f*dot(v, normal)*normal);
}