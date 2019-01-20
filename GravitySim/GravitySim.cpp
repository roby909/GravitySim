// GravitySim.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Circle.h"

constexpr int INIT_NUMBER_OF_CIRCLES = 5;
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

// generate a random radius
int randomRadius()
{
	return random(20, 100);
}

Circle createCircle(const int &x, const int &y, const int &radius, const double &density, const double &scaling_factor)
{
	Circle resultCircle;
	
	resultCircle.shape.setRadius(radius);
	resultCircle.calculateMass(density, scaling_factor);
	resultCircle.setPosition(x, y);
	resultCircle.setColor(sf::Color(random(0, 255), random(0, 255), random(0, 255)));
	resultCircle.enabled = true;
	return resultCircle;
}

// creates random circles
void createCircles(const double &density, const double &scaling_factor, Circle* circles) {
	for (int i = 0; i < INIT_NUMBER_OF_CIRCLES; i++)
	{
		int radius = randomRadius();
		circles[i] = createCircle(random(0, WINDOW_WIDTH - radius * 2), random(0, WINDOW_HEIGHT - radius * 2), 
			radius, density, scaling_factor);
	}
}

int main()
{
	srand(time(NULL));	// random number generator initialization
	
	const double gravitational_constant = 6.674 * pow(10, -11);
	const double density = 5.51;	// kg/m^3
	const double scaling_factor = 100000000;
	int number_of_circles = 5;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GravitySim");
	
	Circle* circles = new Circle[INIT_NUMBER_OF_CIRCLES];
	createCircles(density, scaling_factor, circles);

	number_of_circles = INIT_NUMBER_OF_CIRCLES;

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

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)	// if we press the left mouse button, we create a new circle
				{	
					// fetch mouse coordinates
					int newX = sf::Mouse::getPosition(window).x;
					int newY = sf::Mouse::getPosition(window).y;
					
					// create new circles array
					Circle* newCircles = new Circle[number_of_circles + 1];
					std::copy(circles, circles + number_of_circles, newCircles);
					delete[] circles;
					circles = newCircles;
										
					// create the new circle
					circles[number_of_circles] = createCircle(newX, newY, randomRadius(), density, scaling_factor);
					number_of_circles++;
				}
			}
		}

		window.clear(sf::Color(40, 40, 40));

		for (int i = 0; i < number_of_circles; i++)
		{
			// applying gravitational force to the circles			
			double x_movement = 0.0;
			double y_movement = 0.0;

			for (int j = 0; j < number_of_circles; j++)
			{
				if (j != i && circles[i].enabled && circles[j].enabled)
				{					
					// a = F/m
					// F = G * ((m1 * m2) / r^2)

					double vector_inbetween_x = circles[j].getX() - circles[i].getX();
					double vector_inbetween_y = circles[j].getY() - circles[i].getY();
					double distance = vector_length(vector_inbetween_x, vector_inbetween_y);					
					
					//if (distance > circles[i].shape.getRadius() + circles[j].shape.getRadius())
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
						// shift the two circles as if they have collided
						/*x_movement = (circles[i].getX() - circles[j].getX()) / circles[i].shape.getRadius();
						y_movement = (circles[i].getY() - circles[j].getY()) / circles[i].shape.getRadius();*/

						// assimilate the two circles together
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
			
			circles[i].setPosition(circles[i].getX() + x_movement, circles[i].getY() + y_movement);	// apply the movement
			circles[i].draw(window);	// drawing the circles			
		}

		window.display();
	}

	delete[] circles;
    return 0;
}