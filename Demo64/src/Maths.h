#pragma once
#include "Def.h"

#define PI 3.14159265359f
#define PI2 6.28318530718f
#define PIHALF 1.57079632679f
#define EPSILON 0.00001f;

struct Vector2
{
	float x;
	float y;

	Vector2()
	{
		this->x = 0;
		this->y = 0;
	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	const Vector2 operator-(const Vector2 v2)
	{
		return Vector2(this->x - v2.x, this->y - v2.y);
	}

	const Vector2 operator-(const Vector2 v2) const
	{
		return Vector2(this->x - v2.x, this->y - v2.y);
	}

	const Vector2 operator-()
	{
		return Vector2(-this->x, -this->y);
	}

	const Vector2 operator*(const float v)
	{
		return Vector2(this->x * v, this->y * v);
	}

	const Vector2 operator*(const float v) const
	{
		return Vector2(this->x * v, this->y * v);
	}

	const Vector2 operator/(const float v)
	{
		return Vector2(this->x / v, this->y / v);
	}

	const Vector2 operator+(const Vector2 v2)
	{
		return Vector2(this->x + v2.x, this->y + v2.y);
	}

	const Vector2& operator+=(const Vector2 v2)
	{
		this->x += v2.x;
		this->y += v2.y;
		return *this;
	}

	const Vector2& operator*=(const float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		return *this;
	}

	const Vector2 operator+(const Vector2 v2) const
	{
		return Vector2(this->x + v2.x, this->y + v2.y);
	}

};

struct Vector2i
{
	int x;
	int y;

	Vector2i()
	{
		this->x = 0;
		this->y = 0;
	}

	Vector2i(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	const Vector2i operator+(const Vector2i v2)
	{
		return Vector2i(this->x + v2.x, this->y + v2.y);
	}
};

struct Vector3i
{
	int x;
	int y;
	int z;

	Vector3i()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	Vector3i(int x, int y, int z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	const Vector3i operator+(const Vector3i v3)
	{
		return Vector3i(this->x + v3.x, this->y + v3.y, this->z + v3.z);
	}

	bool operator==(const Vector3i v3)
	{
		return (v3.x == this->x && v3.y == this->y && v3.z == this->z);
	}

	bool operator!=(const Vector3i v3)
	{
		return !(*this == v3);
	}
};

struct Vector3;
struct Vector4
{
	float x;
	float y;
	float z;
	float w;

	Vector4() :x(0), y(0), z(0), w(0) {};
	Vector4(Vector3 vec, float w);

	Vector4(float x, float y, float z, float w);

	const Vector4 operator -();
	const Vector4 operator +=(const Vector4);
	const Vector4 operator *(const float x);
	const Vector4 operator*=(const float x);
	const Vector4 operator /=(const float x);
};

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	Vector3(Vector4 vec);

	Vector3(float x, float y, float z);

	Vector3 operator*(float x);

	Vector3 operator/(float x);

	Vector3 operator+(Vector3 x);
	Vector3 operator-(Vector3 x);

	Vector3 operator+=(Vector3 x);
	Vector3 operator-=(Vector3 x);

	Vector3 operator-();
	bool operator==(Vector3 x);
};

struct Matrix4x4
{
	union
	{
		float x[16];
		struct
		{
			Vector4 v1;
			Vector4 v2;
			Vector4 v3;
			Vector4 v4;
		};
	};

	Matrix4x4() :
		x{ 0 }
	{

	}

	const float& operator[](int index) const
	{
		return x[index];
	}

	float& operator[](int index)
	{
		return x[index];
	}

	const Matrix4x4 operator *(const Matrix4x4 m)
	{
		Matrix4x4 result;
		result[0] = x[0] * m[0] + x[4] * m[1] + x[8] * m[2] + x[12] * m[3];
		result[1] = x[1] * m[0] + x[5] * m[1] + x[9] * m[2] + x[13] * m[3];
		result[2] = x[2] * m[0] + x[6] * m[1] + x[10] * m[2] + x[14] * m[3];
		result[3] = x[3] * m[0] + x[7] * m[1] + x[11] * m[2] + x[15] * m[3];

		result[4] = x[0] * m[4] + x[4] * m[5] + x[8] * m[6] + x[12] * m[7];
		result[5] = x[1] * m[4] + x[5] * m[5] + x[9] * m[6] + x[13] * m[7];
		result[6] = x[2] * m[4] + x[6] * m[5] + x[10] * m[6] + x[14] * m[7];
		result[7] = x[3] * m[4] + x[7] * m[5] + x[11] * m[6] + x[15] * m[7];

		result[8] = x[0] * m[8] + x[4] * m[9] + x[8] * m[10] + x[12] * m[11];
		result[9] = x[1] * m[8] + x[5] * m[9] + x[9] * m[10] + x[13] * m[11];
		result[10] = x[2] * m[8] + x[6] * m[9] + x[10] * m[10] + x[14] * m[11];
		result[11] = x[3] * m[8] + x[7] * m[9] + x[11] * m[10] + x[15] * m[11];

		result[12] = x[0] * m[12] + x[4] * m[13] + x[8] * m[14] + x[12] * m[15];
		result[13] = x[1] * m[12] + x[5] * m[13] + x[9] * m[14] + x[13] * m[15];
		result[14] = x[2] * m[12] + x[6] * m[13] + x[10] * m[14] + x[14] * m[15];
		result[15] = x[3] * m[12] + x[7] * m[13] + x[11] * m[14] + x[15] * m[15];
		return result;
	}

	const Matrix4x4 operator *(const Matrix4x4 m) const
	{
		Matrix4x4 result;
		result[0] = x[0] * m[0] + x[4] * m[1] + x[8] * m[2] + x[12] * m[3];
		result[1] = x[1] * m[0] + x[5] * m[1] + x[9] * m[2] + x[13] * m[3];
		result[2] = x[2] * m[0] + x[6] * m[1] + x[10] * m[2] + x[14] * m[3];
		result[3] = x[3] * m[0] + x[7] * m[1] + x[11] * m[2] + x[15] * m[3];

		result[4] = x[0] * m[4] + x[4] * m[5] + x[8] * m[6] + x[12] * m[7];
		result[5] = x[1] * m[4] + x[5] * m[5] + x[9] * m[6] + x[13] * m[7];
		result[6] = x[2] * m[4] + x[6] * m[5] + x[10] * m[6] + x[14] * m[7];
		result[7] = x[3] * m[4] + x[7] * m[5] + x[11] * m[6] + x[15] * m[7];

		result[8] = x[0] * m[8] + x[4] * m[9] + x[8] * m[10] + x[12] * m[11];
		result[9] = x[1] * m[8] + x[5] * m[9] + x[9] * m[10] + x[13] * m[11];
		result[10] = x[2] * m[8] + x[6] * m[9] + x[10] * m[10] + x[14] * m[11];
		result[11] = x[3] * m[8] + x[7] * m[9] + x[11] * m[10] + x[15] * m[11];

		result[12] = x[0] * m[12] + x[4] * m[13] + x[8] * m[14] + x[12] * m[15];
		result[13] = x[1] * m[12] + x[5] * m[13] + x[9] * m[14] + x[13] * m[15];
		result[14] = x[2] * m[12] + x[6] * m[13] + x[10] * m[14] + x[14] * m[15];
		result[15] = x[3] * m[12] + x[7] * m[13] + x[11] * m[14] + x[15] * m[15];
		return result;
	}

	const Vector4 operator * (const Vector4 v)
	{
		Vector4 result;

		result.x = x[0] * v.x + x[4] * v.y + x[8] * v.z + x[12] * v.w;
		result.y = x[1] * v.x + x[5] * v.y + x[9] * v.z + x[13] * v.w;
		result.z = x[2] * v.x + x[6] * v.y + x[10] * v.z + x[14] * v.w;
		result.w = x[3] * v.x + x[7] * v.y + x[11] * v.z + x[15] * v.w;
		return result;
	}

	const Vector4 operator * (const Vector4 v) const
	{
		Vector4 result;

		result.x = x[0] * v.x + x[4] * v.y + x[8] * v.z + x[12] * v.w;
		result.y = x[1] * v.x + x[5] * v.y + x[9] * v.z + x[13] * v.w;
		result.z = x[2] * v.x + x[6] * v.y + x[10] * v.z + x[14] * v.w;
		result.w = x[3] * v.x + x[7] * v.y + x[11] * v.z + x[15] * v.w;
		return result;
	}

	const Vector3 operator *(const Vector3 v)
	{
		Vector4 result = (*this) * Vector4(v, 0.0f);
		return Vector3(result.x, result.y, result.z);
	}

};

namespace Math
{
	float Length(Vector2 v);
	float Dot(Vector2 v1, Vector2 v2);
	float Dot(Vector3 v1, Vector3 v2);
	Vector2 Normalize(Vector2 v);
	Vector2 Rotate(float angle, Vector2 v);
	float Distance(Vector2 v1, Vector2 v2);

	float Abs(float x);
	bool FloatEqual(float a, float b, float epsilon = 0.0001f);
	bool FloatEqual(Vector3 v1, Vector3 v2, float epsilon = 0.0001f);

	const Matrix4x4 GetTranslation(Vector3 vec);
	const Matrix4x4 GetTranslation(const float dx, const float dy, const float dz);
	const Matrix4x4 GetRotation(const float angle, Vector3 axis);
	const Matrix4x4 GetIdentity();
	const Matrix4x4 GetScale(const float sx, const float sy, const float sz);

	Vector3 Normalize(Vector3 v);
	float Length(Vector3 v);
	Vector3 CrossProduct(Vector3 v1, Vector3 v2);
}


#pragma once
