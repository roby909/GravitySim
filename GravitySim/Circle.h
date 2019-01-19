#pragma once
#include "stdafx.h"
#include "Vector2D.h"
#include <SFML/Graphics.hpp>

#define PI 3.14159265358979323846

class Circle
{
public:
	bool enabled;
	void setMass(const double &mass);
	void calculateMass(const double &density, const double &scaling_factor);	// this method calculates the mass with the provided density and the circle's radius
	void setPosition(float x, float y);
	float getX();
	float getY();
	Vector2D getPosition();
	double getMass();
	double getVolume();
	sf::Color getColor();
	void setColor(sf::Color color);

	void draw(sf::RenderWindow &window);	// call this in your loop to draw the circle
	
	int getRed();
	int getGreen();
	int getBlue();
	void setRed(const int &red);
	void setGreen(const int &green);
	void setBlue(const int &blue);

	sf::CircleShape shape;
	Circle();
	Circle(const float &xPos, const float &yPos, const double &radius, const double &mass, const sf::Color &color);
	~Circle();
private:
	double mass;	
};