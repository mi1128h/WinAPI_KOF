#include "config.h"

inline void RenderRect(HDC hdc, int ltX, int ltY, int width, int height)
{
	Rectangle(hdc, ltX, ltY, ltX + width, ltY + height);
}

inline void RenderRectAtCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Rectangle(hdc, centerX - width / 2, centerY - height / 2, centerX + width / 2, centerY + height / 2);
}

inline void RenderEllipse(HDC hdc, int ltX, int ltY, int width, int height)
{
	Ellipse(hdc, ltX, ltY, ltX + width, ltY + height);
}

inline void RenderEllipseAtCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Ellipse(hdc, centerX - width / 2, centerY - height / 2, centerX + width / 2, centerY + height / 2);
}

inline RECT GetRect(int left, int top, int width, int height)
{
	return RECT{ left, top, left + width, top + height };
}

inline RECT GetRectAtCenter(int x, int y, int width, int height)
{
	return RECT{ x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
}

inline bool PointInRect(FPOINT ptMouse, RECT rc)
{
	if (ptMouse.x < rc.left or ptMouse.x > rc.right) return false;
	if (ptMouse.y < rc.top or ptMouse.y > rc.bottom) return false;
	return true;
}

inline void UpdateRect(RECT& rc, FPOINT pt)
{
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	rc.left = pt.x - width / 2;
	rc.right = rc.left + width;
	rc.top = pt.y - height / 2;
	rc.bottom = rc.top + height;
}

inline void MoveRect(RECT& rc, int dx, int dy)
{
	rc.left += dx;
	rc.right += dx;
	rc.top += dy;
	rc.bottom += dy;
}

inline bool RectInRect(RECT rc1, RECT rc2)
{
	if (rc1.left > rc2.right) return false;
	if (rc1.right < rc2.left) return false;
	if (rc1.top > rc2.bottom) return false;
	if (rc1.bottom < rc2.top) return false;
	return true;
}

inline bool IsOutOfRange(FPOINT pos, int size_x, int size_y)
{
	if (pos.x < 0) return true;
	if (pos.y < 0) return true;
	if (pos.x > size_x) return true;
	if (pos.y > size_y) return true;
	return false;
}

template<typename T>
inline T ClampVal(T val, T low, T high)
{
	T retVal;
	if (val < low) retVal = low;
	else if (val > high) retVal = high;
	else retVal = val;

	return retVal;
}

inline bool CircleCollideCircle(FPOINT position, FPOINT targetPos, int size, int targetSize)
{
	int dx = targetPos.x - position.x;
	int dy = targetPos.y - position.y;
	int rSum = targetSize / 2 + size / 2;
	return ((dx * dx + dy * dy) < (rSum * rSum));
}

inline float GetDistance(FPOINT a, FPOINT b)
{
	int dx = a.x - b.x;
	int dy = a.y - b.y;
	return sqrtf(dx * dx + dy * dy);
}

inline float GetAngle(FPOINT position, FPOINT targetPos)
{
	float dx = targetPos.x - position.x;
	float dy = targetPos.y - position.y;
	return TODEGREE(-atan2f(dy, dx));
}