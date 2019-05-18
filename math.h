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

	inline float length_squared() {
		return x*x + y*y + z*z;
	}

	inline void normalize() {
		float k = 1.0f / length();
		x *= k;
		y *= k;
		z *= k;
	}

	inline V3 get_normalized() {
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

inline float map() {
	// TODO
}