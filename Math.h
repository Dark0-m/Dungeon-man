#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>

#define PI 3.14159265358979

class Math {
	public:
		float lerp(float start, float end, float t) {
			return start + t * (end - start);
		}

		double getDistance(float x1, float x2){
			return sqrt(abs(pow(x2, 2) - pow(x1, 2)));
		}

		double getDistance(sf::Vector2f v1, sf::Vector2f v2) {
			return sqrt(abs(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2)));
		}

		double getAngle(sf::Vector2f a) {
			return atan2(a.y, a.x);
		}

		double RadToDeg(float rad) {
			return rad * (180 / PI);
		}

		double DegToRad(float deg) {
			return deg * (PI / 180);
		}

};