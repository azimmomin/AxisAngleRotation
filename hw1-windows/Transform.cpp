// Transform.cpp: implementation of the Transform class.

#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// Initialze result as the idenity matrix.
	mat3 result(1.0f);

	// Initialize rotation in radians and dual matrix of the axis.
	float radians = glm::radians(degrees);
	mat3 dualMatrix(
		0, axis.z, -axis.y,
		-axis.z, 0, axis.x,
		axis.y, -axis.x, 0
	);

	// Add in perpendicular component
	result += (glm::sin(radians) * dualMatrix);

	// Add in parallel component.
	result += ((1 - glm::cos(radians)) * (dualMatrix * dualMatrix));

	return result;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	mat3 rotation = rotate(degrees, glm::normalize(up));
	eye = rotation * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 axis = glm::normalize(glm::cross(eye, up));
	mat3 rotation = rotate(degrees, axis);
	eye = rotation * eye;
	up = rotation * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	vec3 forward = glm::normalize(-eye);
	vec3 right = glm::normalize(glm::cross(forward, up));
	vec3 newUp = glm::cross(right, forward);

	return mat4(
		right.x, newUp.x, -forward.x, 0,
		right.y, newUp.y, -forward.y, 0,
		right.z, newUp.z, -forward.z, 0,
		-glm::dot(right, eye), -glm::dot(newUp, eye), glm::dot(forward, eye), 1
	);
}

Transform::Transform()
{

}

Transform::~Transform()
{

}