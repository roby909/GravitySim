#pragma once
#include <iostream>

class Vector2D
{
private:
	float x, y;
public:
	float GetX();
	float GetY();
	float GetLength();
	void SetX(float x);
	void SetY(float y);
	void Set(float x, float y);
	void ToUnitVector();
	Vector2D(float x, float y);
	Vector2D();
	~Vector2D();

	Vector2D operator+(Vector2D& other);
	Vector2D operator-(Vector2D& other);
	Vector2D operator*(double& other);
	friend std::ostream& operator<<(std::ostream &out, const Vector2D &vec);
};
