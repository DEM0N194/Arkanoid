#include "Graphics.h"

void Graphics::Block(int x, int y, Color c)
{
	for (int xPos = x; xPos <= (x + 3); xPos++)
	{
		for (int yPos = y; yPos <= (y + 3); yPos++)
		{
			PutPixel(xPos, yPos, c);
		}
	}
}

void Graphics::chA(int x, int y, Color c)
{
	Block(x+10, y, c);

	Block(x+5, y+5, c);
	Block(x+15, y+5, c);

	Block(x, y+10, c);
	Block(x+20, y+10, c);

	Block(x, y+15, c);
	Block(x+5, y + 15, c);
	Block(x+10, y + 15, c);
	Block(x+15, y + 15, c);
	Block(x+20, y + 15, c);

	Block(x, y + 20, c);
	Block(x+20, y + 20, c);

	Block(x, y + 25, c);
	Block(x+20, y + 25, c);
}
void Graphics::chB(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+5, y, c);
	Block(x+10, y, c);
	Block(x+15, y, c);

	Block(x, y+5, c);
	Block(x+20, y+5, c);

	Block(x, y+10, c);
	Block(x+5, y+10, c);
	Block(x+10, y+10, c);
	Block(x+15, y+10, c);

	Block(x, y+15, c);
	Block(x+20, y+15, c);

	Block(x, y+20, c);
	Block(x+20, y+20, c);

	Block(x, y+25, c);
	Block(x+5, y+25, c);
	Block(x+10, y+25, c);
	Block(x+15, y+25, c);
}
void Graphics::chC(int x, int y, Color c)
{
	Block(x+5, y, c);
	Block(x+10, y, c);
	Block(x+15, y, c);

	Block(x, y+5, c);
	Block(x+20, y+5, c);

	Block(x, y+10, c);

	Block(x, y+15, c);

	Block(x, y+20, c);
	Block(x+20, y+20, c);

	Block(x+5, y+25, c);
	Block(x+10, y+25, c);
	Block(x+15, y+25, c);
}
void Graphics::chD(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+5, y, c);
	Block(x+10, y, c);

	Block(x, y+5, c);
	Block(x+15, y+5, c);

	Block(x, y+10, c);
	Block(x+20, y+10, c);

	Block(x, y+15, c);
	Block(x+20, y+15, c);

	Block(x, y+20, c);
	Block(x+15, y+20, c);

	Block(x, y+25, c);
	Block(x+5, y+25, c);
	Block(x+10, y+25, c);
}
void Graphics::chE(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+5, y, c);
	Block(x+10, y, c);
	Block(x+15, y, c);
	Block(x+20, y, c);

	Block(x, y+5, c);

	Block(x, y+10, c);
	Block(x+5, y+10, c);
	Block(x+10, y+10, c);

	Block(x, y+15, c);

	Block(x, y+20, c);

	Block(x, y+25, c);
	Block(x+5, y+25, c);
	Block(x+10, y+25, c);
	Block(x+15, y+25, c);
	Block(x+20, y+25, c);
}
void Graphics::chF(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+5, y, c);
	Block(x+10, y, c);
	Block(x+15, y, c);
	Block(x+20, y, c);

	Block(x, y+5, c);

	Block(x, y+10, c);
	Block(x+5, y+10, c);
	Block(x+10, y+10, c);

	Block(x, y+15, c);

	Block(x, y+20, c);

	Block(x, y+25, c);
}
void Graphics::chG(int x, int y, Color c)
{
	Block(x+5, y, c);
	Block(x+10, y, c);
	Block(x+15, y, c);

	Block(x, y+5, c);
	Block(x+20, y+5, c);

	Block(x, y+10, c);

	Block(x, y+15, c);
	Block(x+10, y+15, c);
	Block(x+15, y+15, c);
	Block(x+20, y+15, c);

	Block(x, y+20, c);
	Block(x+20, y+20, c);

	Block(x+5, y+25, c);
	Block(x+10, y+25, c);
	Block(x+15, y+25, c);
}
void Graphics::chH(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+20, y, c);

	Block(x, y+5, c);
	Block(x+20, y+5, c);

	Block(x, y+10, c);
	Block(x+5, y+10, c);
	Block(x+10, y+10, c);
	Block(x+15, y+10, c);
	Block(x+20, y+10, c);

	Block(x, y+15, c);
	Block(x+20, y+15, c);

	Block(x, y+20, c);
	Block(x+20, y+20, c);

	Block(x, y+25, c);
	Block(x+20, y+25, c);
}
void Graphics::chI(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+5, y, c);
	Block(x+10, y, c);
	Block(x+15, y, c);
	Block(x+20, y, c);

	Block(x+10, y+5, c);

	Block(x+10, y+10, c);

	Block(x+10, y+15, c);

	Block(x+10, y+20, c);

	Block(x, y+25, c);
	Block(x+5, y+25, c);
	Block(x+10, y+25, c);
	Block(x+15, y+25, c);
	Block(x+20, y+25, c);
}
void Graphics::chJ(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+5, y, c);
	Block(x+10, y, c);
	Block(x+15, y, c);
	Block(x+20, y, c);

	Block(x+10, y+5, c);

	Block(x+10, y+10, c);

	Block(x+10, y+15, c);

	Block(x, y+20, c);
	Block(x+10, y+20, c);

	Block(x+5, y+25, c);
	Block(x+10, y+25, c);
}
void Graphics::chK(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+20, y, c);

	Block(x, y+5, c);
	Block(x+15, y+5, c);

	Block(x, y+10, c);
	Block(x+5, y+10, c);
	Block(x+10, y+10, c);

	Block(x, y+15, c);
	Block(x+10, y+15, c);

	Block(x, y+20, c);
	Block(x+15, y+20, c);

	Block(x, y+25, c);
	Block(x+20, y+25, c);
}
void Graphics::chL(int x, int y, Color c)
{
	Block(x, y, c);

	Block(x, y+5, c);

	Block(x, y+10, c);

	Block(x, y+15, c);

	Block(x, y+20, c);

	Block(x, y+25, c);
	Block(x+5, y+25, c);
	Block(x+10, y+25, c);
	Block(x+15, y+25, c);
	Block(x+20, y+25, c);
}
void Graphics::chM(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+20, y, c);

	Block(x, y+5, c);
	Block(x+5, y+5, c);
	Block(x+15, y+5, c);
	Block(x+20, y+5, c);

	Block(x, y+10, c);
	Block(x+10, y+10, c);
	Block(x+20, y+10, c);

	Block(x, y+15, c);
	Block(x+10, y+15, c);
	Block(x+20, y+15, c);

	Block(x, y+20, c);
	Block(x+20, y+20, c);

	Block(x, y+25, c);
	Block(x+20, y+25, c);
}
void Graphics::chN(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+20, y, c);

	Block(x, y+5, c);
	Block(x+5, y+5, c);
	Block(x+20, y+5, c);

	Block(x, y+10, c);
	Block(x+10, y+10, c);
	Block(x+20, y+10, c);

	Block(x, y+15, c);
	Block(x+15, y+15, c);
	Block(x+20, y+15, c);

	Block(x, y+20, c);
	Block(x+20, y+20, c);

	Block(x, y+25, c);
	Block(x+20, y+25, c);
}
void Graphics::chO(int x, int y, Color c)
{
	Block(x+5, y, c);
	Block(x+10, y, c);
	Block(x+15, y, c);

	Block(x, y+5, c);
	Block(x+20, y+5, c);

	Block(x, y+10, c);
	Block(x+20, y+10, c);

	Block(x, y+15, c);
	Block(x+20, y+15, c);

	Block(x, y+20, c);
	Block(x+20, y+20, c);

	Block(x+5, y+25, c);
	Block(x+10, y+25, c);
	Block(x+15, y+25, c);
}
void Graphics::chP(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+5, y, c);
	Block(x+10, y, c);
	Block(x+15, y, c);

	Block(x, y+5, c);
	Block(x+20, y+5, c);

	Block(x, y+10, c);
	Block(x+5, y+10, c);
	Block(x+10, y+10, c);
	Block(x+15, y+10, c);

	Block(x, y+15, c);

	Block(x, y+20, c);

	Block(x, y+25, c);
}
void Graphics::chQ(int x, int y, Color c)
{
	Block(x+5, y, c);
	Block(x+10, y, c);
	Block(x+15, y, c);

	Block(x, y+5, c);
	Block(x+20, y+5, c);

	Block(x, y+10, c);
	Block(x+20, y+10, c);

	Block(x, y+15, c);
	Block(x+10, y+15, c);
	Block(x+20, y+15, c);

	Block(x, y+20, c);
	Block(x+15, y+20, c);

	Block(x+5, y+25, c);
	Block(x+10, y+25, c);
	Block(x+20, y+25, c);
}
void Graphics::chR(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+5, y, c);
	Block(x+10, y, c);
	Block(x+15, y, c);

	Block(x, y+5, c);
	Block(x+20, y+5, c);

	Block(x, y+10, c);
	Block(x+5, y+10, c);
	Block(x+10, y+10, c);
	Block(x+15, y+10, c);

	Block(x, y+15, c);
	Block(x+20, y+15, c);

	Block(x, y+20, c);
	Block(x+20, y+20, c);

	Block(x, y+25, c);
	Block(x+20, y+25, c);
}
void Graphics::chS(int x, int y, Color c)
{
	Block(x+5, y, c);
	Block(x+10, y, c);
	Block(x+15, y, c);
	Block(x+20, y, c);

	Block(x, y+5, c);

	Block(x+5, y+10, c);
	Block(x+10, y+10, c);
	Block(x+15, y+10, c);

	Block(x+20, y+15, c);

	Block(x+20, y+20, c);

	Block(x, y+25, c);
	Block(x+5, y+25, c);
	Block(x+10, y+25, c);
	Block(x+15, y+25, c);
}
void Graphics::chT(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+5, y, c);
	Block(x+10, y, c);
	Block(x+15, y, c);
	Block(x+20, y, c);

	Block(x+10, y+5, c);

	Block(x+10, y+10, c);

	Block(x+10, y+15, c);

	Block(x+10, y+20, c);

	Block(x+10, y+25, c);
}
void Graphics::chU(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+20, y, c);

	Block(x, y+5, c);
	Block(x+20, y+5, c);

	Block(x, y+10, c);
	Block(x+20, y+10, c);

	Block(x, y+15, c);
	Block(x+20, y+15, c);

	Block(x, y+20, c);
	Block(x+20, y+20, c);

	Block(x+5, y+25, c);
	Block(x+10, y+25, c);
	Block(x+15, y+25, c);
}
void Graphics::chV(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+20, y, c);

	Block(x, y+5, c);
	Block(x+20, y+5, c);

	Block(x, y+10, c);
	Block(x+20, y+10, c);

	Block(x+5, y+15, c);
	Block(x+15, y+15, c);

	Block(x+5, y+20, c);
	Block(x+15, y+20, c);

	Block(x+10, y+25, c);
}
void Graphics::chW(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+20, y, c);

	Block(x, y+5, c);
	Block(x+20, y+5, c);

	Block(x, y+10, c);
	Block(x+20, y+10, c);

	Block(x, y+15, c);
	Block(x+10, y+15, c);
	Block(x+20, y+15, c);

	Block(x, y+20, c);
	Block(x+10, y+20, c);
	Block(x+20, y+20, c);

	Block(x+5, y+25, c);
	Block(x+15, y+25, c);
}
void Graphics::chX(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+20, y, c);

	Block(x+5, y+5, c);
	Block(x+15, y+5, c);

	Block(x+10, y+10, c);

	Block(x+10, y+15, c);

	Block(x+5, y+20, c);
	Block(x+15, y+20, c);

	Block(x, y+25, c);
	Block(x+20, y+25, c);
}
void Graphics::chY(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+20, y, c);

	Block(x, y+5, c);
	Block(x+20, y+5, c);

	Block(x+5, y+10, c);
	Block(x+15, y+10, c);

	Block(x+10, y+15, c);

	Block(x+10, y+20, c);

	Block(x+10, y+25, c);
}
void Graphics::chZ(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x+5, y, c);
	Block(x+10, y, c);
	Block(x+15, y, c);
	Block(x+20, y, c);

	Block(x+20, y+5, c);

	Block(x+15, y+10, c);

	Block(x+10, y+15, c);

	Block(x+5, y+20, c);

	Block(x, y+25, c);
	Block(x+5, y+25, c);
	Block(x+10, y+25, c);
	Block(x+15, y+25, c);
	Block(x+20, y+25, c);
}

void Graphics::ch0(int x, int y, Color c)
{
	Block(x + 5, y, c);
	Block(x + 10, y, c);
	Block(x + 15, y, c);

	Block(x, y + 5, c);
	Block(x + 15, y + 5, c);
	Block(x + 20, y + 5, c);

	Block(x, y + 10, c);
	Block(x + 10, y + 10, c);
	Block(x + 20, y + 10, c);

	Block(x, y + 15, c);
	Block(x + 10, y + 15, c);
	Block(x + 20, y + 15, c);

	Block(x, y + 20, c);
	Block(x + 5, y + 20, c);
	Block(x + 20, y + 20, c);

	Block(x + 5, y + 25, c);
	Block(x + 10, y + 25, c);
	Block(x + 15, y + 25, c);
}
void Graphics::ch1(int x, int y, Color c)
{
	Block(x + 15, y, c);

	Block(x + 10, y + 5, c);
	Block(x + 15, y + 5, c);

	Block(x + 15, y + 10, c);

	Block(x + 15, y + 15, c);

	Block(x + 15, y + 20, c);

	Block(x + 10, y + 25, c);
	Block(x + 15, y + 25, c);
	Block(x + 20, y + 25, c);
}
void Graphics::ch2(int x, int y, Color c)
{
	Block(x + 5, y, c);
	Block(x + 10, y, c);
	Block(x + 15, y, c);

	Block(x, y + 5, c);
	Block(x + 20, y + 5, c);

	Block(x + 20, y + 10, c);

	Block(x + 5, y + 15, c);
	Block(x + 10, y + 15, c);
	Block(x + 15, y + 15, c);

	Block(x, y + 20, c);

	Block(x , y + 25, c);
	Block(x + 5, y + 25, c);
	Block(x + 10, y + 25, c);
	Block(x + 15, y + 25, c);
	Block(x + 20, y + 25, c);
}
void Graphics::ch3(int x, int y, Color c)
{
	Block(x, y + 5, c);

	Block(x + 5, y, c);
	Block(x + 10, y, c);
	Block(x + 15, y, c);

	Block(x + 20, y + 5, c);

	Block(x + 10, y + 10, c);
	Block(x + 15, y + 10, c);

	Block(x + 20, y + 20, c);
	Block(x + 20, y + 15, c);

	Block(x, y + 20, c);

	Block(x + 5, y + 25, c);
	Block(x + 10, y + 25, c);
	Block(x + 15, y + 25, c);
}
void Graphics::ch4(int x, int y, Color c)
{
	Block(x + 15, y, c);

	Block(x + 10, y + 5, c);
	Block(x + 15, y + 5, c);

	Block(x + 5, y + 10, c);
	Block(x + 15, y + 10, c);

	Block(x, y + 15, c);
	Block(x + 15, y + 15, c);

	Block(x, y + 20, c);
	Block(x + 5, y + 20, c);
	Block(x + 10, y + 20, c);
	Block(x + 15, y + 20, c);
	Block(x + 20, y + 20, c);

	Block(x + 15, y + 25, c);
}
void Graphics::ch5(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x + 5, y, c);
	Block(x + 10, y, c);
	Block(x + 15, y, c);
	Block(x + 20, y, c);

	Block(x, y + 5, c);

	Block(x, y + 10, c);
	Block(x + 5, y + 10, c);
	Block(x + 10, y + 10, c);
	Block(x + 15, y + 10, c);


	Block(x + 20, y + 15, c);

	Block(x + 20, y + 20, c);

	Block(x, y + 25, c);
	Block(x + 5, y + 25, c);
	Block(x + 10, y + 25, c);
	Block(x + 15, y + 25, c);
}
void Graphics::ch6(int x, int y, Color c)
{
	Block(x + 10, y, c);
	Block(x + 15, y, c);

	Block(x + 5, y + 5, c);


	Block(x, y + 10, c);

	Block(x, y + 15, c);
	Block(x + 5, y + 15, c);
	Block(x + 10, y + 15, c);
	Block(x + 15, y + 15, c);

	Block(x, y + 20, c);
	Block(x + 20, y + 20, c);

	Block(x + 5, y + 25, c);
	Block(x + 10, y + 25, c);
	Block(x + 15, y + 25, c);
}
void Graphics::ch7(int x, int y, Color c)
{
	Block(x, y, c);
	Block(x + 5, y, c);
	Block(x + 10, y, c);
	Block(x + 15, y, c);
	Block(x + 20, y, c);

	Block(x + 20, y + 5, c);

	Block(x + 15, y + 10, c);

	Block(x + 10, y + 15, c);

	Block(x + 5, y + 20, c);

	Block(x + 5, y + 25, c);
}
void Graphics::ch8(int x, int y, Color c)
{
	Block(x + 5, y, c);
	Block(x + 10, y, c);
	Block(x + 15, y, c);

	Block(x, y + 5, c);
	Block(x + 20, y + 5, c);

	Block(x + 5, y + 10, c);
	Block(x + 10, y + 10, c);
	Block(x + 15, y + 10, c);

	Block(x, y + 15, c);
	Block(x + 20, y + 15, c);

	Block(x, y + 20, c);
	Block(x + 20, y + 20, c);

	Block(x + 5, y + 25, c);
	Block(x + 10, y + 25, c);
	Block(x + 15, y + 25, c);
}
void Graphics::ch9(int x, int y, Color c)
{
	Block(x + 5, y, c);
	Block(x + 10, y, c);
	Block(x + 15, y, c);

	Block(x, y + 5, c);
	Block(x, y + 10 , c);
	Block(x + 20, y + 5, c);

	Block(x + 5, y + 15, c);
	Block(x + 10, y + 15, c);
	Block(x + 15, y + 15, c);
	Block(x + 20, y + 10, c);

	Block(x + 20, y + 15, c);

	Block(x + 20, y + 20, c);

	Block(x + 15, y + 25, c);
	Block(x + 10, y + 25, c);
	Block(x + 5, y + 25, c);
}

void Graphics::chDot(int x, int y, Color c)
{
	Block(x + 15, y + 20, c);
	Block(x + 20, y + 20, c);
	Block(x + 15, y + 25, c);
	Block(x + 20, y + 25, c);
}
void Graphics::chComma(int x, int y, Color c)
{
	Block(x + 15, y + 20, c);
	Block(x + 20, y + 20, c);
	Block(x + 20, y + 25, c);
	Block(x + 15, y + 30, c);
}
void Graphics::chApostrophe(int x, int y, Color c)
{
	Block(x + 20, y, c);

	Block(x + 20, y + 5, c);
}
void Graphics::chExMark(int x, int y, Color c)
{
	Block(x + 20, y, c);

	Block(x + 20, y + 5, c);

	Block(x + 20, y + 10, c);

	Block(x + 20, y + 15, c);

	Block(x + 20, y + 25, c);
}
void Graphics::chDash(int x, int y, Color c)
{
	Block(x + 10, y + 10, c);
	Block(x + 15, y + 10, c);
	Block(x + 20, y + 10, c);
}
void Graphics::chQMark(int x, int y, Color c)
{
	Block(x + 5, y, c);
	Block(x + 10, y, c);
	Block(x + 15, y, c);

	Block(x, y + 5, c);
	Block(x + 20, y + 5, c);

	Block(x + 15, y + 10, c);

	Block(x + 10, y + 15, c);

	Block(x + 10, y + 25, c);
}

void Graphics::chA(int x, int y, int r, int g, int b)
{
	chA(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chB(int x, int y, int r, int g, int b)
{
	chB(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chC(int x, int y, int r, int g, int b)
{
	chC(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chD(int x, int y, int r, int g, int b)
{
	chD(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chE(int x, int y, int r, int g, int b)
{
	chE(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chF(int x, int y, int r, int g, int b)
{
	chF(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chG(int x, int y, int r, int g, int b)
{
	chG(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chH(int x, int y, int r, int g, int b)
{
	chH(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chI(int x, int y, int r, int g, int b)
{
	chI(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chJ(int x, int y, int r, int g, int b)
{
	chJ(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chK(int x, int y, int r, int g, int b)
{
	chK(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chL(int x, int y, int r, int g, int b)
{
	chL(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chM(int x, int y, int r, int g, int b)
{
	chM(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chN(int x, int y, int r, int g, int b)
{
	chN(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chO(int x, int y, int r, int g, int b)
{
	chO(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chP(int x, int y, int r, int g, int b)
{
	chP(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chQ(int x, int y, int r, int g, int b)
{
	chQ(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chR(int x, int y, int r, int g, int b)
{
	chR(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chS(int x, int y, int r, int g, int b)
{
	chS(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chT(int x, int y, int r, int g, int b)
{
	chT(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chU(int x, int y, int r, int g, int b)
{
	chU(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chV(int x, int y, int r, int g, int b)
{
	chV(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chW(int x, int y, int r, int g, int b)
{
	chW(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chX(int x, int y, int r, int g, int b)
{
	chX(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chY(int x, int y, int r, int g, int b)
{
	chY(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chZ(int x, int y, int r, int g, int b)
{
	chZ(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::ch0(int x, int y, int r, int g, int b)
{
	ch0(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::ch1(int x, int y, int r, int g, int b)
{
	ch1(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::ch2(int x, int y, int r, int g, int b)
{
	ch2(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::ch3(int x, int y, int r, int g, int b)
{
	ch3(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::ch4(int x, int y, int r, int g, int b)
{
	ch4(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::ch5(int x, int y, int r, int g, int b)
{
	ch5(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::ch6(int x, int y, int r, int g, int b)
{
	ch6(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::ch7(int x, int y, int r, int g, int b)
{
	ch7(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::ch8(int x, int y, int r, int g, int b)
{
	ch8(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::ch9(int x, int y, int r, int g, int b)
{
	ch9(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chDot(int x, int y, int r, int g, int b)
{
	chDot(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chComma(int x, int y, int r, int g, int b)
{
	chComma(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chApostrophe(int x, int y, int r, int g, int b)
{
	chApostrophe(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chExMark(int x, int y, int r, int g, int b)
{
	chExMark(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chQMark(int x, int y, int r, int g, int b)
{
	chQMark(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}

void Graphics::chDash(int x, int y, int r, int g, int b)
{
	chDash(x, y, {unsigned char(r),unsigned char(g),unsigned char(b)});
}