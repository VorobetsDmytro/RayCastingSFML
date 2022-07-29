#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include "math.h"
#include "float.h"
#define PI 3.14f

class Vector2 final {
public:
	Vector2(float x = 0.f, float y = 0.f): x(x), y(y){}
	static Vector2 intersection(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D);
	static Vector2 rotate(float angle, float distance);
	static Vector2 normalize(const Vector2& vec);
	static float length(const Vector2& vec);
	static float length(const Vector2& start, const Vector2& end);
	static float degToRad(float deg);
	float x;
	float y;
};

#endif