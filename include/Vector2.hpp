#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include "math.h"
#include "float.h"
#define PI 3.14159265359f

class Vector2 final {
public:
	Vector2(float x = 0.f, float y = 0.f): x(x), y(y){}
	static Vector2 intersection(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D);
	static Vector2 rotate(const Vector2& vec, float angle);
	static Vector2 rotate(const Vector2& vec, float angle, float distance);
	static Vector2 normalize(const Vector2& vec);
	static Vector2 mult(const Vector2& vec, float scalar);
	static Vector2 sum(const Vector2& A, const Vector2& B);
	static Vector2 sub(const Vector2& A, const Vector2& B);
	static Vector2 position(const Vector2& pos, const Vector2& axisX, const Vector2& axisY, const Vector2& center);
	static float length(const Vector2& vec);
	static float length(const Vector2& start, const Vector2& end);
	static float degToRad(float deg);
	float x;
	float y;
};

#endif