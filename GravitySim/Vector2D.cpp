#include "stdafx.h"
#include "Vector2D.h"

float Vector2D::GetX()
{
	return x;
}

float Vector2D::GetY()
{
	return y;
}

float Vector2D::GetLength()
{
	return (float)sqrt(x * x + y * y);
}

void Vector2D::SetX(float x)
{
	this->x = x;
}

void Vector2D::SetY(float y)
{
	this->y = y;
}

void Vector2D::Set(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Vector2D::ToUnitVector()
{	
	x /= GetLength();
	y /= GetLength();
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D::Vector2D()
{
	this->x = 0.0;
	this->y = 0.0;
}

Vector2D::~Vector2D() {}

Vector2D Vector2D::operator+(Vector2D& other)
{
	Vector2D result(this->GetX() + other.GetX(), this->GetY() + other.GetY());	
	return result;
}

Vector2D Vector2D::operator-(Vector2D& other)
{
	Vector2D result(this->GetX() - other.GetX(), this->GetY() - other.GetY());
	return result;
}

Vector2D Vector2D::operator*(double other)
{
	Vector2D result(this->GetX() * other, this->GetY() * other);
	return result;
}

std::ostream& operator<<(std::ostream &out, const Vector2D &vec)
{
	out << "(" << vec.x << ", " << vec.y << ")";
	return out;
}