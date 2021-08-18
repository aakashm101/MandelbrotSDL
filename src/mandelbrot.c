#include <math.h>
#include "globals.h"
#include "mandelbrot.h"

void processMandelbrot(WindowParameters* wp, UserPreferences* up) 
{
	const int PIXEL_COUNT = wp->WINDOW_WIDTH * wp->WINDOW_HEIGHT;
	int previousProgress;
	int currentProgress;

	previousProgress = 0;
	for (int y = 0; y < wp->WINDOW_HEIGHT; y++)
	{
		for (int x = 0; x < wp->WINDOW_WIDTH; x++)
		{
			const double e = 2.718281828459; //Euler's number
			int iterations;
			double cr = mapToReal(x, -2.5, 1, wp);
			double ci = mapToImaginary(y, -1, 1, wp);
			Uint8 n, r, g, b, a;
			Uint32 pixel;

			// Fetch the number of iterations required for the complex input c
			iterations = mandelbrot(cr, ci, up->maxIterations);

			// Using logarithmic scale instead of linear scale and scaling it within range 0 to 255 (8 bit color)
			n = 255.0 / (log(iterations) / log(e));

			// Store the intensity value in each color variable (Use opaque alpha value = 0xFF)
			r = 0x00; g = 0x00; b = 0x00; a = 0xFF;
			
			// If single color is used (Monochrome), use the same intensity values for r,g,b
			if (up->useSingleColor)
			{
				r = n; g = n; b = n;
			}
			else 
			{
				// Depending on the number of iterations required by each complex number c (Pixel co-ordinate) the colors are chosen for each pixel
				if (n >= 0 && n < 63.5)
				{
					r = 0; g = 0; b = 0;
				}
				else if (n >= 63.5 && n < 127.5)
				{
					r = 0; g = n; b = 0;
				}
				else if (n >= 127.5 && n <= 191)
				{
					r = n; g = n; b = 0;
				}
				else if (n >= 191 && n <= 255)
				{
					r = n; g = 0; b = 0;
				}
			}
			
			pixel = r;  pixel = pixel << 8;
			pixel += g; pixel = pixel << 8;
			pixel += b; pixel = pixel << 8;
			pixel += a;

			// Invert the colors if the user chooses to invert colors
			wp->videoBuffer[(y * wp->WINDOW_WIDTH) + x] = up->invertColors ? ~pixel : pixel;

			currentProgress = (((float)(y * wp->WINDOW_WIDTH) + x) / PIXEL_COUNT) * 100;
			if (currentProgress != previousProgress)
			{
				previousProgress = currentProgress;
				printf("Progress = %2d percent\n", currentProgress);
			}
		}
	}
	printf("Progress = 100 percent.\nProcessing complete.\nDisplaying fractal.\n");
	return;
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
