#include "vector2.h"
#include "cmath"

float Vector2::length(){
    return std::sqrt(x * x + y * y);
}

Vector2 Vector2::normalize(){
	float len = length();
	if (len == 0)
		return Vector2(0, 0);
	return Vector2(x / len, y / len);
}

Vector2 Vector2::operator+(const Vector2& vec) const {
	return Vector2(x + vec.x, y + vec.y);
}

Vector2 Vector2::operator-(const Vector2& vec) const {
	return Vector2(x - vec.x, y - vec.y);
}

float Vector2::operator*(const Vector2& vec) const {
	return x * vec.x + y * vec.y;
}

Vector2 Vector2::operator*(float val) const {
	return Vector2(val * x, val * y);
}
