#include "Image.h"

Image::Image()
{

}

Image::~Image()
{

}

Image::Image(int w, int h)
{
	width = w; height = h;
	pixels = new int[w*h];
}

void Image::setPixel(int rgb, int x, int y)
{
	pixels[x + y*width] = rgb;
}

int Image::getWidth()
{
	return width;
}

int Image::getHeight()
{
	return height;
}

int Image::getPixel(int x, int y)
{
	return pixels[x + y*width];
}

int* Image::getPixels()
{
	return pixels;
}

int readByteToInt(char *b, int start)
{
	return (((b[start + 0] & 0xff) << 24) | ((b[start + 1] & 0xff) << 16) | ((b[start + 2] & 0xff) << 8) | ((b[start + 3] & 0xff)));
}

void Image::loadImage(string caminhoImage)
{
	int convert;
	int length;
	char * buffer;

	ifstream is;
	is.open(caminhoImage, ios::binary);

	if (is.is_open())
	{
		// Pega o comprimento do arquivo
		is.seekg(0, ios::end);
		length = is.tellg();
		is.seekg(0, ios::beg);

		// alocando memória
		buffer = new char[length];

		string linhaCodigo;
		getline(is, linhaCodigo);

		string linhaTamanhoImagem;
		getline(is, linhaTamanhoImagem);

		if (linhaTamanhoImagem[0] == '#')
		{
			getline(is, linhaTamanhoImagem);
		}

		string maxRange;
		getline(is, maxRange);

		//Leitura de um bloco de dados
		is.read(buffer, length);
		is.close();

		//if (linhaCodigo[0] == 'P' && linhaCodigo[1] == '3')
		//{
			width = stoi(linhaTamanhoImagem);
			height = stoi(linhaTamanhoImagem.substr(linhaTamanhoImagem.find(' ') + 1));
			pixels = new int[width*height];

			int a = 0;
			for (int y = 0; y < this->height; y++)
			{
				for (int x = 0; x < this->width; x++)
				{
					convert = readByteToInt(buffer, a);
					//int argb = (((buffer[a + 0] & 0xff) << 24) | ((buffer[a + 1] & 0xff) << 16) | ((buffer[a + 2] & 0xff) << 8) | ((buffer[a + 3] & 0xff)));
					this->setPixel(convert, x, (height - y) - 1);
					a = a + 4;
				}
			}
		//}

		delete[] buffer;
	}
	
}

void Image::plot(int *pixels, int xInicial, int yInicial, int w, int h, int scanW, int scanH)
{
	float alpha;
	int r, g, b;
	int backR, backG, backB;

	for (int y = 0; y < scanH; y++)
	{
		for (int x = 0; x < scanW; x++)
		{
			//setPixel(pixels[x+y*w],xInicial + x,yInicial + y);

			alpha = (pixels[x + y*scanW] >> 24) & 0xff;
			r = (pixels[x + y*scanW] >> 16) & 0xff;
			g = (pixels[x + y*scanW] >> 8) & 0xff;
			b = pixels[x + y*scanW] & 0xff;

			if (alpha != 255)
			{
				alpha /= 255;

				//pixels da Image do fundo
				backR = (this->getPixel(x + xInicial, y + yInicial) >> 16) & 0xff;
				backG = (this->getPixel(x + xInicial, y + yInicial) >> 8) & 0xff;
				backB = this->getPixel(x + xInicial, y + yInicial) & 0xff;

				r = backR*(1 - alpha) + r*alpha;
				g = backG*(1 - alpha) + g*alpha;
				b = backB*(1 - alpha) + b*alpha;
			}

			alpha *= 255;
			int argb = ((int)alpha << 24) | (r << 16) | (g << 8) | b;

			setPixel(argb, xInicial + x, yInicial + y);
		}
	}
}

void Image::loadImage(int posX, int posY, int W, int H, int *pixels)
{
	for (int y = 0; y < H; y++)
	{
		for (int x = 0; x < W; x++)
		{
			int xs = (x + posX) % this->getWidth();
			setPixel(pixels[xs + y*W], x, y);
		}
	}
}

void Image::removerSobreposicao(int posX, int posY, int scanW, int scanH)
{
	for (int y = posY; y < scanH; y++)
	{
		for (int x = posX; x < scanW; x++)
		{
			if (pixels[x + y * width] > 0)
			{
				int a = 0; // alfa
				this->pixels[x + y * width] = 255 - a; // proporção. 0 = total
			}
		}
	}
}