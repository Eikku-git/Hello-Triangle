#pragma once
#include <math.h>

struct vec4 {
	float x, y, z, w;
};

struct vec3 {
public:
	float x, y, z;
	float magnitude();
	vec3 normalized();
	vec3(float x = 0, float y = 0, float z = 0) {
		this->x = x; this->y = y; this->z = z;
	}
};

struct quaternion {
public:
	vec4 rotation;
	void createRotationAroundAxis(float radians, vec3 axis);
	float* createRotationMatrix() const;
};
