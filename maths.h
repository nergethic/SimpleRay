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
};