#include "Vector2.hpp"

Vector2 Vector2::intersection(const Vector2& A, const Vector2& B, const Vector2& C, const Vector2& D){
    float x1 = A.x, x2 = B.x, x3 = C.x, x4 = D.x;
    float y1 = A.y, y2 = B.y, y3 = C.y, y4 = D.y;
    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    if (d == 0)
        return {FLT_MAX, FLT_MAX};
    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / d;
    float u = ((x1 - x3) * (y1 - y2) - (y1 - y3) * (x1 - x2)) / d;
    if(t < 0 || t > 1 || u < 0 || u > 1)
        return {FLT_MAX, FLT_MAX};
    float x = x1 + t * (x2 - x1);
    float y = y1 + t * (y2 - y1);
    return {x, y};
}

Vector2 Vector2::rotate(const Vector2& vec, float angle){
    float x = vec.x * cos(degToRad(angle)) + vec.y * sin(degToRad(angle));
	float y = vec.y * cos(degToRad(angle)) - vec.x * sin(degToRad(angle));
    return {x, y};
}
Vector2 Vector2::rotate(const Vector2& vec, float angle, float distance){
    float x = (distance * cos(degToRad(angle))) + vec.x;
	float y = (-distance * sin(degToRad(angle))) + vec.y;
    return {x, y};
}

Vector2 Vector2::normalize(const Vector2& vec) {
    float lngth = length(vec);
    return {vec.x / lngth, vec.y / lngth};
}

Vector2 Vector2::mult(const Vector2& vec, float scalar){
    return {vec.x * scalar, vec.y * scalar};
}

Vector2 Vector2::sum(const Vector2& A, const Vector2& B){
    return {A.x + B.x, A.y + B.y};
}

Vector2 Vector2::sub(const Vector2& A, const Vector2& B){
    return {A.x - B.x, A.y - B.y};
}

Vector2 Vector2::position(const Vector2& pos, const Vector2& axisX, const Vector2& axisY, const Vector2& center) {
    Vector2 posX = Vector2::mult(axisX, pos.x - center.x);
	Vector2 posY = Vector2::mult(axisY, pos.y - center.y);
	Vector2 position = Vector2::sum(posX, posY);
	position = Vector2::sum(position, center);
	return position;
}

float Vector2::length(const Vector2& vec){
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2));
}

float Vector2::length(const Vector2& start, const Vector2& end){
    return sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));
}

float Vector2::degToRad(float deg){
    return deg * PI / 180;
}