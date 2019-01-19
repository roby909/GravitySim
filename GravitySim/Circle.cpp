#include "stdafx.h"
#include "Circle.h"

double Circle::getMass()
{
	return mass;
}

void Circle::setMass(const double &mass)
{
	this->mass = mass;
}

void Circle::calculateMass(const double &density, const double &scaling_factor)
{
	setMass(density * getVolume() * scaling_factor);
}

void Circle::setPosition(float x, float y)
{
	shape.setPosition(x - shape.getRadius(), y - shape.getRadius());
}

float Circle::getX()
{
	return shape.getPosition().x + shape.getRadius();
}

float Circle::getY()
{
	return shape.getPosition().y + shape.getRadius();
}

Vector2D Circle::getPosition()
{
	return Vector2D(this->getX(), this->getY());
}

double Circle::getVolume()
{
	return shape.getRadius() * shape.getRadius() * PI;
}

sf::Color Circle::getColor()
{
	return shape.getFillColor();
}

void Circle::setColor(sf::Color color)
{	
	shape.setFillColor(color);
}

void Circle::draw(sf::RenderWindow &window)
{
	if (enabled)
		window.draw(shape);
}

int Circle::getRed()
{
	return shape.getFillColor().r;
}

int Circle::getGreen()
{
	return shape.getFillColor().g;
}

int Circle::getBlue()
{
	return shape.getFillColor().b;
}

void Circle::setRed(const int &red)
{
	shape.setFillColor(sf::Color(red, getGreen(), getBlue()));
}

void Circle::setGreen(const int &green)
{
	shape.setFillColor(sf::Color(getRed(), green, getBlue()));
}

void Circle::setBlue(const int &blue)
{
	shape.setFillColor(sf::Color(getRed(), getGreen(), blue));
}

Circle::Circle()
{
	enabled = true;
	shape.setPosition(0, 0);
	shape.setRadius(50.0f);	
	setMass(1);
}

Circle::Circle(const float &xPos, const float &yPos, const double &radius, const double &mass, const sf::Color &color)
{
	enabled = true;
	shape.setPosition(xPos, yPos);
	shape.setRadius(radius);	
	shape.setFillColor(color);
	setMass(mass);
}

Circle::~Circle()
{
}