#include <linmath.hpp>

float vec3::magnitude() {
	return sqrt(x * x + y * y + z * z);
}
vec3 vec3::normalized() {
	float mag = magnitude();
	return vec3(x / mag, y / mag, z / mag);
}

void quaternion::createRotationAroundAxis(float radians, vec3 axis) {
	float sinRot = sin(radians);
	axis = axis.normalized();
	float cosRot = cos(radians);
	vec4 result;
	result.x = axis.x * sinRot;
	result.y = axis.y * sinRot;
	result.z = axis.z * sinRot;
	result.w = cosRot;
	quaternion::rotation = result;
}

float* quaternion::createRotationMatrix() const {
	float xSquare = rotation.x * rotation.x;
	float ySquare = rotation.y * rotation.y;
	float zSquare = rotation.z * rotation.z;
	float result[16]{
		1 - 2 * (ySquare + zSquare), 2 * (rotation.x * rotation.y - rotation.z * rotation.w), 2 * (rotation.x * rotation.z + rotation.y * rotation.w), 0,
		2 * (rotation.x * rotation.y + rotation.z * rotation.w), 1 - 2 * (xSquare + zSquare), 2 * (rotation.y * rotation.z - rotation.x * rotation.w), 0,
		2 * (rotation.y * rotation.z - rotation.y * rotation.w), 2 * (rotation.y * rotation.z + rotation.x * rotation.w), 1 - 2 * (xSquare + ySquare), 0,
		0, 0, 0, 1
	};
	return result;
}
