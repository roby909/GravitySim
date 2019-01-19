// GravitySim.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Circle.h"

constexpr int NUMBER_OF_CIRCLES = 20;
constexpr int WINDOW_WIDTH = 1280;
constexpr int WINDOW_HEIGHT = 720;

double vector_length(double x, double y)
{
	return (double)sqrt(x * x + y * y);
}

double greater(double a, double b)
{
	return (a >= b ? a : b);
}

double less(double a, double b)
{
	return (a <= b ? a : b);
}

int random(const int &min, const int &max)
{
	int randNum = rand() % (max - min + 1) + min;
	return randNum;
}

// creates random circles
void createCircles(const double &density, const double &scaling_factor, Circle* circles) {
	for (int i = 0; i < NUMBER_OF_CIRCLES; i++)
	{
		int radius = random(20, 100);
		circles[i].shape.setRadius(radius);
		circles[i].calculateMass(density, scaling_factor);
		circles[i].setPosition(random(0, WINDOW_WIDTH - radius * 2), random(0, WINDOW_HEIGHT - radius * 2));
		circles[i].setColor(sf::Color(random(0, 255), random(0, 255), random(0, 255)));
		circles[i].enabled = true;
	}
}

int main()
{
	srand(time(NULL));	// random number generator initialization
	
	const double gravitational_constant = 6.674 * pow(10, -11);
	const double density = 5.51;	// kg/m^3
	const double scaling_factor = 100000000;	

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GravitySim");
	
	Circle circles[NUMBER_OF_CIRCLES];		
	createCircles(density, scaling_factor, circles);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)			
				window.close();

			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::R) {	// reset if we press R
					createCircles(density, scaling_factor, circles);
				}
			}
		}

		window.clear(sf::Color(40, 40, 40));

		for (int i = 0; i < NUMBER_OF_CIRCLES; i++)
		{
			// applying gravitational force to the circles
			double x_movement = 0.0;
			double y_movement = 0.0;

			for (int j = 0; j < NUMBER_OF_CIRCLES; j++)
			{
				if (j != i && circles[i].enabled && circles[j].enabled)
				{
					// a = F/m
					// F = G * ((m1 * m2) / r^2)

					double vector_inbetween_x = circles[j].getX() - circles[i].getX();
					double vector_inbetween_y = circles[j].getY() - circles[i].getY();
					double distance = vector_length(vector_inbetween_x, vector_inbetween_y);					
					
					if (distance > 10.0)
					{
						double force = gravitational_constant * ((circles[i].getMass() * circles[j].getMass()) / (distance * distance));
						double acceleration = force / circles[i].getMass();																	

						x_movement += vector_inbetween_x;
						y_movement += vector_inbetween_y;
						double lngth = vector_length(x_movement, y_movement);

						x_movement /= lngth;
						y_movement /= lngth;

						x_movement *= acceleration;
						y_movement *= acceleration;
					}
					else
					{
						if (circles[i].shape.getRadius() > circles[j].shape.getRadius())
						{
							circles[i].shape.setRadius(circles[i].shape.getRadius() + sqrt(circles[j].shape.getRadius()));
							circles[i].calculateMass(density, scaling_factor);
							
							circles[j].enabled = false;
						}
						else
						{
							circles[j].shape.setRadius(circles[j].shape.getRadius() + sqrt(circles[i].shape.getRadius()));
							circles[j].calculateMass(density, scaling_factor);

							circles[i].enabled = false;
						}
					}
				}
			}
			
			circles[i].setPosition(circles[i].getX() + x_movement, circles[i].getY() + y_movement);
			circles[i].draw(window);	// drawing the circles			
		}

		window.display();
	}

    return 0;
}

