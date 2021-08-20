#include <stdio.h>
#include <math.h>
#include "globals.h"
#include "mandelbrot.h"

const Uint32 PALETTE[] =
{
	0x000000, 0xff3242, 0xff3a40, 0xff403d, 0xff473b, 0xff4d38, 0xff5335, 0xff5932,
	0xff5f2f, 0xff652c, 0xff6b29, 0xff7026, 0xff7523, 0xff7b1f, 0xff801b, 0xff8517,
	0xff8b13, 0xff900e, 0xff9508, 0xff9a02, 0xff9f00, 0xffa400, 0xffa900, 0xffae00,
	0xffb300, 0xffb800, 0xffbd00, 0xffc100, 0xffc600, 0xffcb00, 0xffd000, 0xfed400,
	0xfcd903, 0xfade0c, 0xf8e215, 0xf6e71c, 0xf4eb23, 0xf1f029, 0xeff530, 0xecf936
};

const int PALETTE_SIZE = sizeof(PALETTE) / sizeof(Uint32);

void processMandelbrot(WindowParameters* const wp, const UserPreferences* const up) 
{
	const int PIXEL_COUNT = wp->WINDOW_WIDTH * wp->WINDOW_HEIGHT;
	int previousProgress;
	int currentProgress;
	int total;

	previousProgress = 0;
	total = 0;
	for (int y = 0; y < wp->WINDOW_HEIGHT; y++)
	{
		for (int x = 0; x < wp->WINDOW_WIDTH; x++)
		{
			const Uint32 ALPHA = 0xFF; // Force alpha to 255 (opaque)
			int iterations;
			double cr, ci;
			Uint32 pixel;

			cr = mapToReal(x, -2.5, 1, wp);
			ci = mapToImaginary(y, -1, 1, wp);

			// Fetch the number of iterations required for the complex input c
			iterations = mandelbrot(cr, ci, up->maxIterations);

			// If single color is used (Monochrome), use the same intensity values for r,g,b
			if (up->useSingleColor)
			{
				iterations = iterations % 256;
				pixel = iterations; pixel = pixel << 8;
				pixel += iterations; pixel = pixel << 8;
				pixel += iterations; pixel = pixel << 8;
				pixel += ALPHA;	
			}
			else 
			{
				iterations = iterations % PALETTE_SIZE;
				pixel = (PALETTE[iterations] << 8) | ALPHA;
			}

			// Invert the colors if the user chooses to invert colors
			wp->videoBuffer[(y * wp->WINDOW_WIDTH) + x] = up->invertColors ? (~pixel) | ALPHA : pixel;

			// Display the current progress
			currentProgress = (((float)(y * wp->WINDOW_WIDTH) + x) / PIXEL_COUNT) * 100;
			if (currentProgress != previousProgress)
			{
				previousProgress = currentProgress;
				printf("Progress = %3d percent\n", currentProgress);
			}
		}
	}
	printf("Progress = 100 percent\nProcessing complete.\nDisplaying fractal.\n");
	return;
}

inline double mapToReal(const int x, const double minR, const double maxR, const WindowParameters* const wp)
{
	return x * ((maxR - minR) / wp->WINDOW_WIDTH) + minR;
}

inline double mapToImaginary(const int y, const double minI, const double maxI, const WindowParameters* const wp)
{
	return y * ((maxI - minI) / wp->WINDOW_HEIGHT) + minI;
}

int mandelbrot(const double cr, const double ci, const int maxIterations)
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