#pragma once

#include <math.h>

class Vector2D {
private:
	float m_Xcomponent;
	float m_Ycomponent;
	float m_Magnitude;
	double m_Theta;
	
	void calculatePoint();
	void calculateTheta();

public:
	Vector2D()
		: m_Xcomponent(0.0f), m_Ycomponent(0.0f), m_Magnitude(0.0f), m_Theta(0.0) {};
	Vector2D(float magnitude, double theta);
	Vector2D(float x, float y);

	void normalize(float target);

	void setMagnitude(float magnitude);
	void setComponents(float x, float y);
	void setTheta(double theta);
	
	inline float getX() const { return m_Xcomponent; }
	inline float getY() const { return m_Ycomponent; }
	inline float getMagnitude() const { return m_Magnitude; }
	inline double getTheta() const { return m_Theta; }
};