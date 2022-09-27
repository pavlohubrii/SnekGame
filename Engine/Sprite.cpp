#include "Sprite.h"

void Sprite::DrawGameOver(Graphics& gfx)
{
	Color c = Colors::White;

	gfx.PutPixel(x + 1, y, c);
	gfx.PutPixel(x + 2, y, c);
	gfx.PutPixel(x + 3, y, c);
	gfx.PutPixel(x + 4, y, c);
	gfx.PutPixel(x + 5, y, c);

	gfx.PutPixel(x, y + 1, c);
	gfx.PutPixel(x, y + 2, c);
	gfx.PutPixel(x, y + 3, c);
	gfx.PutPixel(x, y + 4, c);
	gfx.PutPixel(x, y + 5, c);

	gfx.PutPixel(x + 1, y + 6, c);
	gfx.PutPixel(x + 2, y + 6, c);
	gfx.PutPixel(x + 3, y + 6, c);
	gfx.PutPixel(x + 4, y + 6, c);
	gfx.PutPixel(x + 5, y + 6, c);

	gfx.PutPixel(x + 5, y + 5, c);
	gfx.PutPixel(x + 5, y + 4, c);
	gfx.PutPixel(x + 4, y + 4, c);

	gfx.PutPixel(x + 11, y, c);
	gfx.PutPixel(x + 12, y, c);
	gfx.PutPixel(x + 13, y, c);
	gfx.PutPixel(x + 14, y, c);
	gfx.PutPixel(x + 15, y, c);

	gfx.PutPixel(x + 10, y + 1, c);
	gfx.PutPixel(x + 10, y + 2, c);
	gfx.PutPixel(x + 10, y + 3, c);
	gfx.PutPixel(x + 10, y + 4, c);
	gfx.PutPixel(x + 10, y + 5, c);

	gfx.PutPixel(x + 11, y + 6, c);
	gfx.PutPixel(x + 12, y + 6, c);
	gfx.PutPixel(x + 13, y + 6, c);
	gfx.PutPixel(x + 14, y + 6, c);
	gfx.PutPixel(x + 15, y + 6, c);

	gfx.PutPixel(x + 15, y + 5, c);
	gfx.PutPixel(x + 15, y + 4, c);
	gfx.PutPixel(x + 14, y + 4, c);

}

