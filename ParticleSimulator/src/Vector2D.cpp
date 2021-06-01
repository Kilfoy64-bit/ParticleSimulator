#include "Vector2D.h"

#include <math.h>

void Vector2D::calculatePoint()
{
	m_Xcomponent = m_Magnitude * cos(m_Theta);
	m_Ycomponent = m_Magnitude * sin(m_Theta);
}

void Vector2D::calculateTheta()
{
	m_Theta = atan(m_Ycomponent / m_Xcomponent);
}

Vector2D::Vector2D(float magnitude, double theta)
	: m_Magnitude(magnitude), m_Theta(theta)
{
	calculatePoint();
};

Vector2D::Vector2D(float x, float y)
	: m_Xcomponent(x), m_Ycomponent(y)
{
	m_Magnitude = (x * x) + (y * y);
	calculateTheta();
}

void Vector2D::normalize(float target)
{
	if (target != 0) {
		m_Magnitude = m_Magnitude / target;
		m_Xcomponent = m_Xcomponent / target;
		m_Ycomponent = m_Ycomponent / target;
	}
	else {
		m_Magnitude = target;
		m_Xcomponent = target;
		m_Ycomponent = target;
	}

}

void Vector2D::setMagnitude(float magnitude)
{
	m_Magnitude = magnitude;
	calculatePoint();
}

void Vector2D::setComponents(float x, float y)
{
	m_Xcomponent = x;
	m_Ycomponent = y;
	calculateTheta();
}

void Vector2D::setTheta(double theta)
{
	m_Theta = theta;
	calculatePoint();
}