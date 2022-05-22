#pragma once

class Box {
private:
	float m_TopMargin;
	float m_BottomMargin;
	float m_LeftMargin;
	float m_RightMargin;

public:
	Box(float width, float height)
		: m_LeftMargin(0.0f), m_RightMargin(width), m_BottomMargin(0.0f), m_TopMargin(height) {};
	Box(float left, float right, float bottom, float top)
		: m_LeftMargin(left), m_RightMargin(right), m_BottomMargin(bottom), m_TopMargin(top) {};

	inline float getTop() const { return m_TopMargin; }
	inline float getBottom() const { return m_BottomMargin; }
	inline float getLeft() const { return m_LeftMargin; }
	inline float getRight() const { return m_RightMargin; }

	inline void setTop(float top) { m_TopMargin = top; }
	inline void setBottom(float bottom) { m_BottomMargin = bottom; }
	inline void setLeft(float left) { m_LeftMargin = left; }
	inline void setRight(float right) { m_RightMargin = right; }
};
