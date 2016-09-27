#include "Includes.h"

using namespace std;

class Image
{
private:
	int *pixels;
	int width, height;

public:
	Image();
	~Image();
	Image(int w, int h);

	int getPixel(int x, int y);
	int *getPixels();
	int getWidth();
	int getHeight();
	void setPixel(int rgb, int x, int y);

	void loadImage(string caminhoImage);
	void plot(int *pixels, int xInicial, int yInicial, int w, int h, int scanW, int scanH);
	void loadImage(int posX, int posY, int W, int H, int *pixels);
	void removerSobreposicao(int w, int h, int scanW, int scanH);
};