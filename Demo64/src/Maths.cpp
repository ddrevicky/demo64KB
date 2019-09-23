#pragma once
#include "Maths.h"
#include "Def.h"

#undef far
#undef near

Vector3 Math::CrossProduct(Vector3 v1, Vector3 v2)
{
	Vector3 crossProduct;
	crossProduct.x = v1.y * v2.z - v1.z * v2.y;
	crossProduct.y = v1.z * v2.x - v1.x * v2.z;
	crossProduct.z = v1.x * v2.y - v1.y * v2.x;
	return crossProduct;
}

const Matrix4x4 Math::GetTranslation(Vector3 vec)
{
	return Math::GetTranslation(vec.x, vec.y, vec.z);
}

const Matrix4x4 Math::GetTranslation(const float dx, const float dy, const float dz)
{
	Matrix4x4 result;

	result[0] = 1;
	result[5] = 1;
	result[10] = 1;
	result[12] = dx;
	result[13] = dy;
	result[14] = dz;
	result[15] = 1;

	return result;
}

const Matrix4x4 Math::GetRotation(const float angle, Vector3 axis)
{
	float c = cos(angle);
	float s = sin(angle);

	Matrix4x4 result;
	float ax = axis.x;
	float ay = axis.y;
	float az = axis.z;
	result[0] = c + (1 - c) * ax * ax;
	result[1] = (1 - c) * ax * ay + s * az;
	result[2] = (1 - c) * ax * az - s * ay;
	result[3] = 0;

	result[4] = (1 - c) * ax * ay - s * az;
	result[5] = c + (1 - c) * ay * ay;
	result[6] = (1 - c) * ay * az + s * ax;
	result[7] = 0;

	result[8] = (1 - c) * ax * az + s * ay;
	result[9] = (1 - c) * ay * az - s * ax;
	result[10] = c + (1 - c) * az * az;
	result[11] = 0;

	result[12] = 0;
	result[13] = 0;
	result[14] = 0;
	result[15] = 1;

	return result;
}

const Matrix4x4 Math::GetIdentity()
{
	Matrix4x4 result;
	result.v1 = Vector4(1, 0, 0, 0);
	result.v2 = Vector4(0, 1, 0, 0);
	result.v3 = Vector4(0, 0, 1, 0);
	result.v4 = Vector4(0, 0, 0, 1);
	return result;
}

const Matrix4x4 Math::GetScale(const float sx, const float sy, const float sz)
{
	Matrix4x4 result = GetIdentity();
	result[0] = sx;
	result[5] = sy;
	result[10] = sz;
	return result;
}

bool Math::FloatEqual(float a, float b, float epsilon)
{
	bool result = Math::Abs(a - b) < epsilon;
	return result;
}

bool Math::FloatEqual(Vector3 v1, Vector3 v2, float epsilon)
{
	bool result = Math::FloatEqual(v1.x, v2.x, epsilon) &&
		Math::FloatEqual(v1.y, v2.y, epsilon) &&
		Math::FloatEqual(v1.z, v2.z, epsilon);
	return result;
}

float Math::Abs(float x)
{
	return x < 0 ? -x : x;
}

#include <math.h>
float Math::Length(Vector2 v)
{
	float result = sqrtf(v.x * v.x + v.y * v.y);
	return result;
}

Vector2 Math::Rotate(float angle, Vector2 v)
{
	Vector2 result;
	result.x = cos(angle) * v.x - sin(angle) * v.y;
	result.y = sin(angle) * v.x + cos(angle) * v.y;
	return result;
}

float Math::Length(Vector3 v)
{
	float result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return result;
}

Vector3 Math::Normalize(Vector3 v)
{
	Vector3 result = v / Length(v);
	return result;
}

float Math::Dot(Vector2 v1, Vector2 v2)
{
	float result = v1.x * v2.x + v1.y * v2.y;
	return result;
}

float Math::Dot(Vector3 v1, Vector3 v2)
{
	float result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return result;
}

float Math::Distance(Vector2 v1, Vector2 v2)
{
	float result = Math::Length(v1 - v2);
	return result;
}

Vector2 Math::Normalize(Vector2 v)
{
	Vector2 result = v / Length(v);
	return result;
}

Vector3::Vector3(Vector4 vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;

}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3 Vector3::operator*(float x)
{
	return Vector3(this->x * x, this->y * x, this->z * x);
}

Vector3 Vector3::operator/(float x)
{
	return Vector3(this->x / x, this->y / x, this->z / x);
}

Vector3 Vector3::operator+(Vector3 x)
{
	return Vector3(this->x + x.x, this->y + x.y, this->z + x.z);
}

Vector3 Vector3::operator-(Vector3 x)
{
	return Vector3(this->x - x.x, this->y - x.y, this->z - x.z);
}

Vector3 Vector3::operator+=(Vector3 x)
{
	this->x += x.x;
	this->y += x.y;
	this->z += x.z;
	return *this;
}

Vector3 Vector3::operator-=(Vector3 x)
{
	this->x -= x.x;
	this->y -= x.y;
	this->z -= x.z;
	return *this;
}

Vector3 Vector3::operator-()
{
	return Vector3(-this->x, -this->y, -this->z);
}
bool Vector3::operator==(const Vector3 v)
{
	return (this->x == v.x) && (this->y == v.y) && (this->z == v.z);
}

Vector4::Vector4(Vector3 vec, float w)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = w;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

const Vector4 Vector4::operator-()
{
	return Vector4(-x, -y, -z, -w);
}

const Vector4 Vector4::operator+=(const Vector4 x)
{
	this->x += x.x;
	this->y += x.y;
	this->z += x.z;
	this->w += x.w;
	return *this;
}

const Vector4 Vector4::operator/=(const float x)
{
	this->x /= x;
	this->y /= x;
	this->z /= x;
	this->w /= x;
	return *this;
}

const Vector4 Vector4::operator*=(const float x)
{
	this->x *= x;
	this->y *= x;
	this->z *= x;
	this->w *= x;
	return *this;
}

const Vector4 Vector4::operator*(const float x)
{
	return Vector4(this->x * x, this->y * x, this->z * x, this->w * x);
}