#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define max_iter 100

void draw(double offset_real, double offset_imag)
{

    // Formula: z_n+1 = z_n^2 + c
    // c is a point in the complex plain
    /*
    z = (a + bi)
    then z² = (a + bi)² = a² + 2abi + (bi)²
            = a² + 2abi - b²      (because i² = -1)
            = (a² - b²) + (2ab)i

    real part is (a² - b²) and imaginary part is 2ab
    */

    // Find terminal size
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int rows = w.ws_row;
    int columns = w.ws_col / 2;

    // Clear screen
    printf("\033[2J");

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < columns; x++)
        {
            double c_real = offset_real + (x / (double)columns) * 3.4;
            double c_imag = offset_imag + (y / (double)rows) * 1.5;

            double z_real = 0, z_imag = 0;

            int in_set = 1;
            int i = 0;
            for (i = 0; i < max_iter; i++)
            {
                double new_real = z_real * z_real - z_imag * z_imag + c_real;
                double new_imag = 2 * z_real * z_imag + c_imag;
                z_real = new_real;
                z_imag = new_imag;
                if (z_real * z_real + z_imag * z_imag > 4.0)
                {
                    in_set = 0;
                    break;
                }
            }
            if (in_set)
            {
                printf("\033[%d;%dH ", y + 1, x * 2 + 1); // black/empty interior
            }
            else
            {
                printf("\033[%d;%dH", y + 1, x * 2 + 1);
                if (i < 3)
                    printf("  "); // empty/black for fast escapers
                else
                {
                    int color = (i % 6) + 31;
                    printf("\033[%dm██\033[0m", color);
                }
            }
        }
    }

    printf("\033[%d;1H", w.ws_row);
}

int main()
{
    double offset_real = -2.5;
    double offset_imag = -0.5;
    draw(offset_real, offset_imag);
    return 0;
}
