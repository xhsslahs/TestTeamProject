#pragma once

enum DIRECTION
{
	NONE,
	UP,
	DOWN,
	RIGHT,
	LEFT
};

inline RECT GetRect(POINT pos, int width, int height)
{	
	RECT rc;
	rc.left = pos.x;
	rc.top = pos.y;
	rc.right = pos.x + width;
	rc.bottom = pos.y + height;

	return rc;
}

inline DIRECTION GetCollisionDirection(RECT player, RECT obj)
{	
	RECT rc;
	if (IntersectRect(&rc, &player, &obj))
	{
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;
		
		if (width < height) //오른쪽 왼쪽 충돌 경우
		{
			if (player.left > obj.left)
			{
				return RIGHT;
			}
			else
			{
				return LEFT;
			}
		}
		else
		{
			if (player.top > obj.top)
			{
				return DOWN;
			}
			else
			{
				return UP;
			}
		}
	}
	else
	{
		return NONE;
	}
}

inline void MakeCeterCircle(HDC hdc, POINT pos, int radius)
{
	Ellipse(hdc, pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius);
}