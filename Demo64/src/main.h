#pragma once
#include "Maths.h"
struct Vector2;
struct Vector3;

struct Context
{
	bool upPressed;
	bool wPressed;
	bool aPressed;
	bool sPressed;
	bool dPressed;
	bool rPressed;
	bool fPressed;
	bool qPressed;
	bool leftButtonDown;
	bool leftButtonPressed;
	Vector2 mousePosition;
	Vector2 previousMousePosition;

	Vector3 cameraPosition;
	Vector3 cameraTarget;
	float cameraForwardSpeed;
	float cameraMaxSpeed;
	float cameraAcceleration;
	float yaw;
	float pitch;

	bool lookingDown;
	Vector3 storedCameraDirection;
};