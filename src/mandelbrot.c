#include "globals.h"
#include "mandelbrot.h"

void processMandelbrot(WindowParameters* wp, UserPreferences* up) 
{
	const int PIXEL_COUNT = wp->WINDOW_WIDTH * wp->WINDOW_HEIGHT;
	int previousProgress;
	int currentProgress;

	printf("Processing mandelbrot set...\n");
	previousProgress = 0;
	for (int y = 0; y < wp->WINDOW_HEIGHT; y++)
	{
		for (int x = 0; x < wp->WINDOW_WIDTH; x++)
		{
			double cr = mapToReal(x, -2.5, 1, wp);
			double ci = mapToImaginary(y, -1, 1, wp);
			Uint8 n, r, g, b, a;
			Uint32 pixel;

			n = mandelbrot(cr, ci, up->maxIterations) % 256;
			r = n; g = n; b = n; a = 0xFF;
			pixel = r;  pixel = pixel << 8;
			pixel += g; pixel = pixel << 8;
			pixel += b; pixel = pixel << 8;
			pixel += a;
			wp->videoBuffer[(y * wp->WINDOW_WIDTH) + x] = up->invertColors ? ~pixel : pixel;     // Invert the colors if the user chooses to invert colors

			currentProgress = (((float)(y * wp->WINDOW_WIDTH) + x) / PIXEL_COUNT) * 100;
			if (currentProgress != previousProgress)
			{
				previousProgress = currentProgress;
				printf("Progress = %2d percent\n", currentProgress);
			}
		}
	}
	printf("Progress = 100 percent.\nProcessing complete.\nDisplaying fractal.\n");
}

inline double mapToReal(int x, double minR, double maxR, const WindowParameters* const wp)
{
	return x * ((maxR - minR) / wp->WINDOW_WIDTH) + minR;
}

inline double mapToImaginary(int y, double minI, double maxI, const WindowParameters* const wp)
{
	return y * ((maxI - minI) / wp->WINDOW_HEIGHT) + minI;
}

int mandelbrot(double cr, double ci, int maxIterations)
{
	int iteration = 0;
	double zr = 0, zi = 0;
	while (iteration < maxIterations && (zr * zr) + (zi * zi) <= 4.0)
	{
		double temp = zr * zr - zi * zi + cr;
		zi = 2 * zr * zi + ci;
		zr = temp;
		iteration++;
	}
	return iteration;
}
