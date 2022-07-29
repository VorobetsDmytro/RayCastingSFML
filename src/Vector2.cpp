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

Vector2 Vector2::rotate(float angle, float distance){
    float x = distance * cos(degToRad(angle));
	float y = -distance * sin(degToRad(angle));
    return {x, y};
}

Vector2 Vector2::normalize(const Vector2& vec) {
    float lngth = length(vec);
    return {vec.x / lngth, vec.y / lngth};
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